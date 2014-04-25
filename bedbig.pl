#!/usr/bin/perl

# Convert bed file to bigbed file
# Requires bedToBigBed to be in your path
# You can specify the file containing the chromosome sizes below
# The file takes two parameters: the bed file to be converted and the chromosome sizes
# It converts 'file.bed' (BED format) to 'file.bb' (BigBed format)
# The sorting and clipping of the BED file is done automatically by the script
# Usage: bedbig.pl bedfile.bed chromsizes.txt

if ($ARGV[0] eq "" || $ARGV[1] eq "") {die "Usage: bedbig.pl bedfile.bed chromsizes.txt\n";}

$chrom=$ARGV[1];
$in=$ARGV[0];
$out=$in;
$out=~s/\.bed$/\.bb/gi;

print "Converting BED file $in to BigBed file $out\n";

if ($out eq $in) { die "Invalid input format!\n"; }

# First we sort the bed file and remove any entries with negative values and 'track' lines
# Also we only take the first four columns. We don't need anything else
`sort -k1,1 -k2,2n $in | cut -f1,2,3,4 | grep -v "track" > temp.bed`;

# Now we load chromosome sizes and clip the bed intervals to the size of the chromosome
# We need to do this because you might have intervals 'larger' than the chromosome

open INFILE, "<$chrom" or die "Unable to load file $chrom\n";
while (<INFILE>) {
	@token = split /\s+/, $_;
	$size{$token[0]} = $token[1];
}
close INFILE;

open INFILE, "<temp.bed" or die "Unable to load temp.bed\n";
open OUTFILE, ">tempclipped.bed" or die "Unable to open tempclipped.bed for writing\n";
while (<INFILE>) {
	@tokens = split /\s+/, $_;
	if ($tokens[1] < 0 || $tokens[2] < 0) { next; }
	if ($tokens[1] >= $size{$tokens[0]}) { next; }
	if ($tokens[2] > $size{$tokens[0]}) { $tokens[2] = $size{$tokens[0]}; }
	print OUTFILE "$tokens[0]\t$tokens[1]\t$tokens[2]\t$tokens[3]\n";
}
close INFILE;
close OUTFILE;

#Now we run bedToBigBed to convert our cleaned up bed file to a BigBed file
`bedToBigBed -type=bed4 tempclipped.bed $chrom $out`;
system("rm temp.bed");
system("rm tempclipped.bed");
