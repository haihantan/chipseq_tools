# ChIP-seq tools

A bunch of shell and perl scripts for format conversion and ChIP-seq data analysis.
All scripts are heavily commented so please read the script itself for requirements and usage instructions.

* bamtobedhomer.sh - Converts BAM file to HOMER-friendly BED file
* bamtobed.sh - Converts BAM file to BED file, for use with MACS
* dallianceall.sh - Converts all wig, bed and bedgraph files to Dalliance-friendly binary formats, and indexes all BAM files
* homerplot.sh - Run inside homer tag directory to generate autocorrelation plot as PDF
* makedir.sh - Make tag directory, output directory has same name as input BED file but without extension
* bedbig.pl - Convert BED file to BigBed format
* bedgraphbigwig.pl - Convert BedGraph file to BigWig format
* get-Ensembl-genes-Xbp-single-ChIP.pl - Annotate peaks with Ensembl genes within X bp of peak center
* homerbigwig.pl - Generate BigWig files from homer peak calling data by extending tags manually
* wigbig.pl - Convert WIG files to BigWig format
* countuniq.sh - Counts duplicates in fastq file.

countuniq.sh can be run either on uncompressed fastq files:
```
countuniq.sh file.fastq
```
or on compressed fastq files:
```
zcat file.fastq.gz | countuniq.sh
```


The file 'get-overlapping-peaks.cpp' is a C++ source file which needs to be compiled before use.
You can use the g++ compiler to compile it and make the resulting binary executable by running:

```
g++ get-overlapping-peaks.cpp -oget-overlapping-peaks
chmod a+x get-overlapping-peaks
```

Then you can simply copy the binary to your bin directory.
