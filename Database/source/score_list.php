<?
$connect = dbconnect($host, $dbid, $dbpass, $dbname);
$query = "select * from register natural join student";
$c_id = $_GET["c_id"];
$c_name = $_GET["c_name"];
$query = $query . "where c_id like '%$c_id%'";

mysqli_query("set autocommit = 0", $connect);
mysqli_query("set transaction isolation level read committed", $connect);
mysqli_query("start", $connect);
$res = mysqli_query($connect, $query);
if($res){
  mysqli_query("commit", $connect);
} else {
  mysqli_query("rollback", $connect);
  s_msg("검색에 실패하였습니다."); echo "<meta http-equiv='refresh' content = '0;url=register_list.php'>";

}?>
