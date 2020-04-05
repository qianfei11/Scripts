#!/bin/bash
if [ $# -ne 1 ] ; then
	echo "Usage:" $0 "[PID]"
else
	lsof -i:$1
fi
