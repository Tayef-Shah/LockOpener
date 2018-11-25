<?php
require_once 'db.php';

if (!empty($_GET)) {
	$id = $_GET["id"];
	$command = "OPEN " + $id;
	
	$query = "
		INSERT INTO commands (data)
		VALUES ('{$command}');
	";

	$queryRet = $db->exec($query);
	if(!$queryRet) {
	    echo $db->lastErrorMsg();
	} else {
	    echo "Command Sent\n";
	}
	$db->close();
}
?>

<form action="index.php" method="get">
	<input type="number" required value="0" placeholder="0" name="id"></input>
	<input type="submit" value="Open Lock"></input>
</form>