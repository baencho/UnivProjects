<?
$connect = dbconnect($host, $dbid, $dbpass, $dbname);
$query = "select * from student";
if (array_key_exists("search_keyword", $_POST)){
  $search_keyword = $_POST["search_keyword"];
  $query = $query . " where s_name like '%$search_keyword%'";
}

mysqli_query("set autocommit = 0", $connect);
mysqli_query("set transaction isolation level serializable", $connect);
mysqli_query("start", $connect);
$res = mysqli_query($connect, $query);
if($res){
  mysqli_query("commit", $connect);
} else {
  mysqli_query("rollback", $connect);
  s_msg("검색에 실패하였습니다."); echo "<meta http-equiv='refresh' content = '0;url=student_list.php'>";

}?>
