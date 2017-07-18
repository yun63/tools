import sys

template= sys.argv[1]
port = int(sys.argv[2])

tf = open(template, 'r')
tls = tf.readlines()
tf.close()

confstr = ''.join(tls)
head='master'
if template.find('master') >= 0 :
    confstr = confstr % (port, port, port, port, port)
else:
    head='slave'
    masterip = sys.argv[3]
    confstr = confstr % (port, port, port, port, masterip, port, port)

f = open('./conf/%s-%d.conf' % (head, port), 'w')
f.write(confstr)
f.close()

shstr='''
#!/bin/bash
SHELL_FOLDER=$(cd `dirname ${0}`; pwd)
BINDIR=$(cd ${SHELL_FOLDER}/bin/; pwd)
cd ${SHELL_FOLDER}
echo "shutdown" | ${BINDIR}/redis-cli -p %d > /dev/null 2>&1
sleep 1
nohup ${BINDIR}/redis-server ${SHELL_FOLDER}/conf/%s-%d.conf > ${SHELL_FOLDER}/data/redis-%d.log 2>&1 &
echo "done"
''' % (port, head, port, port)

f = open('./%s-%d.sh' % (head, port), 'w')
f.write(shstr)
f.close()

import commands
commands.getoutput('chmod +x ./%s-%d.sh' % (head, port))

