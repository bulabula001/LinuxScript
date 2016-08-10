#!/bin/bash
#
#2015/3/3 by chenfei
#
#record the useage of the cpu
#
#script start
###################################################

set -x

LOGPATH=/root/test

date >> $LOGPATH/cpu_date.txt

top -b -n 1 | grep Cpu >> $LOGPATH/cpu_now.txt

paste	$LOGPATH/cpu_date.txt $LOGPATH/cpu_now.txt  > $LOGPATH/cpu_log.txt

#
#limit the size of these log file
#

MAXLINE=100

CURLINE=`cat $LOGPATH/cpu_log.txt|wc -l`

if [ $CURLINE -gt $MAXLINE ];then

>$LOGPATH/cpu_date.txt

>$LOGPATH/cpu_now.txt

>$LOGPATH/cpu_log.txt

fi


####################################################
#
#End the script
#
