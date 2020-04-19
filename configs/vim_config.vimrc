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
Plugin 'mzlogin/vim-smali'
Plugin 'Chiel92/vim-autoformat'
call vundle#end()            " required
filetype plugin indent on    " required
syntax enable
set showcmd
set cursorline
set lazyredraw
set showmatch
set ruler
set number
set tabstop=4
set shiftwidth=4
set expandtab
set encoding=utf-8
set lines=45 columns=150
set guifont=Monaco\ for\ Powerline:h11
noremap <F3> :Autoformat<CR>
let g:python3_host_prog = "/usr/local/bin/python3"
let g:autoformat_autoindent = 0
let g:autoformat_retab = 0
let g:autoformat_remove_trailing_spaces = 0
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
set rtp+=/Users/assassinq/Library/Python/2.7/lib/python/site-packages/powerline/bindings/vim
let mapleader=','
colorscheme molokai
