/* Program to look for overlaps between two BED files
 * Usage: get-overlapping-peaks BEDfile1 BEDfile2 outputfile
 * Bed file format expected: (without headers please! remove headers) 
 * Chromosome start end peakname score
 * Output file generated with following columns:
 * ChIP1
 * peak1_chromosome
 * peak1_start
 * peak1_end
 * peak1_score
 * ChIP2
 * peak2_chromosome
 * peak2_start 
 * peak2_end
 * peak2_score
 * corepeak_start
 * corepeak_end
 * corepeak_length
 * overallpeak_start
 * overallpeak_end
 * overallpeak_length
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;


int main(int argc, char* argv[]) {

	// Define all our variables first, chromosome, start pos, end pos,
	// score for each bed file

	vector <string> chip1_chr;
	vector <long> chip1_start;
	vector <long> chip1_end;
	vector <string> chip1_peakid;

	vector <string> chip2_chr;
	vector <long> chip2_start;
	vector <long> chip2_end;
	vector <string> chip2_peakid;
	
	
	// Too few parameters: need inputbedfile1 inputbedfile2 outputfile
	
	if (argc < 4) {
		cout << "Usage: get-overlapping-peaks [Bed_file1] [Bed_file2] [outputfile]\n";
		return 0;
	}
	
	char t;
	
	// Open input files
	
	ifstream file1(argv[1]);
	if (!file1) {cout << "Unable to open " << argv[1] << endl; return 0;}

	ifstream file2(argv[2]);
	if (!file2) {cout << "Unable to open " << argv[2] << endl; return 0;}
	
	
	string chro,peakid,start,end,score;
	
	string line;
	istringstream iss;
	
	// Read data from first bed file
	
	while (getline(file1,line,'\n')) {
		
		iss.clear();
		iss.str(line);
		getline(iss,chro,'\t');
		getline(iss,start,'\t');
		getline(iss,end,'\t');
		getline(iss,peakid,'\t');
		getline(iss,score,'\t');
		
		
		chip1_chr.push_back(chro);
		chip1_start.push_back(atoi(start.c_str()));
		chip1_end.push_back(atoi(end.c_str()));
		chip1_peakid.push_back(peakid.c_str());
	}
	
	file1.close();
	
	cout << chip1_chr.size() << " records read from " << argv[1] << endl;
	
	// Read data from second bed file
	
	while (getline(file2,line,'\n')) {
		
		iss.clear();
		iss.str(line);
		getline(iss,chro,'\t');
		getline(iss,start,'\t');
		getline(iss,end,'\t');
		getline(iss,peakid,'\t');
		getline(iss,score,'\t');
		
		
		chip2_chr.push_back(chro);
		chip2_start.push_back(atoi(start.c_str()));
		chip2_end.push_back(atoi(end.c_str()));
		chip2_peakid.push_back(peakid.c_str());
	}
	
	file2.close();
	
	cout << chip2_chr.size() << " records read from " << argv[2] << endl;
	
	
	vector <string> output;
	stringstream temp;
	
	long i,j,k;
	long corestart, coreend;
	long overallstart, overallend;
	long duplicate=0;
	
	// Compare first bed file with second
		
	for (i=0 ; i < chip1_chr.size() ; i++) {
		for (j=0 ; j < chip2_chr.size() ; j++) {
			
			if (chip1_chr[i] == chip2_chr[j] && chip1_start[i] >= chip2_start[j] && chip1_start[i] <= chip2_end[j]) {
				
				if (chip1_start[i] <= chip2_start[j]) {corestart=chip2_start[j];} else {corestart=chip1_start[i];}
				if (chip1_end[i] <= chip2_end[j]) {coreend=chip1_end[i];} else {coreend=chip2_end[j];}
				
				if (chip1_start[i] >= chip2_start[j]) {overallstart=chip2_start[j];} else {overallstart=chip1_start[i];}
				if (chip1_end[i] >= chip2_end[j]) {overallend=chip1_end[i];} else {overallend=chip2_end[j];}
				
				
				temp.str("");
				temp.clear();
				temp << "ChIP1\t";
				temp << chip1_chr[i];
				temp << "\t";
				temp << chip1_start[i];
				temp << "\t";
				temp << chip1_end[i];
				temp << "\t";
				temp << chip1_peakid[i];
				temp << "\t";
				temp << "ChIP2\t";
				temp << chip2_chr[j];
				temp << "\t";
				temp << chip2_start[j];
				temp << "\t";
				temp << chip2_end[j];
				temp << "\t";
				temp << chip2_peakid[j];
				temp << "\t";
				temp << corestart;
				temp << "\t";
				temp << coreend;
				temp << "\t";
				temp << coreend-corestart;
				temp << "\t";
				temp << overallstart;
				temp << "\t";
				temp << overallend;
				temp << "\t";
				temp << (overallend-overallstart);
				temp << "\n";
				
				
				output.push_back(temp.str());
			}
			if (chip1_chr[i] == chip2_chr[j] && chip1_end[i] <= chip2_end[j] && chip1_end[i] >= chip2_start[j]) {

				if (chip1_start[i] <= chip2_start[j]) {corestart=chip2_start[j];} else {corestart=chip1_start[i];}
				if (chip1_end[i] <= chip2_end[j]) {coreend=chip1_end[i];} else {coreend=chip2_end[j];}
				
				if (chip1_start[i] >= chip2_start[j]) {overallstart=chip2_start[j];} else {overallstart=chip1_start[i];}
				if (chip1_end[i] >= chip2_end[j]) {overallend=chip1_end[i];} else {overallend=chip2_end[j];}
				
				temp.str("");
				temp.clear();
				temp << "ChIP1\t";
				temp << chip1_chr[i];
				temp << "\t";
				temp << chip1_start[i];
				temp << "\t";
				temp << chip1_end[i];
				temp << "\t";
				temp << chip1_peakid[i];
				temp << "\t";
				temp << "ChIP2\t";
				temp << chip2_chr[j];
				temp << "\t";
				temp << chip2_start[j];
				temp << "\t";
				temp << chip2_end[j];
				temp << "\t";
				temp << chip2_peakid[j];
				temp << "\t";
				temp << corestart;
				temp << "\t";
				temp << coreend;
				temp << "\t";
				temp << (coreend-corestart);
				temp << "\t";
				temp << overallstart;
				temp << "\t";
				temp << overallend;
				temp << "\t";
				temp << (overallend-overallstart);
				temp << "\n";
				
				output.push_back(temp.str());
			}
		}
	}
	
	// Compare second bed file with first - needed!!
	
	cout << "Completed first loop\n";
	cout << output.size() << " items found\n";
		
	for (j=0 ; j < chip2_chr.size() ; j++) {
		for (i=0 ; i < chip1_chr.size() ; i++) {
			
			if (chip1_chr[i] == chip2_chr[j] && chip2_start[j] >= chip1_start[i] && chip2_start[j] <= chip1_end[i]) {

				if (chip1_start[i] <= chip2_start[j]) {corestart=chip2_start[j];} else {corestart=chip1_start[i];}
				if (chip1_end[i] <= chip2_end[j]) {coreend=chip1_end[i];} else {coreend=chip2_end[j];}
				
				if (chip1_start[i] >= chip2_start[j]) {overallstart=chip2_start[j];} else {overallstart=chip1_start[i];}
				if (chip1_end[i] >= chip2_end[j]) {overallend=chip1_end[i];} else {overallend=chip2_end[j];}
				
				temp.str("");
				temp.clear();
				temp << "ChIP1\t";
				temp << chip1_chr[i];
				temp << "\t";
				temp << chip1_start[i];
				temp << "\t";
				temp << chip1_end[i];
				temp << "\t";
				temp << chip1_peakid[i];
				temp << "\t";
				temp << "ChIP2\t";
				temp << chip2_chr[j];
				temp << "\t";
				temp << chip2_start[j];
				temp << "\t";
				temp << chip2_end[j];
				temp << "\t";
				temp << chip2_peakid[j];
				temp << "\t";
				temp << corestart;
				temp << "\t";
				temp << coreend;
				temp << "\t";
				temp << coreend-corestart;
				temp << "\t";
				temp << overallstart;
				temp << "\t";
				temp << overallend;
				temp << "\t";
				temp << (overallend-overallstart);
				temp << "\n";
				
				output.push_back(temp.str());
			}
			if (chip1_chr[i] == chip2_chr[j] && chip2_end[j] <= chip1_end[i] && chip2_end[j] >= chip1_start[i]) {

				if (chip1_start[i] <= chip2_start[j]) {corestart=chip2_start[j];} else {corestart=chip1_start[i];}
				if (chip1_end[i] <= chip2_end[j]) {coreend=chip1_end[i];} else {coreend=chip2_end[j];}
				
				if (chip1_start[i] >= chip2_start[j]) {overallstart=chip2_start[j];} else {overallstart=chip1_start[i];}
				if (chip1_end[i] >= chip2_end[j]) {overallend=chip1_end[i];} else {overallend=chip2_end[j];}
				
				temp.str("");
				temp.clear();
				temp << "ChIP1\t";
				temp << chip1_chr[i];
				temp << "\t";
				temp << chip1_start[i];
				temp << "\t";
				temp << chip1_end[i];
				temp << "\t";
				temp << chip1_peakid[i];
				temp << "\t";
				temp << "ChIP2\t";
				temp << chip2_chr[j];
				temp << "\t";
				temp << chip2_start[j];
				temp << "\t";
				temp << chip2_end[j];
				temp << "\t";
				temp << chip2_peakid[j];
				temp << "\t";
				temp << corestart;
				temp << "\t";
				temp << coreend;
				temp << "\t";
				temp << (coreend-corestart);
				temp << "\t";
				temp << overallstart;
				temp << "\t";
				temp << overallend;
				temp << "\t";
				temp << (overallend-overallstart);
				temp << "\n";
				
				output.push_back(temp.str());
			}
		}
	}
	
	cout << "Completed second loop\n";
	cout << output.size() << " items found\n";
	
	// Open outputfile to write overlaps
	
	ofstream of(argv[3]);
	if (!of) {cout << "Unable to open " << argv[3] << " for output" << endl; return 0;}
	
	// This loop removes duplicate overlaps
	
	vector <string> outputclean;
		
	int dup;
	
	cout << "File opened for output\n";
	
	cout << output.size() << " matches detected\n";
	
	for (i=0 ; i<output.size() ; i++) {
		dup=0;
		for (j=0 ; j < outputclean.size() ; j++) {
			if (output[i] == outputclean[j]) {dup=1;}
		}
		
		if (dup == 0) {outputclean.push_back(output[i]);}
	}
	
	// Finally, after removing duplicates, write overlaps to output file
	
	for (i=0 ; i<outputclean.size() ; i++) {
		of << outputclean[i];
	}
	of.close();

}
