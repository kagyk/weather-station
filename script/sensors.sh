#!/bin/bash

echo " "
echo "************************************* Работает скрипт $0 *************************************************"
echo " "

FLAG=true
TEMP=0
HUMIDITY=0
FIFO_FILE="/tmp/weather_station.fifo"

trap "handler" SIGINT


handler()
{
    echo "сработал хендлер"
    FLAG=false
    sleep 1s
    test -e $FIFO_FILE && rm -f $FIFO_FILE
}

rnd()
{
    local FLOOR=$1
    local RANGE=$2
    local rnd_num=0
    while [ "$rnd_num" -le $FLOOR ]; do
        rnd_num=$RANDOM
        let "rnd_num %= $RANGE"
    done
    echo ${rnd_num}
}

generate_xml()
{
    HUMIDITY=$(rnd 1 100)
    TEMP=$(rnd 0 100)
    data="<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>
    <config>
        <temperature>$TEMP</temperature>
        <humidity>$HUMIDITY</humidity>
    </config>"
    echo "$data"
}

test -e $FIFO_FILE && rm -f $FIFO_FILE
mkfifo $FIFO_FILE

while [[ $FLAG == true ]]
do
    str="$(generate_xml)"
    echo "$str" > $FIFO_FILE
    echo ""
    echo ""
    sleep 5s

done

echo " "
echo "************************************* Конец работы скрипта $0 *************************************************"
echo " "

exit 0
