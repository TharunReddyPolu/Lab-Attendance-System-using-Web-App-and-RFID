<?php
date_default_timezone_set('Asia/Manila');
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "rfidandphp";

try {
    $conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    }
catch(PDOException $e)
    {
    	echo "Connection failed: " . $e->getMessage();
    }
$logs = $conn->query("SELECT DISTINCT date FROM `rfid`");

    if(isset($_POST['select']))
    {
        $valueToSearch = $_POST["selects"];
        $log = $conn->query("SELECT * FROM `rfid` where date LIKE '%".$valueToSearch."%'");
    }
     else {
      $log = $conn->query("SELECT * FROM `rfid`");

    }
	
?>


<style>

.date-selecter{
    padding:10px;
    align:center; 
    background-color:black;
    color:white;
}

.submit{
    padding:10px;
    align:center; 
    background-color:black;
    color:white;
}

table {
    border-collapse: collapse;
    width: 50%;
	margin: auto;
  }

th, td {
    text-align: left;
    padding: 8px;
    color:black;
  }

tr:nth-child(even){
  background-color: #f2f2f2;
  }

th {
    background-color: #000;
    color: white;
  }

</style>


<!DOCTYPE html>
<html>
<body align="center">
<form action="attendance.php" method="POST">
  <select name="selects" class="date-selecter" required>
    <option value="">SELECT DATE</option>
    <?php
    while($r = $logs->fetch()){
    ?>
    <option  value="<?php echo $r["date"];?>"><?php echo $r["date"];?></option>
    <?php } ?>
  </select>
  <input type="submit" class="submit"  name="select">
</form>

<table>
    <thead>
	  <tr>
		<th colspan="5" style="background:green" >All Records</th>
	  </tr>
      <tr>
        <th>ID</th>
        <th>CARD ID</th>
        <th>DATE</th>
        <th>IN TIME</th>
        <th>OUT TIME</th>
      </tr>
    <thead>
    <tbody>
    <?php
    while($r = $log->fetch()){
    ?>
    <tr>
        <td><?php echo $r["id"] ; ?></td>
        <td><?php echo $r["cardid"] ; ?></td>
        <td><?php echo $r["date"]; ?></td>
        <td><?php echo $r["intime"]; ?></td>
        <td><?php echo $r["outtime"]; ?></td>
    </tr>
    <?php } ?>
    </tbody>
  </table>


</body>
</html>