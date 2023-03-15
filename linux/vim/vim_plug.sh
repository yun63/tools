#!/bin/bash

curl -fLo ~/.vim/autoload/plug.vim --create-dirs https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim

cp -f ./vimrc $HOME/.vimrc

echo "Now Please follow below steps "
echo ""
echo "1> Open vim in commang line"
echo "2> Input ':PluginInstall'"
echo "3> Close vim and reopen it, now enjoy it !"
echo ""

