"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Maintainer: yun63 towardstheway@gmail.com
" Version: 0.1
" Last Change: 01/04/12 16:12:57 
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"允许语法高亮
syntax on
"检测文件类型
filetype on
"允许文件缩进
filetype indent on
"允许插件
filetype plugin on
"允许自动补全
filetype plugin indent on
"显示行号
set nu
"允许鼠标选中
set mouse=v
"自动缩进
set autoindent
"c/c++缩进
set cindent
set cinoptions=g0
"文件修改之后自动载入
set autoread
set nocp
set nocompatible
"忽略文件类型
set wildignore=*.o,*~,*.pyc,*/.git/*,*/.hg/*,*/.svn/*,*.beam
"启动的时候不显示那个援助索马里儿童的提示
set shortmess=atI
"设置折叠
set foldmethod=indent
set foldlevel=10 
"突出显示当前列
set cursorline
"退出vim,内容显示在终端屏幕,防止误删
"set t_ti= t_te=
"键入即时搜索高亮
set incsearch
set infercase
set hlsearch
"编码格式
set langmenu=zh_CN.UTF-8
language messages zh_CN.UTF-8
set termencoding=utf-8
set encoding=UTF-8
set fileencoding=utf-8
set fileencodings=utf-8,ucs-bom,shift-jis,gb18030,gbk,gb2312,cp936
"保存历史命令
set history=100
set t_Co=256
set t_ut=
set wildmenu
"显示标尺
set ruler
"显示输入的命令
set showcmd
"命令行高度
set cmdheight=2
set lz
set backspace=eol,start,indent
set magic
set noerrorbells
set novisualbell
set t_vb=
set showmatch
set laststatus=2
set colorcolumn=120
set clipboard=unnamed
set sessionoptions-=curdir
set sessionoptions+=sesdir
set nobackup
set nowb
set tabstop=4
set shiftwidth=4
set ts=4
set expandtab
set smarttab
set wrap
set completeopt=menuone,menu,longest

"let mapleader = " "
"let g:mapleader = "\\"
let mapleader = ","

"Vundle插件管理
filetype off 
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'gmarik/Vundle.vim'
Plugin 'ycm-core/YouCompleteMe'
Plugin 'rdnetto/YCM-Generator'
Plugin 'vim-cpp-enhanced-highlight'
Plugin 'Lokaltog/vim-powerline'
Plugin 'scrooloose/nerdtree'
Plugin 'sjas/csExplorer'
Plugin 'jlanzarotta/bufexplorer'
Plugin 'yun63/c.vim'
Plugin 'vim-scripts/winmanager'
Plugin 'yun63/doxygen-support.vim'
Plugin 'vim-scripts/DoxygenToolkit.vim'
Plugin 'vim-scripts/taglist.vim'
Plugin 'vim-scripts/a.vim'
Plugin 'vim-scripts/The-NERD-Commenter'
Plugin 'plasticboy/vim-markdown'
Plugin 'SirVer/ultisnips'
Plugin 'honza/vim-snippets'
Plugin 'jiangmiao/auto-pairs'
Plugin 'tomasiser/vim-code-dark'
Plugin 'dunstontc/vim-vscode-theme'
Plugin 'dhruvasagar/vim-table-mode'
Plugin 'rking/ag.vim'
Plugin 'Yggdroot/indentLine'
Plugin 'christoomey/vim-tmux-navigator'
Plugin 'easymotion/vim-easymotion'
Plugin 'skygragon/leetcode-cli'
Plugin 'fatih/vim-go'
Plugin 'NLKNguyen/papercolor-theme'
Plugin 'dracula/vim'
Plugin 'Yggdroot/LeaderF'
Plugin 'tpope/vim-fugitive'
Plugin 'exvim/ex-utility'
Plugin 'exvim/ex-project'
Plugin 'morhetz/gruvbox'
Plugin 'tomasr/molokai'
Plugin 'ayu-theme/ayu-vim'
Plugin 'romainl/Apprentice'

"Plugin 'zxqfl/tabnine-vim'
"Plugin 'marijnh/tern_for_vim'

call vundle#end()      

""""""""""""""""""""""""""""""
" colorscheme setting
""""""""""""""""""""""""""""""
"let g:solarized_termcolors=256
syntax enable
colorscheme gruvbox
set background=dark
let g:Powerline_theme = 'default'
let g:Powerline_colorscheme = 'default'

""""""""""""""""""""""""""""""
" 快捷键隐射
""""""""""""""""""""""""""""""
nnoremap <leader>\ :vs<CR>
nnoremap <leader>- :sp<CR>
inoremap <C-k> <C-O>C
inoremap <C-h> <left>
inoremap <C-l> <right>


""""""""""""""""""""""""""""""
" winmanager setting
""""""""""""""""""""""""""""""
let g:winManagerWindowLayout="FileExplorer,BufExplorer|TagList"
let g:winManagerWidth=30
let g:defaultExplorer=0
autocmd BufWinEnter \[Buf\ List\] setl nonumber

let g:netrw_winsize = 30
let loaded_feraltogglecommentify = 1

"autocmd FileType vim set nofen
autocmd BufNewFile *.py 0r ~/.vim/py.tmpl
autocmd BufNewFile *.py ks|call FileName()|'s
autocmd BufNewFile *.py ks|call CreateTime()|'s

fun FileName()
    if line("$") > 25
        let l = 25
    else
        let l = line("$")
    endif
    exe "1," . l . "g/@File:.*/s/@File:.*/@File: " .expand("%")
