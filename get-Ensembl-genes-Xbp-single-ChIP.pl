#!/usr/bin/perl -w

###############################################################################################################################################
#
#  Written by Andrew C. Nelson - 12/10/2012
#  modified by Husam Hebaishi on April 2014
#
#  Script to identify peak-transcript relationships within X bp
#
#  Usage: get-Ensembl-genes-within-Xbp-single-ChIP.pl file.bed annotation-file.txt X
#
#  where: 
#  file.bed is a standard BED file - the most important columns are the first three: chromosome, start and end coords
#  BED file should NOT contain a header - if there is one, remove it
#  annotation file is a file downloaded from Ensembl Biomart of the form:
#     Ensembl Gene ID, Ensembl Transcript ID, Associated Gene Name, Chromosome Name, Gene Start (bp), Gene End (bp), Strand, Transcript Start (bp), Transcript End (bp)
#  Ensure that the chromosome names in the annotation file are of the format chrN (chr3,chr4 etc). Leave scaffolds as they are.
#  X is the number of bases from the transcription start site you wish to search
#
#  The script returns a file with each line of the format:
#     Ensembl Gene ID, Ensembl Transcript ID, Associated Gene Name, Chromosome Name, Gene Start (bp), Gene End (bp), Strand, Transcript Start (bp), Transcript End (bp) [Line from input bedfile]
#
###############################################################################################################################################

open (FILE, "<$ARGV[0]") or die;
open (FILE1, "<$ARGV[1]") or die;
open (OUT, ">temp") || die;


while (<FILE>) {
    chomp;
    @A=split(/\s+/);
    $middle=(($A[2]-$A[1])/2)+$A[1];
    $centre{$middle}=$A[0];
    $line{"$A[0]-$middle"}=$_;
}
close FILE;

while (<FILE1>){
    chomp;
    @A=split(/\t/);
    foreach $key (keys %centre){
	if (($centre{$key} eq $A[3]) && ($A[6] eq "1") && ($key >= ($A[7]-$ARGV[2])) && ($key <= ($A[7]+$ARGV[2]))) {
	    print OUT join ("\t", @A, $line{"$A[3]-$key"}, $key, ($A[7]-$key), "\n");
	}
	elsif (($centre{$key} eq $A[3]) && ($A[6] eq "-1") && ($key <= ($A[8]+$ARGV[2])) && ($key >= ($A[8]-$ARGV[2]))) {
	    print OUT join ("\t", @A, $line{"$A[3]-$key"}, $key, ($A[8]-$key), "\n");
	}
    }
}
close FILE1;
close OUT;

open (FILE2, "temp") || die;
while (<FILE2>){
    chomp;
    @A=split(/\t/);
    $hash{$_}=$_;
}
close FILE2;

foreach $line (keys %hash){
    print "$hash{$line}\n";
}


system ("rm temp");
