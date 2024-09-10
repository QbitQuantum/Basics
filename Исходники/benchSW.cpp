void benchmarkSW(Sw05 & sw, ofstream & outfile1, ofstream & outfile2, int attributeCount, int iterationCount, CharmListStr & keygenResults, CharmListStr & decryptResults)
{
	Benchmark benchT, benchD, benchK;
    CharmList pk, sk, sk2, CT;
    CharmListStr w, wPrime;
    GT M, newM;
    ZR bf0, uf0, mk;
    int n = attributeCount, dParam = attributeCount;

    double de_in_ms, kg_in_ms;

    sw.setup(n, pk, mk);
    getAttributes(w, attributeCount);
    //cout << "w :\n" << w << endl;
    getAttributes(wPrime, attributeCount);
    //cout << "wPrime :\n" << wPrime << endl;
	for(int i = 0; i < iterationCount; i++) {
		benchK.start();
	    sw.extract(mk, w, pk, dParam, n, sk2);
		benchK.stop();
		kg_in_ms = benchK.computeTimeInMilliseconds();
	}
	cout << "Keygen avg: " << benchK.getAverage() << " ms" << endl;
    stringstream s1;
	s1 << attributeCount << " " << benchK.getAverage() << endl;
	outfile1 << s1.str();
    keygenResults[attributeCount] = benchK.getRawResultString();

    sw.extract(mk, w, pk, dParam, n, sk);
    M = sw.group.random(GT_t);

    sw.encrypt(pk, wPrime, M, n, CT);

    stringstream s2;

    //cout << "ct =\n" << CT << endl;
	for(int i = 0; i < iterationCount; i++) {
		benchD.start();
		sw.decrypt(pk, sk, CT, dParam, newM);
		benchD.stop();
		de_in_ms = benchD.computeTimeInMilliseconds();
	}

	cout << "Decrypt avg: " << benchD.getAverage() << " ms" << endl;
	s2 << attributeCount << " " << benchD.getAverage() << endl;
	outfile2 << s2.str();
	decryptResults[attributeCount] = benchD.getRawResultString();

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