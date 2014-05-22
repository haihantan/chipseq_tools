#!/bin/sh
# Either run on uncompressed fastq files: countuniq.sh file.fastq
# or compressed ones: zcat file.fastq.gz | countuniq.sh
# The output is two columns. Col1 is duplication level, and Col2 is number of sequences
awk '{if ((NR-2) % 4 == 0){print;}}' $1 | sort --parallel=20 | uniq -c| awk '{print $1}' | sort -k2,2n| uniq -c | awk '{print $2 "\t" $1}' | sort -k1,1n
