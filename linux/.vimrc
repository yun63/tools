"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Maintainer: yun63 towardstheway@gmail.com
" Version: 0.1
" Last Change: 01/04/12 16:12:57 
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

set mouse=v
set nocompatible
set nocp
"文件类型
filetype on
"文件缩进
filetype indent on
"允许插件
filetype plugin on
"自动补全
filetype plugin indent on

syntax on

set wildignore=*.o,*~,*.pyc,.git\*,.hg\*,.svn\*,*.beam                                          

"文件修改之后自动载入
set autoread
"启动的时候不显示那个援助索马里儿童的提示
set shortmess=atI
"备份
set backup
set backupext=.bak
set backupdir=~

set foldmethod=syntax
set foldlevel=20 

" 突出显示当前列
set cursorline
" 退出vim,内容显示在终端屏幕,防止误删
"set t_ti= t_te=
" 键入即时搜索
set incsearch
set infercase

set autoindent
set cindent

set encoding=UTF-8
set langmenu=zh_CN.UTF-8
language messages zh_CN.UTF-8
set fileencodings=ucs-bom,utf-8,gbk,gb18030,cp936,big5,euc-cn,euc-kr,latin1

let g:DoxygenToolkit_briefTag_funcName="yes" 
let g:DoxygenToolkit_briefTag_pre="@brief  "
let g:DoxygenToolkit_paramTag_pre="@param  "
let g:DoxygenToolkit_returnTag="@return  "

set history=400
set t_Co=256

let mapleader = ","
let g:mapleader = "\\"

nmap <F9> :SCCompile<cr>
nmap <F10> :SCCompileRun<cr>

" Vundle插件管理
filetype off 
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'gmarik/Vundle.vim'
Plugin 'Lokaltog/vim-powerline'
Plugin 'scrooloose/nerdtree'
Plugin 'kien/ctrlp.vim'
Plugin 'vim-cpp-enhanced-highlight'
Plugin 'eikenb/acp'
Plugin 'sjas/csExplorer'
Plugin 'jlanzarotta/bufexplorer'
Plugin 'dradtke/OmniCppComplete'
Plugin 'vim-scripts/AutoTag'
Plugin 'vim-scripts/winmanager'
Plugin 'vim-scripts/neocomplcache'
Plugin 'vim-scripts/The-NERD-Commenter'
Plugin 'vim-scripts/cscope.vim'
Plugin 'vim-scripts/doxygen-support.vim'
Plugin 'vim-scripts/DoxygenToolkit.vim'
Plugin 'vim-scripts/AutoComplPop'
Plugin 'vim-scripts/SingleCompile'
Plugin 'vim-scripts/lookupfile'
Plugin 'vim-scripts/taglist.vim'
Plugin 'vim-scripts/a.vim'
Plugin 'vim-scripts/pathogen.vim'
Plugin 'godlygeek/tabular'
Plugin 'plasticboy/vim-markdown'
Plugin 'clones/vim-genutils'
Plugin 'vim-erlang/vim-erlang-tags'
Plugin 'vimscript/c-support'
Plugin 'vim-scripts/ag.vim'
Plugin 'google/vim-colorscheme-primary'
Plugin 'pangloss/vim-javascript'
call vundle#end()      
filetype plugin indent on

set wildmenu
set ruler
set showcmd
set cmdheight=2
set nu
set lz
set backspace=eol,start,indent
set whichwrap+=<,>
set incsearch
set hlsearch
set magic
set noerrorbells
set novisualbell
set t_vb=
set showmatch
set laststatus=2
set colorcolumn=120

set clipboard=unnamed

""""""""""""""""""""""""""""""
" colorscheme setting
""""""""""""""""""""""""""""""
let g:solarized_termcolors=256
syntax enable
colorscheme solarized 
set background=light

let g:Powerline_colorscheme='solarized256'

" vimrc文件修改之后自动载入
autocmd! bufwritepost .vimrc source %

nnoremap <C-j> <C-W>j
nnoremap <C-k> <C-W>k
nnoremap <C-h> <C-W>h
nnoremap <C-l> <C-W>l

imap <C-k> <esc>C

set sessionoptions-=curdir
set sessionoptions+=sesdir

set nobackup
set nowb
map <C-F12> :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q --language-force=c++ .<CR>
map <C-F1> :!retext expand('%d:p')<cr>

set tabstop=4
set shiftwidth=4
set ts=4
set expandtab
set smarttab

"au FileType c,java,python setl shiftwidth=4
au FileType txt setl lbr
au FileType txt setl tw=78

set ai
set si

set cindent
set wrap
set completeopt=menuone,menu,longest

nmap <script> <silent> <unique> <Leader>tt :NERDTree<CR>

""""""""""""""""""""""""""""""
" winmanager setting
""""""""""""""""""""""""""""""
let g:winManagerWindowLayout="FileExplorer,BufExplorer|TagList"
let g:winManagerWidth=30
let g:defaultExplorer=0
nmap <C-W><C-F> :FirstExplorerWindow<cr>
nmap <C-W><C-B> :BottomExplorerWindow<cr>
nmap <silent> <leader>wm :WMToggle<cr>
autocmd BufWinEnter \[Buf\ List\] setl nonumber

let g:netrw_winsize = 30
let loaded_feraltogglecommentify = 1

autocmd FileType vim set nofen
autocmd FileType vim map <buffer> <leader><space> :w!<cr>:source %<cr>

autocmd FileType c,cpp  map <buffer> <leader><space> :make<cr>

nmap <leader>cn :cn<cr>
nmap <leader>cp :cp<cr>
nmap <leader>cw :cw 10<cr>

let g:vimrc_loaded = 1

""""""""""""""""""""""""""""""
" omnicomplete setting
""""""""""""""""""""""""""""""
let OmniCpp_NamespaceSearch = 1
let OmniCpp_GlobalScopeSearch=1
let OmniCpp_ShowAccess=1
"显示函数参数列表
let OmniCpp_ShowPrototypeInAbbr = 1 
"输入.自动补全
let OmniCpp_MayCompleteDot = 1   
"输入->后自动补全
let OmniCpp_MayCompleteArrow = 1
"输入::后自动补全
let OmniCpp_MayCompleteScope = 1 
let OmniCpp_DefaultNamespaces = ["std", "_GLIBCXX_STD"]
au CursorMovedI,InsertLeave * if pumvisible() == 0|silent! pclose|endif
autocmd FileType python set omnifunc=pythoncomplete#Complete

highlight darkblue guibg=darkgrey  guifg=black
highlight lightpurple guibg=lightgrey guifg=black

""""""""""""""""""""""""""""""
" ctags setting
""""""""""""""""""""""""""""""
set tags=/home/yun63/backup/stl_tags
set tags+=/home/yun63/myself/repos/aoi/tags
set tags+=/home/yun63/opensource/ipc/unpv2ee/tags
set tags+=/home/yun63/mobile-server/trunk/tags

set runtimepath^=/home/yun63/.vim/bundle/vim-erlang-tags

""""""""""""""""""""""""""""""
" echofunc setting
""""""""""""""""""""""""""""""
let g:EchoFuncLangsUsed=["cpp", "c"]

""""""""""""""""""""""""""""""
" ctrlp setting
""""""""""""""""""""""""""""""
let g:ctrlp_max_files = 10000
let g:ctrlp_max_depth = 60
let g:ctrlp_working_path_mode = 'ra'
let g:ctrlp_max_depth = 40
