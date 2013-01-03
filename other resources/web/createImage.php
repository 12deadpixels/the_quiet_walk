<?php
/*this is the main heatmapping script: it takes a series of lats and longs from xml files and then converts them to screen space
it uses IDW algorithm to interpolate for the heatmap
this version takes a 10 mile radius around newcastle and ignores any results outside that
*/
set_time_limit(0);

//the centre point: in this case newcastle
  		$clat= 54.980095; 
  		$clng= -1.614614;
  		
//delete previous map
unlink('map.png');
$root_dir=".";
$files = scandir($root_dir);
$extensions = array(".xml",".php",".htm");
$xmlFiles=array();

//function from http://snipplr.com/view.php?codeview&id=2531 many thanks 
function distance($lat1, $lng1, $lat2, $lng2, $miles = true)
{
	$pi80 = M_PI / 180;
	$lat1 *= $pi80;
	$lng1 *= $pi80;
	$lat2 *= $pi80;
	$lng2 *= $pi80;

	$r = 6372.797; // mean radius of Earth in km
	$dlat = $lat2 - $lat1;
	$dlng = $lng2 - $lng1;
	$a = sin($dlat / 2) * sin($dlat / 2) + cos($lat1) * cos($lat2) * sin($dlng / 2) * sin($dlng / 2);
	$c = 2 * atan2(sqrt($a), sqrt(1 - $a));
	$km = $r * $c;

	return ($miles ? ($km * 0.621371192) : $km);
}
//http://stackoverflow.com/questions/11111077/find-latitude-longitude-point-in-php-given-initial-lat-lng-distance-and-bearin
function destinationPoint($lat, $lng, $brng, $dist) {
		$latandlong=array();
     // $meters = $dist/3.2808399; // dist in meters
      //$dist =  $meters/1000; // dist in km
      $rad = 6371; // earths mean radius
      $dist = $dist/$rad;  // convert dist to angular distance in radians
      $brng = deg2rad($brng);  // conver to radians 
      $lat1 = deg2rad($lat); 
      $lon1 = deg2rad($lng);

      $lat2 = asin(sin($lat1)*cos($dist) + cos($lat1)*sin($dist)*cos($brng) );
      $lon2 = $lon1 + atan2(sin($brng)*sin($dist)*cos($lat1),cos($dist)-sin($lat1)*sin($lat2));
      $lon2 = fmod($lon2 + 3*M_PI, 2*M_PI) - M_PI;
      $lat2 = rad2deg($lat2);
      $lon2 = rad2deg($lon2);
		array_push($latandlong, $lat2);
		array_push($latandlong, $lon2);
		
        echo "lat2 = ".$lat2."<br/>";
        echo "lon2 = ".$lon2."<br/>";
        return $latandlong;
}
function getFileExtension($fname){
	$brokenFName = explode(".",$fname);
	if(sizeof($brokenFName)>0){
	return $brokenFName[sizeof($brokenFName)-1];
	}
	else
	{
	return "no extension";
	}
}

function beginsWithDot($fname){
	$firstChar = substr($fname,0,1);
	if($firstChar=="."){
	return true;
	}
	else
	{
	return false;
	}
}

function mapRange($OldValue,$OldMin, $OldMax, $NewMin, $NewMax){
	$OldRange = ($OldMax - $OldMin) ;
	$NewRange = ($NewMax - $NewMin)  ;
	$NewValue = ((($OldValue - $OldMin) * $NewRange) / $OldRange) + $NewMin;
	return $NewValue;
}
// Loop through each filename of scandir
foreach ($files as $filename) {
	 // Construct a full path
	 //$filepath = $root_dir.'/'.$filename;

	 // Is it a file? If so, get the extension using some function you created
	 if(is_file($filename)) {
		  $ext = "xml";//getFileExtension($filename);
		  //echo getFileExtension($filename);
		  if(getFileExtension($filename)==$ext && !beginsWithDot($filename)){
		  array_push($xmlFiles, $filename);
		  }
	 }
}
$lats = array();
$longs =array();
$dbs =array();