endfun

fun CreateTime()
    if line("$") > 25
        let l = 25
    else
        let l = line("$")
    endif
    exe "1," . l . "g/@Create:.*/s/@Create:.*/@Create: " .strftime("%Y-%m-%d %T")
endfun

let g:vimrc_loaded = 1

""""""""""""""""""""""""""""""
" YouCompleteMe setting
""""""""""""""""""""""""""""""
let g:ycm_global_ycm_extra_conf = '~/.vim/bundle/YouCompleteMe/.ycm_extra_conf.py'
let g:ycm_collect_identifiers_from_tags_files = 1
let g:ycm_seed_identifiers_with_syntax = 1
let g:ycm_confirm_extra_conf = 0

let g:ycm_key_list_select_completion =
      \ get( g:, 'ycm_key_list_select_completion', [] )

let g:ycm_key_list_previous_completion =
      \ get( g:, 'ycm_key_list_previous_completion', [] )

let g:ycm_show_diagnostics_ui =
      \ get( g:, 'ycm_show_diagnostics_ui',
      \ get( g:, 'ycm_register_as_syntastic_checker', 0 ) )

nnoremap <leader>jd :YcmCompleter GoTo<CR>
nnoremap <silent><leader>f :Ag <cword><CR>

" highlight Cursorline ctermfg=darkred ctermbg=cyan cterm=bold guifg=white guibg=yellow gui=bold

let g:tern_show_signature_in_pum = 1

let g:Lf_ShortcutF = '<C-P>'
let g:Lf_StlColorscheme = 'powerline'

""""""""""""""""""""""""""""""
" tmux setting
""""""""""""""""""""""""""""""
"let g:tmux_navigator_no_mappings = 1

"nnoremap <silent> <c-h> :TmuxNavigateLeft<cr>
"nnoremap <silent> <c-j> :TmuxNavigateDown<cr>
"nnoremap <silent> <c-k> :TmuxNavigateUp<cr>
"nnoremap <silent> <c-l> :TmuxNavigateRight<cr>

nnoremap <silent> <leader>o :EXProjectToggle<CR>

au BufNewFile,BufRead *.py set tabstop=4
au BufNewFile,BufRead *.py set softtabstop=4
au BufNewFile,BufRead *.py set shiftwidth=4

""""""""""""""""""""""""""""""
" indentLine setting
""""""""""""""""""""""""""""""
let g:indentLine_char = "┆"
let g:indentLine_enabled = 0
"let g:indentLine_setConceal = 0

""""""""""""""""""""""""""""""
" easymotion setting
""""""""""""""""""""""""""""""
nnoremap s <Plug>(easymotion-sn)

let Tlist_Use_Right_Window = 1

let g:AutoPairsMapCh = 0
