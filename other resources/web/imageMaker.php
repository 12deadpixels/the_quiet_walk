<?php

$w = 250;
$h = 250;

$gd = imagecreatetruecolor($w, $h);

$red = imagecolorallocate($gd, 255, 0, 0); 

$numPoints = 10;
$xPos= array();
$yPos = array();
$fPoints = array();
for ($i=0; $i<$numPoints; $i++)
  	{
  		$xPos[$i] = rand(0,$w);
  		$yPos[$i] = rand(0,$h);
  		$fPoints[$i] = mt_rand(0.0,100.0)/100;
  		echo " test pints ";
  		echo $xPos[$i];
  	}
echo "TEST";

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

for ($i = 0; $i < $pixLength; $i++) {

	$colorArray = array();
	
	$hue = getInterpValue($x, $y, $xPos, $yPos, $fPoints);
	
	$hsv = array($hue,1,1);

	$colorArray = HSVtoRGB($hsv);
	// echo " hue ";
	//$aColor = imagecolorallocate($gd, $hue*255 	,0 ,0  ); 
	$aColor = imagecolorallocate($gd, 255*$colorArray[0],255*$colorArray[1],255*$colorArray[2] ); 
  	//$aColor = imagecolorallocate($gd, 255*$hue,255*$hue,255*$hue ); 

  	imagesetpixel($gd, $x,$y, $aColor);
  
  $x += 1;
  if( $x>=$w){
  	$x=0;
  	$y += 1;
  }
}
 
header('Content-Type: image/png');
imagepng($gd, "map.png");

?>

