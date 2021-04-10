<?
$connect = dbconnect($host, $dbid, $dbpass, $dbname);

$score = $_POST['score'];
$c_id = $_POST['c_id'];
$count = $_POST['count'];
$c_name = $_POST['c_name'];

mysqli_query("set autocommit = 0", $connect);
mysqli_query("set transaction isolation level serializable", $connect);
mysqli_query("start", $connect);
$query = "select s_id, c_id from register natural join student where c_id = '$c_id'";
$res = mysqli_query($connect, $query);
if(!$res){
  mysqli_query("rollback", $connect);
  s_msg("입력 도중 문제가 발생했습니다.");
  echo "<meta http-equiv='refresh' content = '0;url=score_list.php'>";
}
while($row = mysqli_fetch_array($res)){
  $sid = $row['s_id'];
  $input = $score[$row['s_id']];
  $qry = "update register set $index = $input where c_id = $c_id and s_id = $sid";
  $exe = mysqli_query($connect, $qry);
}

if($exe){
  mysqli_query("commit", $connect);
  s_msg("성공적으로 입력되었습니다.");
  echo "<meta http-equiv='refresh' content='0;url=score_list.php?c_id=$c_id&c_name=$c_name'>";
}else{
  mysqli_query("rollback", $connect);
  s_msg("입력에 실패했습니다. 다시 시도하여 주십시오.")ㅣ
  echo "<meta http-equiv='refresh' content='0;url=score_list.php'>";
}

?>
