#!/bin/bash

home=`cd $(dirname $0); pwd`
CMAKE_SRC="cmake-3.13.2"
LLVM_SRC="llvm-7.0.1"
CLANG_SRC="cfe-7.0.1"
COMPILER_RT_SRC="compiler-rt-7.0.1"
CLANG_TOOLS_EXTRA_SRC="clang-tools-extra-7.0.1"

if [ ! -d $HOME/.vim/bundle/YouCompleteMe ]; then
    echo "Please install 'YouCompleteMe' first !!"
    echo "How to install YouCompleteMe, please refer to https://github.com/yun63/tools/vim/vim_vundle.sh"
    exit 1
fi;

# download source code 
if [ ! -f ${CMAKE_SRC}.tar.gz ]; then
    wget https://cmake.org/files/v3.13/${CMAKE_SRC}.tar.gz
fi

if [ ! -f ${LLVM_SRC}.src.tar.xz ]; then
    wget http://releases.llvm.org/7.0.1/${LLVM_SRC}.src.tar.xz
fi

if [ ! -f ${CLANG_SRC}.src.tar.xz ]; then
    wget http://releases.llvm.org/7.0.1/${CLANG_SRC}.src.tar.xz
fi

if [ ! -f ${COMPILER_RT_SRC}.src.tar.xz ]; then
    wget http://releases.llvm.org/7.0.1/${COMPILER_RT_SRC}.src.tar.xz
fi

if [ ! -f ${CLANG_TOOLS_EXTRA_SRC}.src.tar.xz ]; then
    wget http://releases.llvm.org/7.0.1/${CLANG_TOOLS_EXTRA_SRC}.src.tar.xz
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
cd build && ../llvm-7.0.1.src/configure --enable-optimized --enable-targets=host-only
make -j4 && sudo make install

cd $HOME/.vim/bundle/YouCompleteMe
./install.py --clang-completer --system-libclang

# finish
echo " Enjoyed it !"


