<?php
	// Open Database
	class DB extends SQLite3 {
		function __construct() {
			$this->open('../database/opener.db3');
		}
	}
	$db = new DB();
	if(!$db) {
		die($db->lastErrorMsg());
	}

	// Create Tables (if not exists)
	// Data table, this is for user config
	$sql =<<<EOF
	CREATE TABLE IF NOT EXISTS data (
        id INT(32) PRIMARY KEY UNIQUE,
        num1 INT(32),
        num2 INT(32),
        num3 INT(32)
    );
EOF;
   $ret = $db->exec($sql);
   if(!$ret){
      die($db->lastErrorMsg());
   }

   // Log table
   	$sql =<<<EOF
	CREATE TABLE IF NOT EXISTS log (
        id INT(32) PRIMARY KEY UNIQUE,
        data TEXT,
        time TIME DEFAULT (CURRENT_TIME) 
    );
EOF;
   $ret = $db->exec($sql);
   if(!$ret){
      die($db->lastErrorMsg());
   }

   // Command Queue table
   	$sql =<<<EOF
	CREATE TABLE IF NOT EXISTS commands (
        id INT(32) PRIMARY KEY UNIQUE,
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