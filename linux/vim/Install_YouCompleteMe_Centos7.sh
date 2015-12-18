#!/bin/bash

home=`cd $(dirname $0); pwd`
CMAKE_SRC="cmake-3.4.1"
LLVM_SRC="llvm-3.7.0"
CLANG_SRC="cfe-3.7.0"
COMPILER_RT_SRC="compiler-rt-3.7.0"
CLANG_TOOLS_EXTRA_SRC="clang-tools-extra-3.7.0"

# download source code 
if [ ! -f ${CMAKE_SRC}.tar.gz ]; then
    wget https://cmake.org/files/v3.4/${CMAKE_SRC}.tar.gz
fi

if [ ! -f ${LLVM_SRC}.src.tar.xz ]; then
    wget http://llvm.org/releases/3.7.0/${LLVM_SRC}.src.tar.xz
fi

if [ ! -f ${CLANG_SRC}.src.tar.xz ]; then
    wget http://llvm.org/releases/3.7.0/${CLANG_SRC}.src.tar.xz
fi

if [ ! -f ${COMPILER_RT_SRC}.src.tar.xz ]; then
    wget http://llvm.org/releases/3.7.0/${COMPILER_RT_SRC}.src.tar.xz
fi

if [ ! -f ${CLANG_TOOLS_EXTRA_SRC}.src.tar.xz ]; then
    wget http://llvm.org/releases/3.7.0/${CLANG_TOOLS_EXTRA_SRC}.src.tar.xz
fi

mkdir -p build

# unzip
tar -zxf ${CMAKE_SRC}.tar.gz
tar -xvf ${LLVM_SRC}.src.tar.xz
tar -xvf ${CLANG_SRC}.src.tar.xz
tar -xvf ${COMPILER_RT_SRC}.src.tar.xz
tar -xvf ${CLANG_TOOLS_EXTRA_SRC}.src.tar.xz

rm -f ${LLVM_SRC}.src/tools/clang -rf
mv ${CLANG_SRC}.src ${LLVM_SRC}.src/tools/clang -f
mv ${CLANG_TOOLS_EXTRA_SRC}.src ${LLVM_SRC}.src/tools/clang/extra -f
rm ${LLVM_SRC}.src/projects/compiler-rt -rf
mv ${COMPILER_RT_SRC}.src ${LLVM_SRC}.src/projects/compiler-rt -f

# build and install cmake llvm
cd ${CMAKE_SRC} && ./bootstrap
make -j4 && sudo make install
cd build && ../llvm-3.7.0.src/configure --enable-optimized --enable-targets=host-only
make -j4 && sudo make install

cd $HOME/.vim/bundle/YouCompleteMe
./install.py --clang-completer --system-libclang

# finish
echo " Enjoyed it !"


