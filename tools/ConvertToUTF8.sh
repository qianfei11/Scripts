#!/bin/bash
if [ $# -ne 2 ] ; then
	echo "Usage:" $0 "[Input] [Output]"
else
	iconv -c -f GB2312 -t UTF-8 $1 > $2
fi
