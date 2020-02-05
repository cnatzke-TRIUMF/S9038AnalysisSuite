#!/bin/bash
DATADIR=/tig/grifstore0b/griffin/90Sr-source # File Path of Midas Files
FRAGDIR=/tig/belodon_data4/S9038/FragmentTrees # Directory to store Fragment Trees
ANALDIR=/tig/belodon_data4/S9038/AnalysisTrees # Directory to store Analysis Trees
CFILE=/tig/belodon_data4/S9038/S1367Cal.cal # Calibration File

DLEN=${#DATADIR}

m=15740 # Only Sort after this run
last_run=15868

# hack to find grsisort 
#PATH=/home/S9038/packages/GRSISort/bin:/opt/root/bin:/opt/bin:/usr/local/texlive/2015/bin/x86_64-linux:/usr/lib64/qt-3.3/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/S9038/bin
#LD_LIBRARY_PATH=/home/S9038/packages/GRSISort/GRSIData/lib:/home/S9038/packages/GRSISort/lib:/opt/root/lib

# cd into sorting directory
cd /tig/belodon_data4/S9038/

if [ $# -eq 0 ]
then
   for f in $DATADIR/*.mid; do # Sorts all runs
      g=${f:DLEN+4}
      h=${g:0:${#g}-4} 
      i=${g:0:${#g}-8} 
      FFILE=$FRAGDIR/fragment$h.root
      AFILE=$ANALDIR/analysis$h.root
      echo "Processing run$g"

      if [ ! -f $AFILE ] && [ $i -gt $m ] && [ $i -lt $last_run ]; # Checks if file exists if not it sorts it  
      then
         echo "File $AFILE does not exist."
         grsisort --recommended --word-count-offset=-1 $f $CFILE
         mv -f analysis$h.root $ANALDIR
         mv -f fragment$h.root $FRAGDIR

      fi

      if [ -f $AFILE ]
      then 

         if [ "$AFILE" -ot "$f" ] && [ $i -gt $m ] && [ $i -lt $last_run ]; # Checks if the midas file is newer than analysis tree
         then
            echo "File $AFILE exists but is older than $f"
            grsisort --recommended --word-count-offset=-1 $f $CFILE
            mv -f analysis$h.root $ANALDIR
            mv -f fragment$h.root $FRAGDIR
         fi
      fi
   done 

else 
   for f in $DATADIR/run"$@"_*.mid; # Sorts sub runs from a single file

   do
      g=${f:DLEN+4}
      h=${g:0:${#g}-4} 
      i=${g:0:${#g}-8} 
      FFILE=$FRAGDIR/fragment$h.root
      AFILE=$ANALDIR/analysis$h.root
      echo "Processing run$g "

      if [ ! -f $AFILE ];  
      then
         echo "File $AFILE does not exist."
         grsisort --recommended --word-count-offset=-1 $f $CFILE
         mv -f analysis$h.root $ANALDIR
         mv -f fragment$h.root $FRAGDIR

      fi

      if [ -f $AFILE ]
      then 

         if [ "$AFILE" -ot "$f" ] && [ $i -gt $m ];
         then
            echo "File $AFILE exists but is older than $f"
            grsisort --recommended --word-count-offset=-1 $f $CFILE
            mv -f analysis$h.root $ANALDIR
            mv -f fragment$h.root $FRAGDIR
         fi
      fi
   done
fi
