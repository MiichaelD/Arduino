#!/bin/sh

# For Window's bash -- Linux: "Permission denied"
# https://blogs.msdn.microsoft.com/wsl/2017/04/14/serial-support-on-the-windows-subsystem-for-linux

# serial.sh
# Usage:
# $ serial.sh <device> <baud_rate>
# Example: serial.sh /dev/ttyUSB0 9600
if [ "$#" -ne 2 ]; then
  echo "Usage: serial.sh <device> <baud_rate>\nExample: serial.sh /dev/ttyUSB0 9600\n" >&2
  exit 1
else
  echo "Type 'z' to close subprocesses when finished" 
fi

# Set up device
stty -F $1 $2

# Let cat read the device $1 in the background
# cat $1 &
./serialc $1 & # serialc can interact with the input (i.e. react when receiving a string)

# Capture PID of background process so it is possible to terminate it when done
bgPid=$!

# Read commands from user, send them to device $1
while read cmd; do
  echo "$cmd" > $1
  if [ "$cmd" = "z" ]; then
    echo "Exiting serial.sh and subprocess "$bgPid 
    break
  fi
done

# Terminate background read process  -- serialc exits loops automatically, no need to kill
# kill $bgPid
echo "\n";