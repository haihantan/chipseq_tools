#!/usr/bin/perl

@adapts = ();
open(INFILE, "<$ARGV[0]") or die("Unable to open $ARGV[0]: $!\n");

while (<INFILE>) {
	unless($_ =~ m/^>/g) {
		chomp;
		push(@adapts, $_);
	}
}

close INFILE;

$count = 0;
@lines = ();
open (INFILE, "<$ARGV[1]") or die("Unable to open $ARGV[1]: $!\n");

while (<INFILE>) {
	if ($count < 3) {
		$lines[$count] = $_;
		$count ++;
	}
	else {
		$lines[$count] = $_;
		$match = 0;
		for $ad (@adapts) {
			if ($lines[1] =~ m/$ad/gi) {
				$match = 1;
				last;
			}
		}
		if ($match == 0) {
			print @lines;
		}
		$count = 0;
	}
}

close INFILE;
