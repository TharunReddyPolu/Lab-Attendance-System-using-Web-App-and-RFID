<?php
date_default_timezone_set("Asia/Calcutta"); 
if($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["action"])){
	switch ($_POST['action']) {
		case 'insertinRecord':
		insertinRecord();
		break;
		case 'insertoutRecord':
		insertoutRecord();
		break;
		case 'showProcess':
		showProcess();
		break;
		case 'checkRecord':
		checkRecord();
		break;
		default:
		break;
	}
}

function insertinRecord() {
    include 'conn.php';
    $cardid = $_POST['cardid'];
	$stmt = $conn->prepare("INSERT INTO `rfid` ( `cardid`, `datetime`, `date`, `intime`, `outtime`) VALUES ( '$cardid', current_timestamp(), current_timestamp(), current_timestamp(), current_timestamp())");    
	$stmt->execute();
	echo "success";
}

function insertoutRecord() {
    include 'conn.php';
    $cardid = $_POST['cardid'];
	$stmt = $conn->prepare("INSERT INTO `rfid` ( `cardid`, `datetime`, `date`, `intime`, `outtime`) VALUES ( '$cardid', current_timestamp(), current_timestamp(), current_timestamp(), current_timestamp())");    
	$stmt->execute();
	echo "success";
}

function checkRecord() {
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
	$cardid = $_POST['cardid'];
	$sql="SELECT * FROM rfid WHERE date = CURDATE() and cardid=$cardid";
	$result = mysqli_query($conn, $sql);
	$num=mysqli_num_rows($result);
	if($num>0)
	{	
		echo "yes";
	}
	else
	{
		echo "no";
	}
}

function showProcess()
{
	include 'conn.php';

	$logs = $conn->query("SELECT * FROM `rfid`");
	while($r = $logs->fetch()){
		echo "<tr>";
		echo "<td>".$r['id']."</td>";
		echo "<td>".$r['cardid']."</td>";
		$dateadded = date("F j, Y, g:i a", $r["logdate"]);
		echo "<td>".$dateadded."</td>";
		echo "</tr>";
	}
}

?>
