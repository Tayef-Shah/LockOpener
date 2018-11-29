<?php
require_once 'db.php';

// Update Lock
if (!empty($_GET)) {
	$id = $_GET["id"];
	$num1 = $_GET["num1"];
	$num2 = $_GET["num2"] + 2;
	$num3 = $_GET["num3"] - 1;

	if ($num3 < 0) {
		$num3 = 0;
	}

	$query = "
		INSERT OR REPLACE INTO data (id, num1, num2, num3)
		VALUES ({$id}, {$num1}, {$num2}, {$num3});
	";

	$queryRet = $db->exec($query);
	if(!$queryRet) {
	    die($db->lastErrorMsg());
	} else {
	    echo "<script>alert('Data for lock #{$id} has been updated!');</script>";
	}

// Create Lock
} else if (!empty($_POST)) {
	$nextId = $_POST["createLock"];
	$query = "
		INSERT OR REPLACE INTO data (id, num1, num2, num3)
		VALUES ({$nextId}, 0,0,0);
	";

	$queryRet = $db->exec($query);
	if(!$queryRet) {
		die($db->lastErrorMsg());
	} else {
		echo "<script>alert('Lock #{$nextId} has been created!');</script>";
	}
}

// Grab Existing Locks
$ids = array();
$lastId = -1;

$query = "SELECT id FROM data;";
$select = $db->query($query);
while ($row = $select->fetchArray(SQLITE3_ASSOC)) {
	$ids[] = $row["id"];
	if ($row["id"] > $lastId) {
		$lastId = $row["id"];
	}
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
		
			<form action="config.php" method="post">
				<input type="hidden" id="createLock" name="createLock" value="<?php echo ($lastId + 1); ?>">
				<div class="form-group">
					<input type="submit" value="Create New Lock" class="btn btn-info formInput"></input>
				</div>
			</form>
			<hr/>
			<form action="config.php" method="get">
				<div class="form-group">
					<label for="idSelect">Select Lock:</label>
					<select required class="form-control formInput" id="id" name="id">
						<?php
							foreach ($ids as $val) {
								echo "<option>{$val}</option>";
							}
						?>
					</select>
				</div>
				<div class="form-group">
					<label for="num1">1st Number:</label>
					<input type="number" min="0" required class="form-control formInput" id="num1" name="num1" placeholder="(eg. 34)">
				</div>
				<div class="form-group">
					<label for="num2">2nd Number:</label>
					<input type="number" min="0" required class="form-control formInput" id="num2" name="num2" placeholder="(eg. 16)">
				</div>
				<div class="form-group">
					<label for="num3">3rd Number:</label>
					<input type="number" min="0" required class="form-control formInput" id="num3" name="num3" placeholder="(eg. 22)">
				</div>
				<div class="form-group">
					<input type="submit" value="Update Combination" class="btn btn-success formInput"></input>
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