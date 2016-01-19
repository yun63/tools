#!/bin/bash
cd ${PWD}
svn st | grep ? | awk '{print $2}' | xargs svn add
svn ci -m "add new files"
