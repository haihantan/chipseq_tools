#!/bin/sh
# Usage: dallianceall.sh chromsize.txt
# chromsize.txt must contain chromsomename<TAB>size
# for all chromosomes in your genome
# This script makes all files in the current directory dalliance friendly by:
# 1. Indexing all bam files
# 2. Converting all BED files to BigBed format
# 3. Converting all WIG and BedGraph files to BigWig format
# It needs the following tools:
# samtools
# bedbig.pl
# wigbig.pl
# bedgraphbigwig.pl
if [ $# -eq 0 ]
  then
    echo "No arguments supplied"
    echo "Usage: dallianceall.sh chromsize.txt"
    exit 0
fi
echo "Indexing all bam files"
find . -name \*.bam -exec samtools index {} \;
echo "Converting bed files to BigBed"
find . -name \*.bed -exec bedbig.pl {} $1 \;
echo "Converting wig files to BigWig"
find . -name \*.wig -exec wigbig.pl {} $1 \;
echo "Converting bedgraph files to BigWig"
find . -name \*.bdg -exec bedgraphbigwig.pl {} $1 \;
