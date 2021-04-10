<?
$connect = dbconnect($host, $dbid, $dbpass, $dbname);

$t_id = $_GET['t_id'];

mysqli_query("set autocommit = 0", $connect);
mysqli_query("set transaction isolation level serializable", $connect);
mysqli_query("start", $connect);

$ret = mysqli_query($connect, "delete from teacher where t_id = '$t_id'");

if($ret){
  mysqli_query("commit", $connect);
  s_msg("성공적으로 삭제 되었습니다.");
  echo "<meta http-equiv='refresh' content = '0;url=teacher_list.php'>";
} else {
  mysqli_query("rollback", $connect);
  s_msg("삭제에 실패하였습니다. 다시 시도하여 주십시오.");
  echo "<meta http-equiv='refresh' content = '0;url=teacher_list.php'>";
}?>
