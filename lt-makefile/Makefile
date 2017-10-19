#############################################################################
#
# Generic Makefile for C/C++ Program
#
# Author:  yun63<thewardsthe@mail.com>
#
#############################################################################


include define.mk

BASE_DIR = .

LIBS_PATH = $(BASE_DIR)/lib

## DEBUG开关选项
DEBUG := 1

## 头文件搜索路径 
INCPATHS := -I$(BASE_DIR)/include -I$(BASE_DIR)/src#$(addprefix -I, $(HDRS)) 

## 库文件搜索路径及库
LIBS := $(addprefix -L, $(LIBPATHS)) -lm

## 源代码子目录
SRCDIRS := $(BASE_DIR)/include $(BASE_DIR)/src

## 目标目录
SAMPLES_PATH := $(BASE_DIR)/sample

## GTest测试框架目录
GTEST_DIR =
GTEST_HEADERS := $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h 
GTEST_SRCS_ := $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

## 可执行目标程序
SAMPLES = executable

CPPFLAGS += -isystem $(GTEST_DIR)/include

ifeq ($(DEBUG), 1)
	CXXFLAGS += -g
else
	CXXFLAGS += -O2
endif

COMMON_DIRS = $(BASE_DIR)/src/common $(BASE_DIR)/src/util
COMMON_SOURCES = $(foreach d, $(COMMON_DIRS), $(wildcard $(addprefix $(d)/*, $(SRCEXTS))))
COMMON_OBJECTS = $(addsuffix .o, $(basename $(COMMON_SOURCES)))

SAMPLES_TARGETS = $(LIBS_PATH)/libcommon.a \
	$(LIBS_PATH)/libcommon.so \
	$(foreach v, $(SAMPLES), $(SAMPLES_PATH)/$(v)) \

all: $(SAMPLES_TARGETS)

$(LIBS_PATH):
	@mkdir $(LIBS_PATH)

$(LIBS_PATH)/libcommon.a: $(COMMON_OBJECTS) | $(LIBS_PATH)
	@echo "-- Linking static library $@"
	@$(AR) $(ARFLAGS) $@ $^
	@$(RANLIB) $@

$(LIBS_PATH)/libcommon.so: $(COMMON_OBJECTS) | $(LIBS_PATH)
	@echo "-- Linking shared library $@"
	@$(LINK) -fPIC --shared $^ -o $@ $(INCPATHS) $(LIBS)


$(SAMPLES_PATH)/executable: $(SAMPLES_PATH)/main.o
	@echo "-- Generating $@"
	@$(CXX) $^ -o $@ $(INCPATHS) $(LIBS) -L$(LIBS_PATH) -lcommon

%.o:%.cpp
	@echo "-- Building $@"
	@$(CXX) -c $(CXXFLAGS) $(MYCFLAGS) $< -o $@ $(INCPATHS) 

%.o:%.cc
	@echo "-- Building $@"
	@$(CXX) -c $(CXXFLAGS) $(MYCFLAGS) $< -o $@ $(INCPATHS) 

%.o:%.cxx
	@echo "-- Building $@"
	@$(CXX) -c $(CXXFLAGS) $(MYCFLAGS) $< -o $@ $(INCPATH) 

%.o:%.c
	@echo "-- Building $@"
	@$(CC) -c $(CFLAGS) $(MYCFLAGS) $< -o $@ $(INCPATH) 

#-------------------------------------
.PHONY: clean 
clean:
	@rm -f *.core *.o $(COMMON_OBJECTS)
	@rm -f $(SAMPLES_PATH)/*.o
	@rm -rf $(SAMPLES_PATH)/*.dSYM
	@rm -rf $(LIBS_PATH)
	@rm -f $(SAMPLES_TARGETS)

#############################################################################
