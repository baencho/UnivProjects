<?
$connect = dbconnect($host, $dbid, $dbpass, $dbname);
$mode = "등록";
$action = "student_insert.php";

if (array_key_exists("s_id", $_GET)){
  $s_id = $_GET["s_id"];
  mysqli_query("set autocommit = 0", $connect);
  mysqli_query("set transaction isolation level serializable", $connect);
  mysqli_query("start", $connect);
  $query ="select * from student where s_id = $s_id";
  $res = mysqli_query($connect, $query);
  if($res){
    mysqli_query("commit", $connect);
    $student = mysqli_fetch_array($res);
    if(!$student){
      msg("해당 학생이 존재하지 않습니다.");
    }

    $mode = "수정";
    $action = "student_modify.php";
  } else {
    mysqli_query("rollback", $connect);
    s_msg("해당 학생이 존재하지 않습니다. 다시 시도하여 주십시오.");
    echo "<meta http-equiv='refresh' content = '0;url=student_list.php'>";
}
}?>
