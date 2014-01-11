#!/usr/bin/env bash

check() {
  atime=`shasum game.c | awk '{ print $1 }'`
}

compare() {
  if [[ $atime != $ltime ]]
  then
    echo "building..."
    build.sh
    echo "done."
  fi
  ltime=$atime
}

while true; do
  check
  compare
  sleep 1
done
