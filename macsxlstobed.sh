#!/bin/sh
tail -n +29 $1 | awk '{print $1"\t"$2"\t"$3"\tMACS_peal_logp="$7}'
