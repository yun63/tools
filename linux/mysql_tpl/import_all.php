<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<?php 
include_once("connect.php");

$tplpath = "/home/work/tpl";
echo "<span style=\"color:#ff0000; font-size:35px;\"> For The Dream ... </span>" . "</br>";
echo "</br>";

$workpath = "/home/work";
$tplpath = $workpath . "/tpl";
$url = "http://192.168.5.185:7560/svn/tpl";
$options = " --username leiyunfei --password leiyunfei --non-interactive --no-auth-cache ";

echo date("Y-m-d H:i:s") . "<span style=\"color:#00ff00; font-size:24px;\"> 正在更新配置数据！</span>";
echo "</br>";

if(!file_exists($tplpath))
{
	echo date("Y-m-d H:i:s") . "<span style=\"color:#00ff00; font-size:24px;\"> 检出模板数据文件 </span>" . "</br>";

	$cmd = "cd /home/work && /usr/bin/svn co " . $url . $options . " tpl";
	$result = shell_exec($cmd);
	echo nl2br($result);
	exec("cd /home/work && chmod -R 777 tpl");
	echo "</br>";
}

$cmd = "cd /home/work/tpl && /usr/bin/svn up " . $options;
$result = shell_exec($cmd);
shell_exec("cd /home/work && chmod -R 777 tpl");
echo nl2br($result);
echo "</br>";
echo date("Y-m-d H:i:s")."<span style=\"color:#00ff00; font-size:24px;\"> 更新配置数据完毕！</span>" . "</br>";

if(is_dir($tplpath))
{
	if($op = opendir($tplpath))
	{
		echo "</br>";
		echo date("Y-m-d H:i:s") . "<span style=\"color:#00ff00; font-size:24px;\"> 开始导入tpl数据 </span>" . "</br>";
		echo "</br>";
		while(($csvName = readdir($op)) !== false)
		{
			if ($csvName!='.' && $csvName!='..'&& $csvName!='.svn')
			{
				if(!preg_match('/\\.(csv)$/i', $csvName))
				{
					//echo date("[Y-m-d H:i:s]")."[".$csvName."]该文件为非法的CSV格式";
					continue;
				}
				//setlocale(LC_ALL, 'en_US.UTF-8');
				//setlocale(LC_ALL, 'zh_CN.UTF-8'); 
				$fp = fopen($tplpath.'/'.$csvName,'r');
				if(!$fp)
				{
					echo date("[Y-m-d H:i:s]")."[".$csvName."]打开文件出错！";
					echo "</br>";
				}

				date_default_timezone_set('Asia/Chongqing');

				$lastFileTime = filemtime($tplpath.'/'.$csvName);
				$nowTime = time();

				if($lastFileTime+7200>=$nowTime)
				{
					$num = strpos($csvName,'.');				
					$tableName = substr($csvName,0,$num);

					$npcnum=0;
					$monnum=0;
					$sql = "truncate table ".$tableName;
					mysql_query($sql) or mysql_error();
					$var = "<span style=\"color:#00ffff; font-size:24px;\"> $tableName </span>";
					echo date("Y-m-d H:i:s") . "<span style=\"color:#00ff00; font-size:24px;\"> 开始导入</span>" . $var;
					echo "</br>";
					$row=1;
					while($data = _fgetcsv ($fp))
					{
						$sql = "INSERT INTO `".$tableName."` VALUES(";
						$num = count($data);
						for($i=0;$i<$num;$i++)
						{
							$sql.="'".iconv("GBK","UTF-8",addslashes($data[$i]))."',";
						}						
						$sql = substr($sql,0,-1);
						$sql.=");";						

						if($row === 1)
						{
							//第一行字段名
							continue;
						}
						else
						{
							$query = mysql_query($sql);
							if(!$query)
							{
								echo date("[Y-m-d H:i:s]")."更新表".$tableName."错误";
								echo "</br>";
							}
						}
						$row++;
					}
					echo "</br>";
					fclose($fp);
				}
			}

		}
		echo date("Y-m-d H:i:s") . "<span style=\"color:#00ff00; font-size:24px;\"> 数据表已经全部导入完毕! </span>" . "</br>";
		echo "</br>";
		echo "<span style=\"color:#ff0000; font-size:35px;\"> Happy Work, Happy Life ... </span>" . "</br>";
		echo "</br>";
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
?>

<a href="index.php">返回</a>
