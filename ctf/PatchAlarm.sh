#!/bin/bash
if [ $# -ne 2 ] ; then
	echo "Usage: $0 [BINARY]"
	exit -1;
fi

sed -i s/alarm/isnan/g $1
