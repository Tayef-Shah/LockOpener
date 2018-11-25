<?php
   class DataDB extends SQLite3 {
      function __construct() {
         $this->open('../database/test.db');
      }
   }
   $db = new MyDB();
   if(!$db) {
      echo $db->lastErrorMsg();
   } else {
      echo "Opened database successfully\n";
   }
?>