//got through each xml file
foreach ($xmlFiles as $xmlFileName) {
$xml = simplexml_load_file($xmlFileName);

//go untill you get to the xml elements we are interested in
foreach($xml->children() as $child)
  {
  foreach($child->children() as $item)
  {
  	if($item->getName()=="item"){
  		//echo $item->getName() . ": " . $item . "<br>";
  		
  		$alat;
  		$along;
  		$ageo;
  		foreach($item->children() as $elems)
  		{
  			if($elems->getName()=="geolat"){
  				//array_push($lats ,floatval($elems) );
  				$alat= floatval($elems);
  			}
  			if($elems->getName()=="geolong"){
  				//array_push($longs ,floatval($elems) );
  				$along= floatval($elems);
  			}
  			if($elems->getName()=="geodB_low"){
  				//array_push($dbs ,floatval($elems) );
  				$ageo= floatval($elems);
  			}
  		}
  		  			//check that this location is with 10 miles of NCL city centre

  		//echo " ";
  		//echo distance($alat, $along, $lat2, $lng2, $miles = true);
  		//echo " ";
		if(distance($alat, $along, $clat, $clng, $miles = true)<10){
			array_push($lats ,floatval($alat)) ;
			array_push($longs ,floatval($along)) ;
			array_push($dbs ,floatval($ageo)) ;
			//echo "// in range //";
		}
		else{
			//echo "// not in range ///";
		}
  		
  	}
  }
  }
}


//add notional fade out points at extended four corners
//+- 0.02 is a couple of miles ish... not very scientific but will do for now.
$xPos= array();
$yPos = array();

$minLat =min ( $lats );
$maxLat =max ( $lats );

$minLong =min ( $longs );
$maxLong =max ( $longs );


/*echo "<br>".strval($minLat)."<br>";
echo strval($maxLat)."<br>";
echo strval($minLong)."<br>";
echo strval($maxLong)."<br>";*/


$angle = 0.0;
//$inc = (2.0*M_PI) /10.0;
$inc = 360.0 /30.0;
echo " inc ".$inc;
for($i = 0; $i<30; $i++){
	$thisLatLong = destinationPoint($clat, $clng, $angle, 9.0) ;
	//$x = destinationPoint($clat, $lng, $angle, $dist)  ;
	//$y =  destinationPoint($lat, $lng, $angle, $dist) ;
	echo strval($thisLatLong[0])." ".$thisLatLong[1]."<br>";
	
	array_push($lats ,$thisLatLong[0]) ;
	array_push($longs ,$thisLatLong[1]) ;
	array_push($dbs ,0) ;
	$angle += $inc;
	echo " angle ".strval( $angle)."<br>";
}



$wr= max ( $lats )- min ( $lats );
$hr= max ( $longs )- min ( $longs );

$ratio = $wr/$hr;

$fPoints = array();
$w = 250;
$h = 250;//$w*$ratio;
echo "ratio is ".$ratio."<br>";
echo $w." ".$h;

//fill pixel array with mapped values

for($i = 0; $i<sizeof($lats); $i++){

	//echo mapRange(  $lats [$i], min ( $lats ), max ( $lats ) , 0,1)."<br>";
	$xPos[$i] = ($w * mapRange(  $longs [$i], min ( $longs ), max ( $longs ) , 0,1));
	$yPos[$i] = ($h * (1-mapRange(  $lats [$i], min ( $lats ), max ( $lats ) , 0,1)));
	echo "x and y at ".strval($i)." is ".strval($xPos[$i])." ".strval($yPos[$i]) ."<br>";
	
	$fPoints[$i] =mapRange(  $dbs  [$i], min ( $dbs ), max ( $dbs ) , 0,1);//mt_rand(0.0,100.0)/100;	
}


$gd = imagecreatetruecolor($w, $h);
imagealphablending($gd,false);
imagesavealpha($gd, true);
//$red = imagecolorallocate($gd, 255, 0, 0); 

$numPoints = 10;



function getMaxDistanceFromPoint($x, $y, $xs =array(), $ys=array()) {
	$maxDistance=0.0;
	for ($i=0; $i<sizeof($xs); $i++)
  	{
  		$thisDist = sqrt ((($xs[$i]-$x)*($xs[$i]-$x)) + (($ys[$i]-$y)*($ys[$i]-$y)));
  		if ($thisDist>$maxDistance) {
            $maxDistance=$thisDist;
        }
  	}
	return $maxDistance;
}

