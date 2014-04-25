#!/bin/sh
# Run this file inside a Homer tag directory to see the auto-correlation plot
# The plot is generated as a PDF file and then displayed
FRAG=`head -n1 tagAutocorrelation.txt | sed  -e 's|)|\t|g' -e 's|(|\t|g' | awk '{print $7}'`
PEAK=`head -n1 tagAutocorrelation.txt | sed  -e 's|)|\t|g' -e 's|(|\t|g' | awk '{print $11}'`
echo "pdf(\"tagAutocorr.pdf\",width=6,height=6)" > plot.r
echo "x<-read.table(\"tagAutocorrelation.txt\",skip=1,header=FALSE)" >> plot.r
echo "plot(x[[1]],x[[2]],col=\"red\",main=\"Tag Auto-correlation $1, red=+, blue=-\",xlab=\"Distance (in bp)\", ylab=\"Number of tags \",type=\"l\")" >> plot.r
echo "mtext(\"Fragment size: $FRAG\nPeak size: $PEAK\",side=2,line=-20)" >> plot.r
echo "lines(x[[1]],x[[3]],col=\"blue\")" >> plot.r
echo "dev.off()" >> plot.r
Rscript plot.r
rm plot.r
evince *.pdf
