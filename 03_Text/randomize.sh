#!/bin/bash

inds=()
text=()
DELAY=${1:-0.01}

width=0
height=0

i=0
while IFS= read -r line
do
    text+=("$line")
    for j in `seq 0 $((${#line}-1))`
    do
        inds+=("$i:$j")
    done

    if (( $width < ${#line} ))
    then 
        width=${#line}
    fi

    ((i++))
done
height=$i

term_width=`tput cols`
term_height=`tput lines`

width_offset=$(((term_width - width) / 2))
height_offset=$(((term_height - height) / 2))

tput clear
for idx in `shuf -i 0-$((${#inds[@]}-1))`
do
    x=`echo ${inds[$idx]} | cut -f 2 -d ":"`
    y=`echo ${inds[$idx]} | cut -f 1 -d ":"`
    tput cup $((y + height_offset)) $((x + width_offset))
    echo "${text[$y]:$x:1}"
    sleep $DELAY

done
tput cup "$(tput lines)" 0
echo -n
