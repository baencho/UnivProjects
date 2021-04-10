<?
$connect = dbconnect($host, $dbid, $dbpass, $dbname);
$action = "books.php";
$query = "select * from textbook";
if (array_key_exists("selection", $_GET)){
  $c_id = $_GET["selection"];
  $query = $query."where c_id = $c_id";
}

mysqli_query("set autocommit = 0", $connect);
mysqli_query("set transaction isolation level read uncommitted", $connect);
mysqli_query("start", $connect);
$res = mysqli_query($connect, $query);
$class = array();

$queryc = "select * from class";
$resc = mysqli_query($connect, $queryc);
while($rowc = mysqli_fetch_array($resc)){
  $class[$rowc['c_id']] = $rowc['c_name'];
}

if($res&&$resc){
  mysqli_query("commit", $connect);
} else {
  mysqli_query("rollback", $connect);
  s_msg("검색에 실패하였습니다."); echo "<meta http-equiv='refresh' content = '0;url=book_list.php'>";

}?>
