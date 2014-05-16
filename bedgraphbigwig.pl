#!/usr/bin/perl

# Convert bed file to bigbed file
# Requires bedToBigBed to be in your path
# You can specify the file containing the chromosome sizes below
# The file takes two parameters: the bed file to be converted and the chromosome sizes
# It converts 'file.bdg' (BedGraph format) to 'file.bw' (BigWig format)
# The sorting and clipping of the BED file is done automatically by the script
# Usage: bedgraphbigwig.pl bedfile.bed chromsizes.txt file.bw

if ($ARGV[0] eq "" || $ARGV[1] eq "") {die "Usage: bedbig.pl bedfile.bed chromsizes.txt\n";}

$chrom=$ARGV[1];
$in=$ARGV[0];
$out=$ARGV[2];


print "Converting BedGraph file $in to BigWig file $out\n";

if ($out eq $in) { die "Invalid input format!\n Extension needs to be bdg"; }

# Let's sort the BedGraph file first
`sort -k1,1 -k2,2n $in > temp.bdg`;

# Now we load chromosome sizes and clip the bed intervals to the size of the chromosome
# We need to do this because you might have intervals 'larger' than the chromosome

open INFILE, "<$chrom" or die "Unable to load file $chrom\n";
while (<INFILE>) {
	@token = split /\s+/, $_;
	$size{$token[0]} = $token[1];
}
close INFILE;

open INFILE, "<temp.bdg" or die "Unable to load temp.bdg\n";
open OUTFILE, ">tempclipped.bdg" or die "Unable to open tempclipped.bdg for writing\n";
while (<INFILE>) {
	@tokens = split /\s+/, $_;
	if ($tokens[1] >= $size{$tokens[0]}) { next; }
	if ($tokens[2] > $size{$tokens[0]}) { $tokens[2] = $size{$tokens[0]}; }
	print OUTFILE "$tokens[0]\t$tokens[1]\t$tokens[2]\t$tokens[3]\n";
}
close INFILE;
close OUTFILE;

#Now we run bedToBigBed to convert our cleaned up bed file to a BigBed file
`bedGraphToBigWig tempclipped.bdg $chrom $out`;
system("rm temp.bdg");
system("rm tempclipped.bdg");
