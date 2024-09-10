void benchmarkSW(Sw05 & sw, ofstream & outfile0, ofstream & outfile1, ofstream & outfile2, int attributeCount, int iterationCount, CharmListStr & keygenResults, CharmListStr & transformResults, CharmListStr & decoutResults)
{
	Benchmark benchT, benchD, benchK;
    CharmList pk, skBlinded, skBlinded2, CT, transformOutputList, transformOutputListForLoop;
    CharmListStr w, wPrime;
    GT M, newM;
    ZR bf0, uf0, mk;
    int n = attributeCount, dParam = 1;

    double tf_in_ms, de_in_ms, kg_in_ms;

    sw.setup(n, pk, mk);
    getAttributes(w, attributeCount);
    //cout << "w :\n" << w << endl;
    getAttributes(wPrime, attributeCount);
    //cout << "wPrime :\n" << wPrime << endl;
	// BENCHMARK KEYGEN SETUP
	for(int i = 0; i < iterationCount; i++) {
		benchK.start();
	    sw.extract(mk, w, pk, dParam, n, uf0, bf0, skBlinded2);
		benchK.stop();
		kg_in_ms = benchK.computeTimeInMilliseconds();
	}
	cout << "Keygen avg: " << benchK.getAverage() << " ms" << endl;
    stringstream s0;
	s0 << attributeCount << " " << benchK.getAverage() << endl;
	outfile0 << s0.str();
    keygenResults[attributeCount] = benchK.getRawResultString();
	// BENCHMARK KEYGEN SETUP
    sw.extract(mk, w, pk, dParam, n, uf0, bf0, skBlinded);

    M = sw.group.random(GT_t);

    sw.encrypt(pk, wPrime, M, n, CT);

    stringstream s1, s2;

    //cout << "ct =\n" << CT << endl;
	for(int i = 0; i < iterationCount; i++) {
		// run TRANSFORM
		CharmListStr SKeys;
		int SLen;
		benchT.start();
		sw.transform(pk, skBlinded, CT, dParam, transformOutputList, SKeys, SLen, transformOutputListForLoop);
		benchT.stop();
		tf_in_ms = benchT.computeTimeInMilliseconds();

		benchD.start();
		sw.decout(pk, dParam, transformOutputList, bf0, uf0, SKeys, SLen, transformOutputListForLoop, newM);
		benchD.stop();
		de_in_ms = benchD.computeTimeInMilliseconds();
	}

	cout << "Transform avg: " << benchT.getAverage() << endl;
	s1 << attributeCount << " " << benchT.getAverage() << endl;
	outfile1 << s1.str();
    transformResults[attributeCount] = benchT.getRawResultString();

	cout << "Decout avg: " << benchD.getAverage() << endl;
	s2 << attributeCount << " " << benchD.getAverage() << endl;
	outfile2 << s2.str();
	decoutResults[attributeCount] = benchD.getRawResultString();

	cout << "CT size: " << measureSize(CT) << " bytes" << endl;
	cout << "CTOut size: " << measureSize(transformOutputList) + measureSize(transformOutputListForLoop) << " bytes" << endl;

//    cout << convert_str(M) << endl;
//    cout << convert_str(newM) << endl;
    if(M == newM) {
      cout << "Successful Decryption!" << endl;
    }
    else {
      cout << "FAILED Decryption." << endl;
    }
    return;
}