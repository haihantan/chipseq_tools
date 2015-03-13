#!/bin/sh
# Takes a MACS xls file and converts it to a bed file
# Peak name contains the number and p-value of the peak
grep -v "#" $1 | grep -e '^$' -v | awk '{ if($3-$2>0) { print $1"\t"$2"\t"$3"\tMACS_peak" NR "_logp="$7;}}'
