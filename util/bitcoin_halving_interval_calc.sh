#!/bin/bash

#
# Bitcoin halving interval calculator
#
# Author: Ho-Jung Kim (godmode2k@hotmail.com)
# Date: Since August 29, 2018
# Last modified:
#



# Bitcoin halving interval
# approx. 96(4 years, per 2 weeks) x per 2,016(blocks) = 193,536 (210,000 blocks)
#



#_hvi_block=210000
#_hvi_subsidy=50
#_hvi_subsidy=12.5


if [ -z "$1" ] || [ -z "$2" ]; then
	echo "Usage: bash $0 <total amount> <subsidy>"
	echo "e.g.,) $ bash $0 21000000 50"
	echo ""
	exit
fi

_hvi_block=`bc -l <<< "scale=0; $1 / 100"`
_hvi_subsidy=$2

_val=`bc -l <<< "$_hvi_block * $_hvi_subsidy"`

hvi_block=0
hvi_subsidy=$_hvi_subsidy
val=$_val
sum=0

echo "-----------------------------------------------"
echo "num | hvi block | hvi subsidy | block * subsidy"
echo "-----------------------------------------------"
for i in {00..30}; do
	hvi_block=`bc -l <<< "$hvi_block + $_hvi_block"`
	if [ $i == "00" ]; then
		hvi_subsidy=`bc -l <<< "$hvi_subsidy"`
		val=`bc -l <<< "$val"`
	else
		hvi_subsidy=`bc -l <<< "$hvi_subsidy / 2"`
		val=`bc -l <<< "$val / 2"`
	fi
	sum=`bc -l <<< "$sum + $val"`
	echo "$i    $hvi_block    $hvi_subsidy     $val"
done
echo "-------------------------------------"
echo " = $sum"

