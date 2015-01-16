#!/bin/sh
# Takes a MACS xls file and converts it to a bed file
# Peak name contains the number and p-value of the peak
tail -n+29 $1 | awk '{print $1"\t"$2"\t"$3"\tMACS_peak" NR "_logp="$7;}'
