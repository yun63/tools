#!/bin/bash

while getopts :ab:c opt
do
    case "$opt" in
        a) echo "Fount the -a option" ;;
        b) echo "Fount the -b option, with value $OPTARG" ;;
        c) echo "Fount the -c option" ;;
        *) echo "Unkown option: $opt" ;;
    esac
done

