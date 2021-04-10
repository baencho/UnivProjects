<?
$connect = dbconnect($host, $dbid, $dbpass, $dbname);

$s_id = $_POST['s_id'];
$s_name = $_POST['s_name'];
$s_phone = $_POST['s_phone'];

mysqli_query("set autocommit = 0", $connect);
mysqli_query("set transaction isolation level serializable", $connect);
mysqli_query("start", $connect);

$ret = mysqli_query($conn, "update student set s_name = \"$s_name\",
s_phone =\"$s_phone\" where s_id = \"$s_id\"");

if($ret){
  mysqli_query("commit", $conn);
  s_msg("성공적으로 수정 되었습니다.");
  echo "<meta http-equiv='refresh' content = '0;url=student_list.php'>";
} else {
  mysqli_query("rollback", $conn);
  s_msg("수정에 실패하였습니다. 다시 시도하여 주십시오.");
  echo "<meta http-equiv='refresh' content = '0;url=student_list.php'>";
}?>
