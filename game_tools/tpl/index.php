<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<form id="form1" name="form1" method="post" action="index.php">
  <p>
  <label><b> 模板生成工具 </b></label>
  </p>
  <p>
<input type="submit" name="UpdateDataBtn" id="UpdateDataBtn" value="单表导入" />&nbsp;&nbsp;&nbsp;&nbsp;<input type="text" id="inputTxt"  name="inputTxt" />
  </p>
  <p>
  <a href = "import_all.forbiden.php"><input type="button" name="UpdateDataAll" id="UpdateDataAll" value="全部导入" /></a>
  </p>
  
</form>

<?php
echo "<span style=\"color:#ff0000; font-size:35px;\"> For The Dream ... </span>" . "</br>";
echo "</br>";
echo "<span style=\"color:#00f000; font-size:24px;\"> 注意：全部导入只导入2小时之前修改的数据 </span>" . "</br>";
echo "</br>";

if(isset($_POST['inputTxt'])&&$_POST['inputTxt']!=null)
{
	$csvName=$_POST['inputTxt'].".csv";

	include_once("connect.php");
	$workpath = "/home/work";
	$tplpath = $workpath . "/tpl";
	$url = "http://192.168.5.185:7560/svn/tpl";
	$options = " --username leiyunfei --password leiyunfei --non-interactive ";
	echo "</br>";
	
	if(!file_exists($tplpath))
	{
		echo date("Y-m-d H:i:s") . "<span style=\"color:#00ff00; font-size:24px;\"> 检出模板数据文件 </span>" . "</br>";
		$cmd = "cd /home/work && svn checkout " . $url . $options . " tpl " . " 2>&1";
		$result = exec($cmd);
		echo nl2br($result) . "</br>";
		//exec("/bin/sh checkout.sh");
		exec("cd /home/work && chmod -R 777 tpl");
		exec("cd /home/wotk/tpl");
	}
	else 
	{
		$cmd = "cd /home/work/tpl && svn up " . $options . " 2>&1";
		$result = shell_exec($cmd);
		echo nl2br($result) . "</br>";
		//exec("/bin/sh update.sh");
		exec("cd /home/work && chmod -R 777 tpl");
		echo "</br>";
		echo date("Y-m-d H:i:s") . "<span style=\"color:#00ff00; font-size:24px;\"> 更新配置数据完毕！</span>" . "</br>";
	}

	if(is_dir($tplpath))
	{
		if($op = opendir($tplpath))
		{
			echo date("Y-m-d H:i:s") . "<span style=\"color:#00ff00; font-size:24px;\"> 开始导入csv数据到mysql数据！</span>";
			$csv = $tplpath . "/" . $csvName;
			$fp = fopen($csv, "r") or die("Can't open file" . $csv);
			echo "</br>";
			date_default_timezone_set('Asia/Chongqing');
					
			$num = strpos($csvName,'.');
			$tableName = substr($csvName,0,$num);
			
			$npcnum=0;
			$monnum=0;
			
			$sql = "truncate table ".$tableName;

			mysql_query($sql) or die(mysql_error());
		
			echo date("Y-m-d H:i:s") . "<span style=\"color:#00ff00; font-size:24px;\"> 正在导入数据表 </span>" . $talbeName . "</br>";
			echo "</br>";
			$row = 1;
			while($data = _fgetcsv ($fp))
			{
				$sql = "INSERT INTO `".$tableName."` VALUES(";
				$num = count($data);
				for ($i = 0;$i < $num; $i++)
				{
					$encode = mb_detect_encoding(addslashes($data[$i]),array('ASCII','CP936','GB2312','GBK','UTF-8')); 
					//$sql .= "'" . iconv($encode, "UTF-8", addslashes($data[$i])) . "',";
					//echo "编码: " . $encode;
					$str = mb_convert_encoding(addslashes($data[$i]), 'UTF-8', $encode);
					$sql .= "'" . $str . "',";
					
				}
				$sql = substr($sql, 0, -1);
				$sql .= ");";
				
				if($row === 1) {
					//第一行字段名
					//echo $sql;
				}
				else {
					echo $sql . "</br>";
					$query = mysql_query($sql) or die(mysql_error()."555");
					if(!$query)
					{
						echo date("[Y-m-d H:i:s]")."更新表".$tableName."错误";
						echo "</br>";
					}
				}
				$row++;
			}
			echo "</br>";
			echo date("Y-m-d H:i:s") . "<span style=\"color:#00ff00; font-size:24px;\"> 导入成功 </span>" . $talbeName . "</br>";
			echo "</br>";
			fclose($fp);
			echo date("Y-m-d H:i:s") . "<span style=\"color:#00ff00; font-size:24px;\"> ^_^ Congratulations !! </span>" . "</br>";
			echo "</br>";
		}
	}
}

function _fgetcsv(& $handle, $length = null, $d = ',', $e = '"') {
		 $d = preg_quote($d);
		 $e = preg_quote($e);
		 $_line = "";
		 $eof=false;
		 while ($eof != true) {
			 $_line .= (empty ($length) ? fgets($handle) : fgets($handle, $length));
			 $itemcnt = preg_match_all('/' . $e . '/', $_line, $dummy);
			 if ($itemcnt % 2 == 0)
				 $eof = true;
		 }
		 $_csv_line = preg_replace('/(?: |[ ])?$/', $d, trim($_line));
		 $_csv_pattern = '/(' . $e . '[^' . $e . ']*(?:' . $e . $e . '[^' . $e . ']*)*' . $e . '|[^' . $d . ']*)' . $d . '/';
		 preg_match_all($_csv_pattern, $_csv_line, $_csv_matches);
		 $_csv_data = $_csv_matches[1];
		 for ($_csv_i = 0; $_csv_i < count($_csv_data); $_csv_i++) {
			 $_csv_data[$_csv_i] = preg_replace('/^' . $e . '(.*)' . $e . '$/s', '$1' , $_csv_data[$_csv_i]);
			 $_csv_data[$_csv_i] = str_replace($e . $e, $e, $_csv_data[$_csv_i]);
		 }
		 return empty ($_line) ? false : $_csv_data;
}

echo "<span style=\"color:#ff0000; font-size:35px;\"> Happy Work, Happy Life ... </span>" . "</br>";
?>
