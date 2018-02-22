#!/bin/bash
#
# Author: Gihan De Silva @  gihansblog.com
# rename script
# rename.sh
clear
x=0
for i in `ls *.mp3`
do
x=`expr $x + 1`
mv $i $x.mp3
done



echo “rename done!”