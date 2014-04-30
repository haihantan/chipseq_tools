#!/usr/bin/perl
# Usage: homerbigwig.pl [chromosomesizes.txt] [outputprefix]
# Required bedtools suite to be installed
# chromsizes should be: chrN<TAB>size
$dir = `pwd`;
chomp $dir;
$frag=`grep fragment *`;

$chrom=$ARGV[0];
$out="$ARGV[1].bw";

open INFILE, "<$chrom" or die "Unable to load file $chrom\n";
while (<INFILE>) {
	@token = split /\s+/, $_;
	$size{$token[0]} = $token[1];
}
close INFILE;

if ($frag =~ m/fragmentLengthEstimate\=(\d+)/gi) {
	$len=$1;
}
print "Fragment length is $len\n";

if ($len <= 0) { print "Error getting fragment length!\n"; exit(1); }

opendir (DIR, $dir) or die $!;

open OUTFILE, ">temp.bed" or die $!;

$strand="";

while ($file = readdir(DIR)) {
	next unless ($file =~ m/\.tags\.tsv$/);
	open INFILE, "<$file" or die $!;
	while (<INFILE>) {
		chomp;
		@tokens = split /\s+/, $_;
		$start = $tokens[2]-1;
		$end = $start + $len;
		if ($start >= $size{$tokens[1]}) { print "$start is greater than $size{$tokens[1]}\n"; next; }
		if ($end > $size{$tokens[1]}) { $end = $size{$tokens[1]}; }
		if($tokens[3] == 0) {$strand = "+";}
		if($tokens[3] == 1) {$strand = "-";}
		
	print OUTFILE "$tokens[1]\t$start\t$end\t$strand\n";
	}
	close INFILE;
}

close OUTFILE;

print "Generating BedGraph coverage\n";
`bedtools genomecov -bg -i temp.bed -g $chrom > temp.bg`;

print "Converting BedGraph to BigWig\n";
`bedGraphToBigWig temp.bg $chrom $out`;

system("rm temp.bed");
system("rm temp.bg");



