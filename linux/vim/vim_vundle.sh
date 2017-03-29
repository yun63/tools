#!/bin/bash

mkdir -p $HOME/.vim/bundle

git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim

cp -f ./vimrc $HOME/.vimrc

echo "Now Please follow below steps "
echo ""
echo "1> Open vim in commang line"
echo "2> Input ':PluginInstall'"
echo "3> Close vim and reopen it, now enjoy it !"
echo ""

