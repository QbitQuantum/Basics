int main(int argc, char* argv[]) {


	string refFileName, notNormalFileName, normalFileName;

	if (argc < 4) {
		cout << "usage: normalizeGCContent ref source dest " << endl
				 << "       flips the C/Gs in source randomly until they are the same gc content as ref." << endl;
		exit(1);
	}
		
	refFileName = argv[1];
	notNormalFileName = argv[2];
	normalFileName = argv[3];


	FASTAReader reader;
	FASTAReader queryReader;
	FASTASequence ref;
	vector<FASTASequence> querySequences;
	int queryTotalLength;
	reader.Initialize(refFileName);
	reader.ReadAllSequencesIntoOne(ref);

	queryReader.Initialize(notNormalFileName);
	int refCounts[5], queryCounts[5];
	int s;
	refCounts[0] = refCounts[1] =refCounts[2] = refCounts[3] = refCounts[4] = 0;
	queryCounts[0] = queryCounts[1] =queryCounts[2] = queryCounts[3] = queryCounts[4] = 0;
	
	queryReader.ReadAllSequences(querySequences);
	ofstream normOut;
	CrucialOpen(normalFileName, normOut);

	CountNucs(ref, refCounts);
	
	float refGC = (1.0*refCounts[TwoBit['c']] + refCounts[TwoBit['g']]) / (refCounts[TwoBit['a']] + refCounts[TwoBit['c']] + refCounts[TwoBit['g']] + refCounts[TwoBit['t']]);

	int q;
	for (q = 0; q < querySequences.size(); q++) {
		CountNucs(querySequences[q], queryCounts);
	}

	float queryGC = (1.0*queryCounts[TwoBit['c']] + queryCounts[TwoBit['g']]) / (queryCounts[TwoBit['a']] + queryCounts[TwoBit['c']] + queryCounts[TwoBit['g']] + queryCounts[TwoBit['t']]);

	
	float gcToat = 0.0;
	float atTogc = 0.0;
	if (refGC > queryGC) {
		atTogc = (refGC - queryGC);
	}
	else {
		gcToat = (queryGC - refGC);
	}

	
	DNALength queryGenomeLength = queryCounts[0] +  queryCounts[1] + queryCounts[2] + queryCounts[3] + queryCounts[4];

	DNALength unmaskedQueryLength = queryCounts[0] +  queryCounts[1] + queryCounts[2] + queryCounts[3];

	DNALength ngc2at = unmaskedQueryLength * gcToat;
	DNALength nat2gc = unmaskedQueryLength * atTogc;
	cout << refGC << " " << queryGC << " " << gcToat << " " << atTogc << " " << ngc2at << " " << nat2gc << endl;

	vector<FASTASequence> normalized;

	normalized.resize(querySequences.size());
	vector<DNALength> cumLengths;
	
	cumLengths.resize(normalized.size()+1);
	cumLengths[0] = 0;
	for (q = 0; q < querySequences.size(); q++) {
		normalized[q]   = querySequences[q];
		cumLengths[q+1] = cumLengths[q] + querySequences[q].length;
	}
	
	DNALength i;

																
	for (i = 0; i < ngc2at; i+=2) {
		DNALength pos, chr;
		FindRandomNuc(normalized, queryGenomeLength, cumLengths, 'G', chr, pos);
		normalized[chr].seq[pos] = 'A';
		FindRandomNuc(normalized, queryGenomeLength, cumLengths, 'C', chr, pos);
		normalized[chr].seq[pos] = 'T';		
	}
	
	for (i = 0; i < nat2gc; i+=2) {
		DNALength pos, chr;
		FindRandomNuc(normalized, queryGenomeLength, cumLengths, 'A', chr, pos);
		normalized[chr].seq[pos] = 'g';
		FindRandomNuc(normalized, queryGenomeLength, cumLengths, 'T', chr, pos);
		normalized[chr].seq[pos] = 'c';		
	}

	for (q = 0; q < normalized.size(); q++ ){
		normalized[q].PrintSeq(normOut);
	}

}