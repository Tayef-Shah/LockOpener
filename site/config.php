<?php
if (!empty($_GET)) {
	$id = $_GET["id"];
	$num1 = $_GET["num1"];
	$num2 = $_GET["num2"];
	$num3 = $_GET["num3"];
	echo $id;
}
?>

<form action="config.php" method="get">
	<input type="number" required id="id" value="0" placeholder="0"></input>
	<input type="number" required id="num1" placeholder="xx"></input>
	<input type="number" required id="num2" placeholder="xx"></input>
	<input type="number" required id="num3" placeholder="xx"></input>
	<input type="submit" value="Save Combination"></input>
</form>