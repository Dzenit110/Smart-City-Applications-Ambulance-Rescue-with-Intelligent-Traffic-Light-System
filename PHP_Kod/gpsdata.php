<?php 

require 'config.php';

$enl = $_GET['enl'];
$boym = $_GET['boym'];

echo $enl;
echo "<br>";
echo $boym;


$sql = "INSERT INTO tbl_gps(enl,boym,tarih) 
	VALUES('".$enl."','".$boym."','".date("Y-m-d H:i:s")."')";

if($db->query($sql) === FALSE)
	{ echo "Error: " . $sql . "<br>" . $db->error; }

echo "<br>";
echo $db->insert_id;
