#!/bin/bash
root=`cd $(dirname $0); pwd`
echo $root
cd $root
svn st | grep ? | awk '{print $2}' | xargs svn add
svn ci -m "add new files"
