#!/bin/bash
cd ${PWD}
svn st | grep ! | awk '{print $2}' | xargs svn delete
svn ci -m "delete unuseful files"
