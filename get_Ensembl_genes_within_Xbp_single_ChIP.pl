#!/usr/bin/perl -w

###############################################################################################################################################
#
# Written by Andrew C. Nelson - 12/10/2012
# modified by Husam Hebaishi, September 2015
#
# Script to identify peak-transcript relationships within X bp
#
# Usage: get_Ensembl_genes_within_Xbp_single_ChIP.pl input-file annotation-file.txt X
#
# Where:
# input-file is the peak.xls file outputted directly from MACS, with end-of-line formatting being Unix (important!)
# leave the comments and headers in the .XLS file as the script takes this into account
# annotation file is a file downloaded from Ensembl Biomart of the form:
# Ensembl Gene ID, Ensembl Transcript ID, Associated Gene Name, Chromosome Name, Gene Start (bp), Gene End (bp), Strand, Transcript Start (bp), Transcript End (bp)
# X is an integer value of the number of bases away from the transcription start site that you wish to search
#
# The script returns a file with each line of the format:
# Ensembl_Gene_ID, Ensembl_Transcript_ID, Associated_Gene_Name, Chromosome_Name, Gene_Start, Gene_End, Strand, Transcript_Start, Transcript_End, chr, start, end, length, abs_summit, pileup, -log10(pvalue), fold_enrichment, -log10(qvalue), name, peak_center, peak_center_TSS_distance
#
###############################################################################################################################################

open (FILE, "<$ARGV[0]") or die;
open (FILE1, "<$ARGV[1]") or die;
open (OUT, ">temp") || die;

while (<FILE>) {
    chomp;
    if ($_ =~ m/#/) {
        next;
    }
    @A=split(/\s+/, $_);
    if (!defined($A[0])) {
        next;
    }
    if ($A[0] =~ m/chr/g && $A[1] =~ m/start/g) {
        next;
    }
    $middle=(($A[2]-$A[1])/2)+$A[1];
    $centre{$middle}=$A[0];
    $line{"$A[0]-$middle"}=$_;
}
close FILE;

while (<FILE1>){
    chomp;
    if ($_ =~ m/Ensembl/g) {
        next;
    }

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

print "Ensembl_Gene_ID\tEnsembl_Transcript_ID\tAssociated_Gene_Name\tChromosome_Name\tGene_Start\tGene_End\tStrand\tTranscript_Start\tTranscript_End\tchr\tstart\tend\tlength\tabs_summit\tpileup\t-log10(pvalue)\tfold_enrichment\t-log10(qvalue)\tname\tpeak_center\tpeak_center_TSS_distance\n";

foreach $line (keys %hash){
    print "$hash{$line}\n";
}

system ("rm temp");
