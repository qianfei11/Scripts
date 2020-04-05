#!/bin/bash
if [ $# -ne 1 ] ; then
	echo "Usage:" $0 "[LOCATION]"
else
	defaults write com.apple.screencapture location $1
fi
