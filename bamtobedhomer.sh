#!/bin/sh
#!/bin/sh
# Converts bam file to bed
# Usage: bamtobed.sh file.bam
# You do not specify output file.
# Output file is simply input file with bed extension.
# For above example, file.bed would be the output
# If you are converting BAM files to BED for homer peak calling, use this script
# Requires bedtools to be installed
if [ $# -eq 0 ]
  then
    echo "No arguments supplied"
    echo "Usage: bamtobed.sh file.bam"
    exit 0
fi
BED=`echo $1 | sed "s/.bam$/.BED/gi"`;
echo File $1 will be converted to $BED
bedtools bamtobed -i $1 | grep chr | awk '{print $1"\t"$2"\t"$3"\t"$6;}' > $BED
