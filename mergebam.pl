#!/usr/bin/perl
$tempsam = "temp.sam";
$tempbam = "temp.bam";
$outbam = $ARGV[$#ARGV];

for ($i = 0; $i < $#ARGV ; $i++) {
	if ($i == 0) {
		print "Extracting header from $ARGV[$i]\n";
		system("samtools view -H $ARGV[$i] > $tempsam");
	}
	print "Adding reads from $ARGV[$i] to output\n";
	system("samtools view $ARGV[$i] >> $tempsam");
}

print "Converting SAM to BAM\n";
system("samtools view -bS $tempsam > $tempbam");

print "Sorting BAM file $outbam\n";
system("samtools sort -f $tempbam $outbam");

print "Removing temporary files\n";
#system("rm $tempsam");
#system("rm $tempbam");
