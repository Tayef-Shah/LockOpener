<?php
	// Open Database
	class DB extends SQLite3 {
		function __construct() {
			$this->open('database/db.db3');
		}
	}
	$db = new DB();
	if(!$db) {
		die($db->lastErrorMsg());
	}

	// Create Tables (if not exists)
	$sql =<<<EOF
	CREATE TABLE IF NOT EXISTS data (
        id INTEGER PRIMARY KEY UNIQUE,
        num1 INT(32),
        num2 INT(32),
        num3 INT(32)
    );
	
	CREATE TABLE IF NOT EXISTS log (
        id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
        data TEXT,
        time TIME DEFAULT (CURRENT_TIME) 
    );
	
	CREATE TABLE IF NOT EXISTS commands (
        id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
        data TEXT,
        time TIME DEFAULT (CURRENT_TIME) 
    );
EOF;
   $ret = $db->exec($sql);
   if(!$ret){
      die($db->lastErrorMsg());
   }

   echo "Yeah!";

?>