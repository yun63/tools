
#!/bin/bash
SHELL_FOLDER=$(cd `dirname ${0}`; pwd)
BINDIR=$(cd ${SHELL_FOLDER}/bin/; pwd)
cd ${SHELL_FOLDER}
echo "shutdown" | ${BINDIR}/redis-cli -p 6379 > /dev/null 2>&1
sleep 1
nohup ${BINDIR}/redis-server ${SHELL_FOLDER}/conf/master-6379.conf > ${SHELL_FOLDER}/data/redis-6379.log 2>&1 &
echo "done"
