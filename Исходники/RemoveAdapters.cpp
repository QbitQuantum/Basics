int main(int argc, char* argv[]) {
	string ad1File, ad2File, readsFile, readsOutFile;

	FASTAReader ad1Reader;
	FASTAReader ad2Reader;
	FASTAReader reader;


	CommandLineParser cl;
	float minPctSimilarity = 0.60;
	int indel = 3;
	int minLength = 10;
	cl.RegisterStringOption("ad1", &ad1File, "FASTA file with the first adapter");
	cl.RegisterStringOption("ad2", &ad2File, "FASTA file with the second adapter");
	cl.RegisterStringOption("reads", &readsFile, "FASTA file with SMRTBell reads");
	cl.RegisterStringOption("readsout", &readsOutFile, "output file for split reads");
	cl.RegisterPreviousFlagsAsHidden();
	cl.RegisterFloatOption("pctSim", &minPctSimilarity, "Minimum percent similarity to trigger a match to an adapter.", 
												 CommandLineParser::PositiveFloat);
	cl.RegisterIntOption("indel", &indel, "Penalty for indel (positive)", CommandLineParser::NonNegativeInteger);
	cl.RegisterIntOption("minLength", &minLength, "Minimum length pass to retain.", CommandLineParser::PositiveInteger);
	vector<string> opts;
	cl.ParseCommandLine(argc, argv, opts);

	/*
	 * Open all the required files, quitting if they are unavailable.
	 */

	ad1Reader.Init(ad1File);
	ad2Reader.Init(ad2File);
	reader.Init(readsFile);

	ofstream splitOut;
	CrucialOpen(readsOutFile, splitOut);

	FASTASequence ad1, ad2;
	ad1Reader.GetNext(ad1);
	ad2Reader.GetNext(ad2);

	FASTASequence read;
	vector<int> scoreMat;
	vector<Arrow> pathMat;
	int readIndex = 0;
	while(reader.GetNext(read)) {
		read.ToUpper();
		//
		// Do a fitting sequence alignment to match one of the two 
		// adapters into the read.
		//
		vector<int> passStarts, passLengths, la;
		read.PrintSeq(cout);
		SplitRead(read, 0, read.length, ad1, ad2,
							indel, 
							passStarts, passLengths,la, 0,
							scoreMat, pathMat, minPctSimilarity, minLength);
		int i;
		for (i = 0; i < passStarts.size(); i++) {
			cout << "read: " << readIndex << " pass: "******" " << passStarts[i] << " " << passLengths[i] << " " << la[i] << endl;
		}
		++readIndex;
	}
}