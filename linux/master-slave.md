������װ���ӷ�������ȷ��������������log-bin�����ӷ�������server_idȡ��ͬ�����֡�

mysql ����ͬ���� ԭ����� ��ͨ��io thread ��ȡ����binlog��־��Ȼ�������־��д

----------------------------------------------------------------------------------------------------------------------------------
һ���޸������ļ�
1��������������
auto_increment_increment=10
auto_increment_offset=5
innodb_flush_log_at_trx_commit=1
------------------------------------------------
log-slave-update  //�Ѹ��µļ�¼д���������ļ���,ͬʱҲΪ�˸��õķ����� m-m + s �Ļ�������֤slave�����κ�һ̨master�϶�����յ���һ��master��д����Ϣ����Ȼ������������ܹ����������Ƶļܹ�ͬ��Ҳ��Ҫlog-slave-updates��֧��
slave-skip-errors //�������󣬼���ִ�и��ƣ�
--slave-skip-errors=1062,1053 //ָ�����Ե��e�`ӍϢ
--slave-skip-errors=all //��������Ե������e�`ӍϢ
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
#binlog-do-db=��Ҫ���ݵ����ݿ�������д����
#binlog-ignore-db=����Ҫ���ݵ����ݿ�������д����
------------------------------------------------------------------------------
2���ӷ���������:
server-id = 2
#log-bin = mysql-bin
relay_log=mysql-relay-bin
----------------------
skip_slave_start    #��ֹ�������ڱ�����������
master-connect-retry=60 //������������������ߣ��������ӵ�ʱ�� 
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

����master
   1�������û���
	mysql>grant replication slave on *.* to replication@'192.168.80.221' identified by 'GLLeu0Ev3jXK';
	mysql>flush privileges;
    
    2������ֻ��
	mysql>flush tables with read lock;
    
    3���������ݿ�
	#mysqldump -uroot -p`cat /data/save/mysql_root` --single-transaction --master-data=2 --databases mob_game_4399_s0 mob_manage_4399_s0  --events --routines --triggers > .sql

    4���鿴��������־����ƫ����ֵ
	mysql>show master status\G;

����slave����master.info�ļ����棬���ļ����ȼ�����my.cnf
	mysql>slave stop;
	mysql>change master to  MASTER_HOST='192.168.42.9', MASTER_PORT=3306, MASTER_USER='replication', MASTER_PASSWORD='GLLeu0Ev3jXK', MASTER_LOG_FILE='mysql-bin.000005', MASTER_LOG_POS=107;
	mysql>slave start;
	mysql> show processlist
	10436 | system user ... | waiting for master to send event | NULL
	##������������Ϣ����slave�Ѿ�������master������ʼ���ղ�ִ����־�ˡ�

	mysql>show slave status\G
	���Ƿ������������в��ԣ�

�ġ�master�����ö�����
mysql> unlock tables;

----------------------------------------------------------------------------------------------------------------------------------
̨��
����master
   1�������û���
	mysql>grant replication slave on *.* to replication@'10.1.3.50' identified by 'GLLeu0Ev3jXK';
	mysql>flush privileges;
    
    2������ֻ��
	mysql>flush tables with read lock;
    
    3���������ݿ�
	#mysqldump -uroot -p`cat /data/save/mysql_root` --single-transaction --master-data=2 --databases mob_game_4399_s0 mob_manage_4399_s0  --events --routines --triggers > .sql

    4���鿴��������־����ƫ����ֵ
	mysql>show master status\G;

����slave����master.info�ļ����棬���ļ����ȼ�����my.cnf
	mysql>slave stop;
	mysql>change master to  MASTER_HOST='10.1.3.42', MASTER_PORT=3306, MASTER_USER='replication', MASTER_PASSWORD='GLLeu0Ev3jXK', MASTER_LOG_FILE='mysql-bin.000005', MASTER_LOG_POS=107;
	mysql>slave start;
	mysql> show processlist
	10436 | system user ... | waiting for master to send event | NULL
	##������������Ϣ����slave�Ѿ�������master������ʼ���ղ�ִ����־�ˡ�

	mysql>show slave status\G
	���Ƿ������������в��ԣ�

�ġ�master�����ö�����
mysql> unlock tables;
----------------------------------------------------------------------------------------------------------------------------------