#!/usr/bin/perl

# Convert wig file to bigwig file
# Requires wigToBigWig to be in your path
# You can specify the file containing the chromosome sizes below
# The file takes two parameters: the wig file to be converted and the chromosome sizes
# It converts 'file.wig' (WIG format) to 'file.bw' (BigWig format)
# Removal of 'track' lines is done automatically and entries are clipped to chromosome size
# Usage: wigbig.pl file.wig chromsizes.txt

if ($ARGV[0] eq "") {die "Usage: wigbig.pl file.wig chromsizes.txt\n";}

$chrom=$ARGV[1];
$in=$ARGV[0];
$out=$in;
$out=~s/\.wig$/\.bw/gi;

print "Converting WIG file $in to BigWig file $out\n";

if ($out eq $in) { die "Invalid input format!\nExtension needs to be bed."; }

# First we remove track lines as these can cause errors

`grep -v "track" $in > temp.wig`;

# That's all the cleaning up we need to do
# Now we can run wigToBigWig to convert to BigWig format

`wigToBigWig -clip temp.wig $chrom $out`;
system("rm temp.wig");
