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
	    echo "<script>alert('Data for lock #{$id} has been updated!');</script>";
	}
}

// Grab Existing Locks
$ids = array();

$query = "SELECT id FROM data;";
$select = $db->query($query);
while ($row = $select->fetchArray(SQLITE3_ASSOC)) {
	$ids[] = $row["id"];
}

$db->close();

?>

<!doctype html>
<html lang="en">
	<head>
		<!-- Required meta tags -->
		<meta charset="utf-8">
		<meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

		<!-- Bootstrap CSS -->
		<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
		<link href="https://fonts.googleapis.com/css?family=Open+Sans" rel="stylesheet">
		<link rel="stylesheet" href="src/style.css">

		<title>Combination Lock Opener | Configuration</title>
	</head>
	<body>
		<div id="header">
			<div class="headerItem" id="leftItem">
				<a href="index.php">Home</a>
			</div>
			<div class="headerItem activeHeader" id="rightItem">
				<a href="config.php">Config</a>
			</div>
		</div>

		<div id="body">
			<form action="config.php" method="get">
				<div class="form-group">
					<label for="num1">1st Number:</label>
					<input type="number" required class="form-control" id="num1" name="num1" placeholder="(eg. 34)">
				</div>
				<div class="form-group">
					<label for="num2">2nd Number:</label>
					<input type="number" required class="form-control" id="num2" name="num2" placeholder="(eg. 16)">
				</div>
				<div class="form-group">
					<label for="num3">3rd Number:</label>
					<input type="number" required class="form-control" id="num3" name="num3" placeholder="(eg. 22)">
				</div>
				<div class="form-group">
					<input type="submit" value="Update Combination" class="btn btn-success indexForm"></input>
				</div>
			</form>
		</div>

		<!-- Optional JavaScript -->
		<!-- jQuery first, then Popper.js, then Bootstrap JS -->
		<script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
		<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
		<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
		<script src="src/script.js"></script>
	</body>
</html>