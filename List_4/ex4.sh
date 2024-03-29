#!/bin/bash

SHORT_OPTS=(
    "c"
    "g:"
    "h"
    "v"
    "w"
)

LONG_OPTS=(
    "capitalize"
    "color:"
    "greeting:"
    "help"
    "version"
    "world"
)

opts=$(getopt \
    --longoptions "$(printf "%s," "${LONG_OPTS[@]}")"\
    --name "$(basename "$0")"\
    --options "$(printf "%s," "${SHORT_OPTS[@]}")"\
    -- "$@"
)

eval set --$opts

CAPITALIZE=false
COLOR=false
WORLD=false
GREETING="Hello"
VERSION="HWB Alpha 1.0.0"
HELP="Program for greeting ppl
Usage: hwb [options] arguments
Options:
-c, --capitalize Capitalize ouput
--color=[never|auto|always] Color output
-g [text], --greeting=[text] Change the default message
-h, --help Print out this help message
-v, --version Print out version
-w, --world Extra output\n"
while [[ $# -gt 0 ]]; do
    case "$1" in
        -c | --capitalize)
            CAPITALIZE=true
            shift
            ;;
        -g | --greeting)
            GREETING=$2
            shift 2
            ;;
        --color)
            case "$2" in
            never)COLOR=false;;
            auto)
                if [ -t 1 ]
                then
                    COLOR=true
                else
                    COLOR=false
                fi;;
            always)COLOR=true;;
            *)
                echo "--color=[never|auto|always]"
                exit 1;;
            esac
            shift 2
            ;;
        -h | --help)
            printf "$HELP"
            shift 1
            exit 0
            ;;
        -v | --version)
            echo $VERSION
            shift 1
            exit 0
            ;;
        -w | --world)
            WORLD=true
            echo $WORLD
            shift 
            ;;
        *)
            shift
            break
            ;;
    esac
done

if [ $COLOR = true ];then
    col1=`tput setaf 4`
    col2=`tput setaf 3`
else
    col1=`tput sgr0`
    col2=`tput sgr0`
fi
rest=`tput sgr0`
for var in "$@"
do
    if [ $CAPITALIZE = true ]; then
        var="${var^}"
    fi
    echo "${col1}$GREETING${rest}, ${col2}$var${rest}!"
done
if [ $WORLD = true ]; then
    echo "Hello, world!"
fi