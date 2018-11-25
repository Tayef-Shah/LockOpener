<?php
require_once 'db.php';

if (!empty($_GET)) {
	$id = $_GET["id"];
	$num1 = $_GET["num1"];
	$num2 = $_GET["num2"];
	$num3 = $_GET["num3"];

	$query = "
		INSERT OR REPLACE INTO data (id, num1, num2, num3)
		VALUES ({$id}, {$num1}, {$num2}, {$num3});
	";

	$queryRet = $db->exec($query);
	if(!$queryRet) {
	    echo $db->lastErrorMsg();
	} else {
	    echo "Upserted data for {$id}";
	}
	$db->close();
}
?>

<form action="config.php" method="get">
	<input type="number" required name="id" value="0" placeholder="0"></input>
	<input type="number" required name="num1" placeholder="xx"></input>
	<input type="number" required name="num2" placeholder="xx"></input>
	<input type="number" required name="num3" placeholder="xx"></input>
	<input type="submit" value="Save Combination"></input>
</form>