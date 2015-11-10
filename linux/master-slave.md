正常安装主从服务器。确保主服务器开启log-bin，主从服务器的server_id取不同的数字。

mysql 主从同步的 原理就是 从通过io thread 读取主的binlog日志，然后进行日志重写

----------------------------------------------------------------------------------------------------------------------------------
一、修改配置文件
1，主服务器配置
auto_increment_increment=10
auto_increment_offset=5
innodb_flush_log_at_trx_commit=1
------------------------------------------------
log-slave-update  //把更新的记录写到二进制文件中,同时也为了更好的服务于 m-m + s 的环境，保证slave挂在任何一台master上都会接收到另一个master的写入信息。当然不局限于这个架构，级联复制的架构同样也需要log-slave-updates的支持
slave-skip-errors //跳过错误，继续执行复制；
--slave-skip-errors=1062,1053 //指定忽略的錯誤訊息
--slave-skip-errors=all //代表會忽略掉所有錯誤訊息
mysql> show variables like "%slave%";
sync-binlog=1
--------------------------------------------
server-id = 1
log-bin=mysql-bin
expire_logs_days=3
binlog_format=mixed
max-binlog-size=128M
binlog_cache_size = 4M
-----------------------------
skip-slave-start=1
binlog-ignore-db=mysql
binlog-ignore-db=test
binlog-ignore-db=information_schema
binlog-ignore-db=performance_schema
#binlog-do-db=需要备份的数据库名，可写多行
#binlog-ignore-db=不需要备份的数据库名，可写多行
------------------------------------------------------------------------------
2，从服务器配置:
server-id = 2
#log-bin = mysql-bin
relay_log=mysql-relay-bin
----------------------
skip_slave_start    #阻止服务器在崩溃后自启动
master-connect-retry=60 //如果发现主服务器断线，重新连接的时间差； 
replicate-ignore-db=mysql
replicate-ignore-db=test
replicate-ignore-db=information_schema
replicate-ignore-db=performance_schema
----------------------
log-slave-update 
slave-skip-errors
sync_binlog=1
auto_increment_increment=2
auto_increment_offset=1
----------------------------------------------------------------------------------------------------------------------------------

二、master
   1、建立用户：
	mysql>grant replication slave on *.* to replication@'192.168.80.221' identified by 'GLLeu0Ev3jXK';
	mysql>flush privileges;
    
    2、锁表、只读
	mysql>flush tables with read lock;
    
    3、备份数据库
	#mysqldump -uroot -p`cat /data/save/mysql_root` --single-transaction --master-data=2 --databases mob_game_4399_s0 mob_manage_4399_s0  --events --routines --triggers > .sql

    4、查看二进制日志名和偏移量值
	mysql>show master status\G;

三、slave：以master.info文件保存，此文件优先级高于my.cnf
	mysql>slave stop;
	mysql>change master to  MASTER_HOST='192.168.42.9', MASTER_PORT=3306, MASTER_USER='replication', MASTER_PASSWORD='GLLeu0Ev3jXK', MASTER_LOG_FILE='mysql-bin.000005', MASTER_LOG_POS=107;
	mysql>slave start;
	mysql> show processlist
	10436 | system user ... | waiting for master to send event | NULL
	##若有这样的信息表明slave已经连接上master，并开始接收并执行日志了。

	mysql>show slave status\G
	看是否正常，并进行测试；

四、master：重置读锁定
mysql> unlock tables;

----------------------------------------------------------------------------------------------------------------------------------
台湾
二、master
   1、建立用户：
	mysql>grant replication slave on *.* to replication@'10.1.3.50' identified by 'GLLeu0Ev3jXK';
	mysql>flush privileges;
    
    2、锁表、只读
	mysql>flush tables with read lock;
    
    3、备份数据库
	#mysqldump -uroot -p`cat /data/save/mysql_root` --single-transaction --master-data=2 --databases mob_game_4399_s0 mob_manage_4399_s0  --events --routines --triggers > .sql

    4、查看二进制日志名和偏移量值
	mysql>show master status\G;

三、slave：以master.info文件保存，此文件优先级高于my.cnf
	mysql>slave stop;
	mysql>change master to  MASTER_HOST='10.1.3.42', MASTER_PORT=3306, MASTER_USER='replication', MASTER_PASSWORD='GLLeu0Ev3jXK', MASTER_LOG_FILE='mysql-bin.000005', MASTER_LOG_POS=107;
	mysql>slave start;
	mysql> show processlist
	10436 | system user ... | waiting for master to send event | NULL
	##若有这样的信息表明slave已经连接上master，并开始接收并执行日志了。

	mysql>show slave status\G
	看是否正常，并进行测试；

四、master：重置读锁定
mysql> unlock tables;
----------------------------------------------------------------------------------------------------------------------------------