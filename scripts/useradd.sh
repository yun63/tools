#!/bin/bash 
key_folder=`pwd` 
if [ $# == 1 ] 
then 
        keypath="$key_folder/id_rsa.$1" 
        read -p "Input your id_rsa passwd:(数字特殊符号以及字母大于6位)" -s passwd 
        echo 
        echo 
        read -p "Please Input passwd again:" -s passswd 
        if [ $passwd == $passswd ];then 
                echo "successful!,please remember your passwd" 
                if [ ! -f "$keypath" ];then 
                        /usr/bin/ssh-keygen -b 1024 -t rsa -N $passwd -f ${keypath} 
                        echo $1 >> $key_folder/id_rsa.$1.pub 
                        nc 192.168.10.29 9999 < $key_folder/id_rsa.$1.pub 
                        echo "你的新私钥在 $keypath 下,请注意保管！" 
                fi 
        else 
                echo "你两次输入的密码不一致！！" 
        fi 
else 
        echo "input your username" 
fi 