function getAllDistancesFromPoint($x, $y, $xs =array(), $ys=array()) {
	$allDistances=array();
	for ($i=0; $i<sizeof($xs); $i++)
  	{
  		$thisDist = sqrt ((($xs[$i]-$x)*($xs[$i]-$x)) + (($ys[$i]-$y)*($ys[$i]-$y)));
  		
  		//if ($thisDist>$maxDistance) {
            $allDistances[$i]=$thisDist;
        //}
  	}
  	
	return $allDistances;
}
function getInterpValue($x, $y, $xs =array(), $ys=array(), $f=array()) {
	$interpValue=0.0;
	for ($i=0; $i<sizeof($xs); $i++)
  	{
  		$maxDist = getMaxDistanceFromPoint( $x, $y, $xs, $ys);
  		
  		$allDistances= getAllDistancesFromPoint( $x, $y, $xs, $ys);
  		$thisDist = sqrt ((($xs[$i]-$x)*($xs[$i]-$x)) + (($ys[$i]-$y)*($ys[$i]-$y)));
  		$interpValue += $f[$i]*getWeight( $maxDist, $thisDist, $allDistances );
  	}
  	return $interpValue;
}

function getWeight($maxDistance, $thisDistance, $allDistances=array() ) {
	$weight=0.0;
	if($maxDistance * $thisDistance ==0){
		echo "zero here";	
	}
	$firstTerm = pow((($maxDistance - $thisDistance   )/( $maxDistance * $thisDistance  )),2);
	$secondTerm=0.0;
	for ($i=0; $i<sizeof($allDistances); $i++)
  	{
  		$secondTerm += pow((($maxDistance - $allDistances[$i]   )/( $maxDistance * $allDistances[$i]  )), 2);
  	}
  	$weight = $firstTerm/$secondTerm;
    return $weight;
}
function HSVtoRGB(array $hsv) {
    list($H,$S,$V) = $hsv;
    //1
    $H *= 6;
    //2
    $I = floor($H);
    $F = $H - $I;
    //3
    $M = $V * (1 - $S);
    $N = $V * (1 - $S * $F);
    $K = $V * (1 - $S * (1 - $F));
    //4
    switch ($I) {
        case 0:
            list($R,$G,$B) = array($V,$K,$M);
            break;
        case 1:
            list($R,$G,$B) = array($N,$V,$M);
            break;
        case 2:
            list($R,$G,$B) = array($M,$V,$K);
            break;
        case 3:
            list($R,$G,$B) = array($M,$N,$V);
            break;
        case 4:
            list($R,$G,$B) = array($K,$M,$V);
            break;
        case 5:
        case 6: //for when $H=1 is given
            list($R,$G,$B) = array($V,$M,$N);
            break;
    }
    return array($R, $G, $B);
}

$pixLength = $w * $h;
echo "starting pic";
$x=0;
$y=0;

$xs = $w/2;
$ys= $h/2;



$maxRange = sqrt ( ($xs*$xs)+($ys*$ys));
for ($i = 0; $i < $pixLength; $i++) {

	$colorArray = array();
	
	$hue = getInterpValue($x, $y, $xPos, $yPos, $fPoints);
	
	$hsv = array($hue,1,1);

	$colorArray = HSVtoRGB($hsv);
	
	$thisDist = sqrt ((($xs-$x)*($xs-$x)) + (($ys-$y)*($ys-$y)));
	
	
	
	if($thisDist> ($maxRange *0.6)){
		$alpha= mapRange($thisDist,0, $maxRange, 0,  127);
	}
	else{
		$alpha	=0;
	}
	$aColor = imagecolorallocatealpha($gd, 255*$colorArray[0],255*$colorArray[1],255*$colorArray[2],(127-(127 * $hue )) ); 

  	imagesetpixel($gd, $x,$y, $aColor);
  
  $x += 1;
  if( $x>=$w){
  	$x=0;
  	$y += 1;
  }
}
//draw a spot at each point
/*$white = imagecolorallocate($gd, 255, 255, 255);
echo "sizeof($xPos)".strval(sizeof($xPos));
for ($i = 0; $i < sizeof($xPos); $i++) {
	imagearc($gd, $xPos[$i], $yPos[$i], 3, 3,  0, 360, $white);
}*/
	$fname = "map.png";
	
	$coord_string = strval(min($lats))."_".strval(min($longs))."_".strval(max($lats))."_".strval( max($longs))."_".strval($clat)."_".strval($clng);
	file_put_contents ( "coord_log.txt" ,$coord_string);
	header('Content-Type: image/png');
	imagepng($gd, $fname);
	

//echo json_encode($xmlFiles);
?>