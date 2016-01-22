#!/bin/bash

respath=$HOME/Work/res/Resources

replace_png()
{
    for path in `find $respath -name $1`; do
        echo $1 $path
        cp -f $1 $path
    done
}

for f in `ls *.png`; do
    replace_png $f
done


