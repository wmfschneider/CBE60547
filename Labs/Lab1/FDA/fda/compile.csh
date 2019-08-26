#!/bin/csh
rm -f compile.log
foreach cxx (*.cxx)
  echo $cxx
  echo "" >> compile.log
  echo $cxx >> compile.log
  g++ -c -DEBUGGED -DHAVE_LOG1P -O $cxx >>& compile.log
  end
