CentOS-8源码安装vim8.1
=====================

## 1 安装依赖

`yum install python-dev python3-dev ncurses-devel git`

## 2 删除旧版本的vim（如果有）

## # 下载源码并安装

```
$ git clone https://github.com/vim/vim.git
$ cd vim
$ ./configure --with-features=huge \
            --enable-multibyte \
            --enable-pythoninterp=yes \
            --enable-python3interp=yes \
            --enable-perlinterp=yes \
            --enable-luainterp=yes \
            --enable-cscope \
            --prefix=/usr/local
$ make
$ make install
```

完毕！


