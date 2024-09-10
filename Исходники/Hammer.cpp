int main(int argc, char* argv[]) {
	string refFileName, queryFileName;
	int maxHammingDistance;
	if (argc < 4) {
		cout << "usage: hammer ref query maxHam " << endl;
		exit(1);
	}
	refFileName = argv[1];
	queryFileName = argv[2];
	maxHammingDistance = atoi(argv[3]);

	FASTAReader reader;
	reader.Initialize(refFileName);
	FASTASequence ref, refRC;
	reader.GetNext(ref);
	ref.MakeRC(refRC);
	
	FASTAReader queryReader;
	queryReader.Initialize(queryFileName);
	FASTASequence query;
	queryReader.GetNext(query);
	DNALength p;
	for(p=0; p < ref.length-query.length-1; p++ ){
		DNASequence subseq;
		subseq.seq = &ref.seq[p];
		subseq.length = query.length;
		//		cout << "t "; subseq.PrintSeq(cout);
		//		cout << "q "; ((DNASequence*)&query)->PrintSeq(cout);
		if (HammingDistance(&subseq.seq[0], &query.seq[0], query.length) < maxHammingDistance) {
			cout << ">" << p << endl;
			subseq.PrintSeq(cout);
		}
		int i;
		for (i =0; i < query.length; i++) {
			subseq.seq[i] = toupper(subseq.seq[i]);
		}
	}

	for(p=0; p < ref.length-query.length-1; p++ ){
		DNASequence subseq;
		subseq.seq = &refRC.seq[p];
		subseq.length = query.length;
		if (HammingDistance(&subseq.seq[0], &query.seq[0], query.length) < maxHammingDistance) {
			cout << ">" << p << "rc" << endl;
			subseq.PrintSeq(cout);
		}
		int i;
		for (i =0; i < query.length; i++) {
			subseq.seq[i] = toupper(subseq.seq[i]);
		}
	}

}