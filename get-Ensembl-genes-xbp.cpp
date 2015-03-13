/* Program to look for overlaps between two BED files
 * Usage: get-Ensembl-genes-xbp file.bed annotation.txt 10000
 * Ensembl Gene ID, Ensembl Transcript ID, Associated Gene Name, Chromosome Name, Gene Start (bp), Gene End (bp), Strand, Transcript Start (bp), Transcript End (bp)
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cmath>

using namespace std;

struct annotation{
	string geneID, transcriptID;
	string geneName, chrName;
	long int geneStart, geneEnd;
	string strand;
	long transcriptStart, transcriptEnd;
};

struct interval {
	string chrName;
	long int start, end;
	string name, score, strand;
};

int main(int argc, char* argv[]) {

	// Declare variables for storing genes and bed intervals

	vector <annotation> genes;
	vector <interval> bedInput;
	
	int distance = atoi(argv[3]);
	if (distance < 0) { cout << "Invalid distance!\n"; return 0;}
	
	
	// Too few parameters: need inputbedfile1 inputbedfile2 outputfile
	
	if (argc < 4) {
		cout << "Usage: get-Ensembl-genes-xbp file.bed annotation.txt 10000\n";
		return 0;
	}
	
	// Declare temporary variables
	string line;
	istringstream iss;
	string temp;
	int currRecord;
	
	// Read BED file first

	ifstream bedFile(argv[1]);
	if (!bedFile) {cout << "Unable to open " << argv[2] << endl; return 0;}
	
	while (getline(bedFile,line,'\n')) {
		
		iss.clear();
		iss.str(line);
		bedInput.push_back(interval());
		currRecord = bedInput.size() -1;
		
		if (getline(iss,temp,'\t')) { bedInput[currRecord].chrName = temp;}
		if (getline(iss,temp,'\t')) { bedInput[currRecord].start = atoi(temp.c_str());}
		if (getline(iss,temp,'\t')) { bedInput[currRecord].end = atoi(temp.c_str());}
		if (getline(iss,temp,'\t')) { bedInput[currRecord].name = temp; }
		if (getline(iss,temp,'\t')) { bedInput[currRecord].score = temp; }
		if (getline(iss,temp,'\t')) { bedInput[currRecord].strand = temp;}
		
	}
	
	bedFile.close();

	ifstream genesFile(argv[2]);
	if (!genesFile) {cout << "Unable to open " << argv[1] << endl; return 0;}
	
	// Read data from first bed file
	
	while (getline(genesFile,line,'\n')) {
		
		iss.clear();
		iss.str(line);
		genes.push_back(annotation());
		currRecord = genes.size() -1;
		
		if (getline(iss,temp,'\t')) { genes[currRecord].geneID = temp;}
		if (getline(iss,temp,'\t')) { genes[currRecord].transcriptID = temp;}
		if (getline(iss,temp,'\t')) { genes[currRecord].geneName = temp;}
		if (getline(iss,temp,'\t')) { genes[currRecord].chrName = temp;}
		if (getline(iss,temp,'\t')) { genes[currRecord].geneStart = atoi(temp.c_str());}
		if (getline(iss,temp,'\t')) { genes[currRecord].geneEnd = atoi(temp.c_str());}
		if (getline(iss,temp,'\t')) { genes[currRecord].strand = temp;}
		if (getline(iss,temp,'\t')) { genes[currRecord].transcriptStart = atoi(temp.c_str());}
		if (getline(iss,temp,'\t')) { genes[currRecord].transcriptEnd = atoi(temp.c_str());}
		
	}
	
	genesFile.close();
	
	int i,j;
	int peakMid;
	
	cout << "Ensembl_Gene_ID\tEnsembl_Transcript_ID\tAssociated_Gene_Name\tChromosome\tGene_Start\tGene_End\tStrand\tTranscript_start\tTranscript_End\t";
	cout << "Peak_chromosome\tPeak_start\tPeak_end\tPeak_name\tPeak_score\tPeak_strand\n";
	
	for (i=0 ; i < bedInput.size() ; i++) {
		for (j=0 ; j < genes.size() ; j++) {
			if (bedInput[i].chrName == genes[j].chrName) {
				peakMid = abs(((bedInput[i].end - bedInput[i].start) /2) + bedInput[i].start);
				if (abs(peakMid-genes[j].transcriptStart) <= distance) {
					
					cout << genes[j].geneID << "\t";
					cout << genes[j].transcriptID << "\t";
					cout << genes[j].geneName << "\t";
					cout << genes[j].chrName << "\t";
					cout << genes[j].geneStart << "\t";
					cout << genes[j].geneEnd << "\t";
					cout << genes[j].strand << "\t";
					cout << genes[j].transcriptStart << "\t";
					cout << genes[j].transcriptEnd << "\t";

					cout << bedInput[i].chrName << "\t";
					cout << bedInput[i].start << "\t";
					cout << bedInput[i].end << "\t";
					cout << bedInput[i].name << "\t";
					cout << bedInput[i].score << "\t";
					cout << bedInput[i].strand << "\t";
					cout << endl;
					
				}
			}
		}
	}

	
	return 0;
}
