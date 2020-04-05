#!/bin/bash
if [ -z "$1" ]; then
	eval "curl wttr.in"
fi
if [ -n "$1" ]; then
	eval "curl wttr.in/$1"
fi
