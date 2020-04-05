#!/bin/bash

set -o nounset

help() {
	cat << EOT
Usage: $0 [OPTION]
Option:
 ## $0 Options
  -b, --binary=BINARY
  -i, --ip=IP
  -p, --port=PORT
  -d, --debug
  -g, --gdb
  -h, --help
EOT
}

if [ $# -eq 0 ] ; then
	help;
	exit -1;
fi

BINARY=
IP="127.0.0.1"
PORT="8888"
DEBUG=0
GDB=0

RET=`getopt -o dhb:i:p: --long debug,help,binary:,ip:,port:\
 -n ' * ERROR' -- "$@"`

if [ $? != 0 ] ; then
	echo "$0 exited with doing nothing.";
	exit -1;
fi

eval set -- "$RET"

while true ; do
	case "$1" in
		-h | --help )
			help;
			exit -1;;
		-d | --debug )
			DEBUG=1;
			shift;;
		-g | --gdb )
			GDB=1;
			;;
		-b | --binary )
			BINARY=$2;
			shift 2;;
		-i | --ip )
			IP=$2;
			shift 2;;
		-p | --port )
			PORT=$2;
			shift 2;;
		-- )
			shift;
			break;;
		* )
			echo "Internal error.";
			exit -1;
	esac
done

if [ ! -n "$BINARY" ] ; then
	echo "$0 need a specific BINARY.";
	exit -1;
fi

if [ $DEBUG -eq 1 ] ; then
	if [ $GDB -eq 1 ] ; then
		echo "Can not use gdb and debug together.";
		exit -1;
	else
		ncat -vc "LD_SHOW_AUXV=1 strace -e trace=read $BINARY" -kl $IP $PORT
	fi
else
	if [ $GDB -eq 1 ] ; then
		ncat -vc "gdbserver $IP:`expr $PORT + 1` $BINARY" -kl $IP $PORT
	else
		ncat -vc "$BINARY" -kl $IP $PORT
	fi
fi

