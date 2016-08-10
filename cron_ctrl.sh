#!/bin/bash
#
#2015/3/3 by chenfei
#
#extend the function of crontab command
#
#script start
#
####################################################
#
# set -x

USER=`who am i| awk '{print $1}'`

SCRIPTDIR="/root/test"

CRON_TEMP=$SCRIPT/cron_temp

TARGET=$SCRIPTDOR/$1.sh

echo $TARGET

if [ $# != 2 ]
then
        echo "Usage:`basename $0` jobname [--start|--stop|--list|--help]" >&2
        exit 1

fi
OPT=$2
case $OPT in
--start)
        echo "Will start the mission `basename $1` ,please wait..."
	echo "-------------------------------->"
        crontab -l > $CRON_TEMP
	sed -i  's%\(^##*\)\(.*'''$TARGET'''\)%\2%' $CRON_TEMP
	crontab $CRON_TEMP
	>$CRON_TEMP
	if [ $? -eq 0 ]
        then
        echo "commands have finished!"
        fi
	;;
--stop)
        echo "stop...`basename $1`"
	echo "-------------------------------->"
        crontab -l > $CRON_TEMP 
	sed  -i 's%\(.*'''$TARGET'''\)%#\1%' $CRON_TEMP
	crontab $CRON_TEMP
	>$CRON_TEMP
	;;
--list)
	echo "will list the missions under current user,please wait..."
	echo "-------------------------------->"
	crontab -l -u $USER
	if [ $? -eq 0 ]
	then
	echo "commands have finished!"
	fi
	;;
--help)
        echo "now don't support help"
	echo "-------------------------------->"
	if [ $? -eq 0 ]
        then
        echo "commands have finished!"
        fi
        ;;
-v|--version)
	echo "current version is V1.0"
	echo "-------------------------------->"
	if [ $? -eq 0 ]
        then
        echo "commands have finished!"
        fi
	;; 
*)
      	echo "Usage:`basename $0` jobname [--start|--stop|--list|--help|--version]" 
	;;        

esac

