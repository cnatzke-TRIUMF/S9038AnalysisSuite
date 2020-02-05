#!/bin/bash

PIDFILE=/data2/S9038/Utils/autosort.pid

## hack to find grsisort 
#export PATH="/home/S9038/packages/GRSISort/bin:/opt/root/bin:/opt/bin:/usr/local/texlive/2015/bin/x86_64-linux:/usr/lib64/qt-3.3/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/S9038/bin"
#export LD_LIBRARY_PATH="/home/S9038/packages/GRSISort/GRSIData/lib:/home/S9038/packages/GRSISort/lib:/opt/root/lib"

# send message to discord
send_message() {
   python3 /data2/S9038/Utils/send_discord_message.py "$@"
}

# safety checks to make sure only one instance runs at once
if [ -f $PIDFILE ]; then 
   PID=$(cat $PIDFILE)
   ps -p $PID > /dev/null 2>&1
   if [ $? -eq 0 ]; then 
      send_message "MakeAnalysis already running ... "
      exit 1
   else
      ## process not found, assume not running
      echo $$ > $PIDFILE
      if [ $? -ne 0 ]; then 
         send_message "Could not create PID file ... [EXITING]"
         exit 1
      fi
   fi
else
   echo $$ > $PIDFILE
   if [ $? -ne 0 ]; then 
      send_message "Could not create PID file ... [EXITING]"
      exit 1
   fi
fi

# unpacks Midas files
send_message "Running MakeAnalysis.sh ..."
/data2/S9038/MakeAnalysis.sh 15686 
rm $PIDFILE
send_message "Running MakeAnalysis.sh ... [DONE]"

