<?
$connect = dbconnect($host, $dbid, $dbpass, $dbname);
$mode = "등록";
$action = "teacher_insert.php";

if (array_key_exists("s_id", $_GET)){
  $t_id = $_GET["t_id"];
  mysqli_query("set autocommit = 0", $connect);
  mysqli_query("set transaction isolation level serializable", $connect);
  mysqli_query("start", $connect);
  $query ="select * from teacher where t_id = $t_id";
  $res = mysqli_query($connect, $query);
  if($res){
    mysqli_query("commit", $connect);
    $teacher = mysqli_fetch_array($res);
    if(!$teacher){
      msg("해당 선생님이 존재하지 않습니다.");
    }

    $mode = "수정";
    $action = "teacher_modify.php";
  } else {
    mysqli_query("rollback", $connect);
    s_msg("해당 선생님이 존재하지 않습니다. 다시 시도하여 주십시오.");
    echo "<meta http-equiv='refresh' content = '0;url=teacher_list.php'>";
  }
}?>
