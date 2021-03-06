<?php
require_once 'db.php';

if (!empty($_GET)) {
	$id = $_GET["id"];
	
	$query = "
		INSERT INTO commands (data)
		VALUES ({$id});
	";

	$queryRet = $db->exec($query);
	if(!$queryRet) {
	    echo $db->lastErrorMsg();
	} else {
	    echo "<script>alert('Command Sent!');</script>";
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

		<title>Combination Lock Opener</title>
	</head>
	<body>
		<div id="header">
			<div class="headerItem activeHeader" id="leftItem">
				<a href="index.php">Home</a>
			</div>
			<div class="headerItem" id="rightItem">
				<a href="config.php">Config</a>
			</div>
		</div>

		<div id="body">
			<form action="index.php" method="get">
				<div class="form-group">
					<label for="idSelect">Select Lock:</label>
					<select required class="form-control formInput" id="id" name="id">
						<?php
							foreach ($ids as $val) {
								echo "<option>{$val}</option>";
							}
						?>
					</select>
					<input type="submit" value="Open Lock" class="btn btn-success formInput"></input>
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