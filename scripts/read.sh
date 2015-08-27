#!/bin/bash

select=1
read -p "Please select the web of nginx/apache, input 1 or 2: " select
if [ "$select" == "1" ]; then
    web=nginx
elif [ "$select" == "2" ]; then
    web=apache
fi

select=1
if echo $web | grep "nginx" > /dev/null; then
    read -p "Please select the nginx version of 1.4.4, input 1: " select
    if [ "$select" == "1" ]; then
        nginx_version=1.4.4
    fi
else
    read -t 5 -p "Please select the apache version of 2.2.29/2.4.10, input 1 or 2: " select
    if [ "$select" == "1" ]; then
        httpd_version=2.2.29
    elif [ "$select" == "2" ]; then
        httpd_version=2.4.10
    fi
fi

echo ""
echo "You select the version: "
echo "web       : $web"
if echo $web | grep "nginx" > /dev/null; then
    echo "nginx     :$nginx_version"
else
    echo "apache    :$httpd_version"
fi

read -t 10 -p "Enter the Y/Yes to continue: " isY
if [ "${isY}" != "Y" ] && [ "${IsY}" != "Yes" ]; then
    exit 1
fi
