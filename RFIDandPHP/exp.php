<?php
date_default_timezone_set('Asia/Manila');
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "rfidandphp";

try {
    $conn=mysqli_connect($servername,$username,$password,$dbname);
    }
catch(PDOException $e)
    {
    	echo "Connection failed: " . $e->getMessage();
    }

$i ="SELECT * FROM rfid WHERE date = CURDATE();";
$result = mysqli_query($conn, $i);
echo mysqli_num_rows($result);
	
?>