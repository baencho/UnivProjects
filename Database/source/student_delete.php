<?
$connect = dbconnect($host, $dbid, $dbpass, $dbname);

$s_id = $_GET['s_id'];

mysqli_query("set autocommit = 0", $connect);
mysqli_query("set transaction isolation level serializable", $connect);
mysqli_query("start", $connect);

$ret = mysqli_query($conn, "delete from student where s_id = '$s_id'");

if($ret){
  mysqli_query("commit", $conn);
  s_msg("성공적으로 삭제 되었습니다.");
  echo "<meta http-equiv='refresh' content = '0;url=student_list.php'>";
} else {
  mysqli_query("rollback", $conn);
  s_msg("삭제에 실패하였습니다. 다시 시도하여 주십시오.");
  echo "<meta http-equiv='refresh' content = '0;url=student_list.php'>";
}?>
