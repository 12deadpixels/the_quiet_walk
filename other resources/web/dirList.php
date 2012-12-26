<?php
$root_dir=".";
$files = scandir($root_dir);
$extensions = array(".xml",".php",".htm");
$xmlFiles=array();

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
echo json_encode($xmlFiles);
?>