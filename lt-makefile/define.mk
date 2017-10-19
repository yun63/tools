#############################################################################
#
# Generic defination for Makefile
#
# Author:  yun63<thewardsthe@mail.com> 
#
#############################################################################

## 源文件类型
SRCEXTS := .c .cc .cpp .cxx

## 指定C/C++编译器
CC := gcc
CXX := g++
LINK := g++
AR := ar
RANLIB := ranlib

## 编译器选项
CFLAGS := -Wall -W -fPIC
CXXFLAGS := -Wall -W -Wextra -Wno-unused-parameter --std=c++11 -fPIC
MYCFLAGS := -DDEBUG
ARFLAGS := crs

## 头文件搜索路径
HDRS :=

# 库文件搜索路径
LIBPATHS :=

# 输出颜色定义
RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
PURPLE='\033[1;35m'
CYAN='\033[1;36m'
NC='\033[0m'
