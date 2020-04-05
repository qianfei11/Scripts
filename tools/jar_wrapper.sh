#!/bin/bash -
#===============================================================================
#
# FILE: shell_pack.sh
#
# USAGE: ./shell_pack.sh
#
# DESCRIPTION:
#
# OPTIONS: ---
# REQUIREMENTS: ---
# BUGS: ---
# NOTES: ---
# AUTHOR: lwq (28120), xxx@email.com
# ORGANIZATION:
# CREATED: 04/22/2015 02:38:01 PM CST
# REVISION: ---
#===============================================================================

#=== FUNCTION ================================================================
# NAME: usage
# DESCRIPTION: Display usage information.
#===============================================================================
function usage() {
    cat <<-EOT
Usage : $0 [options] -p package -s script file1 file2 file3 ...
Options:
    -h|help Display this message
    -p|package The output package name
    -j|jar file The jar file
EOT
} # ---------- end of function usage ----------

#-----------------------------------------------------------------------
# Handle command line arguments
#-----------------------------------------------------------------------

while getopts ":hp:j:" opt; do
    case $opt in

    h | help)
        usage
        exit 0
        ;;
    p | package) package_name=$OPTARG ;;
    j | jar) jar_file=$OPTARG ;;
    \?)
        echo -e "\n Option does not exist : $OPTARG\n"
        usage
        exit 1
        ;;

    esac # --- end of case ---
done
shift $(($OPTIND - 1))

if [[ -z $package_name ]]; then
    echo "package_name can't not be empty"
    usage
    exit
fi

if [[ -z $jar_file ]]; then
    echo "jar_file can't not be empty"
    usage
    exit
fi

generate_wrapper_script() {
    local wrapper_script=$1
    cat <<-'EOT' >$wrapper_script
#!/bin/sh
java -jar $0 "$@"
if [ $? -ne 0 ]; then
 echo "run jar file failed."
 exit 1
fi
exit 0
#__SCRIPTEND__
EOT
}

wrapfile=wrap_$$.sh

echo -e "start packing ..\n"
generate_wrapper_script $wrapfile
cat $wrapfile $jar_file >$package_name
chmod +x $package_name

echo -e "\noutput: $package_name\n"

rm -f $wrapfile
