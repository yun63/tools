<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<?php
//$conn = mysql_connect("localhost","admin","admin") or die("Could not connect:".$mysql_error());
//mysql_select_db("test");
$conn = mysql_connect("localhost","watchdog","watchdog") or die("Could not connect:".$mysql_error());
mysql_select_db("game_tpl");
mysql_query("set names utf8");
//mysql_close($conn);

?>
