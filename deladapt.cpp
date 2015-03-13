#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
	
	if (argc < 4) {
		cout << "Usage: deladapt adapters.fa inputfile.fastq outputfile.fastq" << endl;
		return 0;
	}
	
	// Open fasta file containing adapters
	ifstream fasta(argv[1]);
	
	vector <string> fastqrecord;
	fastqrecord.resize(4);
	
	if (!fasta) { cout << "Unable to open " << argv[1] << endl; return -1; }
	
	// Read in all adapters
	string line;
	vector <string> sequences;
	
	while (getline(fasta,line,'\n')) {
		if (line[0] != '>') {
			sequences.push_back(line);
		}
	}
	
	fasta.close();
	
	ifstream fastq(argv[2]);
	if (!fastq) { cout << "Unable to open " << argv[2] << endl; return -1; }
	
	ofstream output(argv[3]);
	if (!output) {cout << "Unable to open " << argv[3] << endl; return -1; }
	
	int count = 0;
	int match = 0;
	int i;
	
	while(getline(fastq,line,'\n')) {
		if (count < 3) {
			fastqrecord[count] = line;
			count++;
		} else {
			fastqrecord[count] = line;
			for (i=0 ; i < sequences.size() ; i++) {
				if(fastqrecord[1].find(sequences[i]) != string::npos) {
					match=1;
					break;
				}
			}
			if (match == 0) {
				for (i=0 ; i < 4 ; i++) {
					output << fastqrecord[i] << endl;
				}
			}
			count = 0;
			match = 0;
		}
	}
	fastq.close();
	output.close();
	
	return 0;
		
}
	
	
