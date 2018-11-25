<?php
if (!empty($_GET)) {
	$id = $_GET["id"];
	echo $id;
}
?>

<form action="index.php" method="get">
	<input type="number" required value="0" placeholder="0" id="id"></input>
	<input type="submit" value="Open Lock"></input>
</form>