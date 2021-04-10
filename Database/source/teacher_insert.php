<?
$connect = dbconnect($host, $dbid, $dbpass, $dbname);

$t_id = $_POST['t_id'];
$t_name = $_POST['t_name'];
$t_phone = $_POST['t_phone'];
$password = $_POST['password'];

mysqli_query("set autocommit = 0", $connect);
mysqli_query("set transaction isolation level serializable", $connect);
mysqli_query("start", $connect);
$ret = mysqli_query($connect, "insert into teacher (t_id, t_name, t_phone, t_password) values('$t_id', '$t_name', '$t_phone', '$password')");
if($ret){
  mysqli_query("commit", $connect);
  s_msg("성공적으로 입력 되었습니다.");
  echo "<meta http-equiv='refresh' content = '0;url=teacher_list.php'>";

} else {
  mysqli_query("rollback", $connect);
  s_msg("입력에 실패하였습니다. 다시 시도하여 주십시오.");
  echo "<meta http-equiv='refresh' content = '0;url=teacher_list.php'>";
}?>
