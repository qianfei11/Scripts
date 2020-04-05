set nocompatible              " be iMproved, required
filetype off                  " required
" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'
Plugin 'Valloric/YouCompleteMe'
Plugin 'tomlion/vim-solidity'
Plugin 'frazrepo/vim-rainbow'
Plugin 'git://github.com/scrooloose/nerdtree.git'
Plugin 'Xuyuanp/nerdtree-git-plugin'
Plugin 'scrooloose/nerdcommenter'
Plugin 'tpope/vim-fugitive'
Plugin 'airblade/vim-gitgutter'
call vundle#end()            " required
filetype plugin indent on    " required
syntax enable
set showcmd
set cursorline
set lazyredraw
set showmatch
set ruler
set number
set encoding=utf-8
set softtabstop=4
set tabstop=4
set lines=45 columns=150
set guifont=Monaco\ for\ Powerline:h11
let g:rainbow_active = 1
autocmd vimenter * NERDTree
let g:NERDTreeIndicatorMapCustom = {
    \ "Modified"  : "✹",
    \ "Staged"    : "✚",
    \ "Untracked" : "✭",
    \ "Renamed"   : "➜",
    \ "Unmerged"  : "═",
    \ "Deleted"   : "✖",
    \ "Dirty"     : "✗",
    \ "Clean"     : "✔︎",
    \ 'Ignored'   : '☒',
    \ "Unknown"   : "?"
    \ }
let mapleader=','
colorscheme molokai
