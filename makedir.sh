#!/bin/sh
DIR=`echo $1 | sed "s/.BED$//gi"`;
grep chr $1 > temp.bed
makeTagDirectory $DIR temp.bed -format bed
rm temp.bed
