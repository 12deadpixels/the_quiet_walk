<?php

$header = "<?xml version='1.0'?>\n";
$header .= "<rss version='2.0' xmlns:geo='http://www.w3.org/2003/01/geo/wgs84_pos#' xmlns:dc='http://purl.org/dc/elements/1.1/'>\n";
$header .= "  <channel>\n";
$header .= "    <title>The Quiet Walk</title>\n";
$header .= "    <description>A project by Alessandro Altavilla and Tom Schofield. Php script by Paolo Marangi www.zuf.it </description>\n";
$header .= "    <link>http://www.alessandroaltavilla.net/thequietwalk</link>\n";
$header .= "    <dc:publisher>Alessandro Altavilla and Tom Schofield @cc </dc:publisher>\n";
$header .= "    <pubDate>";
$header.=date("d-M-y_H-i-s");
$header.="</pubDate>\n";

$xml = $header;

$maxEntries = 4;
$validCoordsCount = 0;

//hack because I can't seem to get the contents of the array properly
for ($i = 0; $i < $maxEntries; $i++) {
	echo "longI_".strval($i);
	$longin = $_POST["longI_".strval($i)];
	$lati = $_POST["lat_".strval($i)];
	$decibels = $_POST["dB_low_".strval($i)];
	echo "LEGNTH \n";
	echo strlen("    <item><geolat>$lati</geolat><geolong>$longin</geolong><geodB_low>$decibels</geodB_low></item>\n");
	//if(floatval($longin)<90.0 && floatval($longin)>-90.0){
	if(strlen("    <item><geolat>$lati</geolat><geolong>$longin</geolong><geodB_low>$decibels</geodB_low></item>\n")>77){
	$xml.= "    <item><geolat>$lati</geolat><geolong>$longin</geolong><geodB_low>$decibels</geodB_low></item>\n";
		$validCoordsCount+=1;
	}
}
$xml.= "</channel>\n";
$xml.= "</rss>\n";

//$filepath = $dir.'/'.date("/d-M-y/d-M-y_H-i-s.xml");
//is_dir() {mkdir(...)}
$filepath =  date("d-M-y_H-i-s");
$filepath.=".xml";

if($validCoordsCount>0){
	file_put_contents($filepath, $xml, FILE_APPEND | LOCK_EX);
}

//$myFile = "fishys.xml";
//$fh = fopen($myFile, 'a') or die("can't open file");

//$stringData = "<?xml version='1.0'?>\n";
//fwrite($fh, $stringData);
//fclose($fh);
?>