#!/bin/sh

fname=$1
#
echo
while read run
  do
#
# Write file batch_krun
#
  echo
  echo "epstopdf "${run} >> run.sh
  echo
#
# sleep 1
done < $fname
echo
echo "***** Good Bye and thank you for using the script *****"
echo
