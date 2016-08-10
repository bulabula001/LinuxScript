#!/bin/bash
# deal with the log cutting problem
#
#by chenfei 2015/2/25
#
#the script begin!

LOG="maillog"
LOGPATH="/var/log"
DATE=`date -d today +%Y%m%d`
IPADDR=`ifconfig eth0 | grep 'inet addr' | awk '{print $2}' | cut -d ':' -f 2`
CUTLOG=$LOG.$IPADDR.$DATE

cd $LOGPATH
mv $LOG $CUTLOG

gzip -c $CUTLOG > $CUTLOG.gz  && rm  -rf $CUTLOG  



