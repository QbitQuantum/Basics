int main(int argc, char *argv[])
{	
	string chrName = "", chrNameB = "";
	CLineFields inputReferenceGenomeFile;
	CLineFields genotypesFile;

	if (parseParameters (argc, argv) == false) 	{
		cerr << "Version: 1.0-r7" << endl;
		cerr << "Contact: [email protected]" << endl << endl;		
		cerr << "Usage: " << argv[0] <<" -r haploid.fa -g genotypes -l length -o diploid.fa" << endl << endl;
		cerr << "Convert haploid reference genome to diploid reference genome according to the genotypes and sequencing read length" << endl << endl;
		cerr << "Example: " << argv[0] << " -r hg19.fa -g known.genotypes -l 36 -o diploid.fa" << endl;
		cerr << endl << "Parameters (mandatory): " << endl;
		cerr << "  -r\t\thaploid reference genome file " << endl;
		cerr << "  -g\t\tgenotypes file" << endl;
		cerr << "  -l\t\tread length" << endl;
		cerr << "  -o\t\toutput diploid reference genome file " << endl;
		cerr << endl << "Parameters (optional): " << endl;
		cerr << "  -d\t\tmaximal deletion in a read and mapped to alternative alleles [default=0]" << endl;
		cerr << "  -s\t\tsex of the individual [default=\"m\"]" << endl;
		exit(-1);
	}
	
	if (inputReferenceGenomeFile.openFile(inputReferenceGenomeFileName)==false) {
		cerr << "Can not open file: " << inputReferenceGenomeFileName << endl;
		exit (-1);
	}

	if (genotypesFile.openFile(genotypesFileName)==false) {
		cerr << "Can not open file: " << genotypesFileName << endl;
		exit (-1);
	}	

	// step 1: read haploid reference genome file, double the total number of chromosomes.
	bool readin = false;
	inputReferenceGenomeFile.readline();
	while (inputReferenceGenomeFile.endofFile()==false) {
		if (inputReferenceGenomeFile.line[0]=='>') {
			chrName = inputReferenceGenomeFile.line.substr(1);
			chrNameB = chrName+"b";
			if (chrName != "chrY" || gender=='m') {
				chrMap[chrName] = "";
				chrMap[chrNameB] = "";
				chrNameList.push_back(chrName);			
				chrNameList.push_back(chrNameB);
				readin = true;
			} else {
				readin = false;  // skip chromosome Y for female individuals.
			}
		} else if (readin){
			
			chrMap[chrName] += inputReferenceGenomeFile.line;
			chrMap[chrNameB] += inputReferenceGenomeFile.line;
		}
		inputReferenceGenomeFile.readline();
	}	
	inputReferenceGenomeFile.closeFile();

	// step 2: use genotype file to modify the chromosomes. double the chromosome numbers.
	if (genotypesFile.isOpen()) {
		int refColumn = -1, altColumn=-1;
		genotypesFile.readline();
		while(genotypesFile.endofFile()==false) {
			unsigned int pos = atoi(genotypesFile.field[2].c_str());
			chrName = genotypesFile.field[1];
			chrNameB = chrName+"b";
			
			if (chrMap[chrName].length()<pos) {
				cerr << "Warning!!! genotype is out of range at: " << chrName << ": " << genotypesFile.field[2] << endl;
			} else {
				// decide which is ref and which is non-ref
				if (toupper(chrMap[chrName][pos-1]) == toupper(genotypesFile.field[4][0])) {						
					refColumn = 4;
					altColumn = 3;
				}
				else {
					refColumn = 3;
					altColumn = 4;
				}

				// if genotype is alt/alt, then we still need to change reference allele.
				if (chrMap[chrName][pos-1] >='A' && chrMap[chrName][pos-1] <='Z') {
					chrMap[chrName][pos-1] = toupper(genotypesFile.field[refColumn][0]);
					chrMap[chrNameB][pos-1] = toupper(genotypesFile.field[altColumn][0]);
				}
				else {
					chrMap[chrName][pos-1] = tolower(genotypesFile.field[refColumn][0]);
					chrMap[chrNameB][pos-1] = tolower(genotypesFile.field[altColumn][0]);
				}
			}
			genotypesFile.readline();
		}
		genotypesFile.closeFile();
	} 
	contextLength = 2*readLength - 1 + 2*maxDeletion;
	outputReferenceGenomeFile.open(outputReferenceGenomeFileName);
	dipmapFile.open(dipmapFileName);

	// step 3: create mini chromosomes and append them to the end of reference allele.
	for (int i=0; i<(int)chrNameList.size(); i++) {
		chrName = chrNameList[i];		
		if (chrName[chrName.length()-1] == 'b')
			extendFromDiploid(chrName);
	}

	// step 4: print out the reference allele, which has already been extended by mini chromosomes.
	for (int i=0; i<(int)chrNameList.size(); i++) {
		chrName = chrNameList[i];		
		if (chrName[chrName.length()-1] != 'b')
			printHaploid(chrName);
	}
	outputReferenceGenomeFile << endl;
	dipmapFile.close();
	outputReferenceGenomeFile.close();
	
	return 0;
}