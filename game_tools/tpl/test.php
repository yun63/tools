<?php
echo "<span style=\"color:#00ff00;\"> Hello </span>";
exec("cd /home/work/ && /usr/bin/svn co svn://192.168.5.185/tpl tpl_tmp --username leiyunfei --password leiyunfei --non-interactive --no-auth-cache", $result);
echo $result;
?>
