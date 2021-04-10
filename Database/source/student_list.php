<?
$connect = dbconnect($host, $dbid, $dbpass, $dbname);
$query = "select * from register natural join student where c_id = $c_id";
mysqli_query("set autocommit = 0", $connect);
mysqli_query("set transaction isolation level read committed", $connect);
mysqli_query("start", $connect);
$res = mysqli_query($connect, $query);
mysqli_query("commit", $connect);
?>
