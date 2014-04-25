#!/usr/bin/perl -w

###############################################################################################################################################
#
#  Written by Andrew C. Nelson - 12/10/2012
#
#  Script to identify peak-transcript relationships within X bp
#
#  Usage: get-Ensembl-genes-within-Xbp.pl file.bed annotation-file.txt X
#
#  where: 
#  ChIP1-ChIP2-overlapping-peaks.txt is the output file from the script "get-overlapping-peaks.pl"
#  annotation file is a file downloaded from Ensembl Biomart of the form:
#     Ensembl Gene ID, Ensembl Transcript ID, Associated Gene Name, Chromosome Name, Gene Start (bp), Gene End (bp), Strand, Transcript Start (bp), Transcript End (bp)
#  X is the number of bases from the transcription start site you wish to search
#
#  The script returns a file with each line of the format:
#  Line from annotation file, line from peak file, space, position of core peak centre, distance of peak centre from transcription start site
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
