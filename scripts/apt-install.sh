#!/bin/bash

INSTALL="apt-get install -y"
UPDATE="apt-get update"

$UPDATE

#tools
$INSTALL vim
$INSTALL git git-core git-completion
$INSTALL ssh screen
$INSTALL curl
$INSTALL make
$INSTALL cmake
#cpp
$INSTALL g++
#python
$INSTALL python-setuptools python-mysqldb pylint
#node.js
$INSTALL npm

