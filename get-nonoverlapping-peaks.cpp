/* Program to look for overlaps between two BED files
 * Usage: get-overlapping-peaks BEDfile1 BEDfile2 outputfile
 * Bed file format expected: (without headers please! remove headers) 
 * Chromosome start end peakname score
 * Output file generated with following columns:
 * peak1_chromosome
 * peak1_start
 * peak1_end
 * peak1_score
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
	vector <string> chip1_peakname;

	vector <string> chip2_chr;
	vector <long> chip2_start;
	vector <long> chip2_end;
	vector <string> chip2_peakname;
	
	bool overlap;
	
	
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
		chip1_peakname.push_back(peakid.c_str());
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
		chip2_peakname.push_back(peakid.c_str());
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
		overlap=0;
		for (j=0 ; j < chip2_chr.size() ; j++) {
			
			if (chip1_chr[i] == chip2_chr[j]) {
				if ( chip1_start[i] >= chip2_start[j] && chip1_start[i] <= chip2_end[j]) {
					overlap=1;
					break;
				}
			
				if (chip1_end[i] <= chip2_end[j] && chip1_end[i] >= chip2_start[j]) {
					overlap=1;
					break;
				}
			}

		}
		if (overlap == 0) {
			temp.str("");
			temp.clear();
			temp << chip1_chr[i];
			temp << "\t";
			temp << chip1_start[i];
			temp << "\t";
			temp << chip1_end[i];
			temp << "\t";
			temp << chip1_peakname[i];
			temp << "\n";
			output.push_back(temp.str());
		}
	}
	
	cout << output.size() << " items found\n";

	
	// Open outputfile to write overlaps
	
	ofstream of(argv[3]);
	if (!of) {cout << "Unable to open " << argv[3] << " for output" << endl; return 0;}
	
	// Finally, after removing duplicates, write overlaps to output file
	
	for (i=0 ; i<output.size() ; i++) {
		of << output[i];
	}
	of.close();

}
