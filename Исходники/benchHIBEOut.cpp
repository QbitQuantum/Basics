void benchmarkHIBE(Hibe & hibe, ofstream & outfile0, ofstream & outfile1, ofstream & outfile2, int ID_string_len, int iterationCount, CharmListStr & keygenResults, CharmListStr & transformResults, CharmListStr & decoutResults)
{
	int l = 5;
	int z = 32;
	Benchmark benchT, benchD, benchK;
    CharmList mk, mpk, pk, skBlinded, skBlinded2, ct, transformOutputList;
//    CharmListStr S;
    GT M, newM;
    ZR uf0, bf0;
    string id = getID(ID_string_len); // "*****@*****.**";
    double tf_in_ms, de_in_ms, kg_in_ms;
    stringstream s0;

	hibe.setup(l, z, mpk, mk);
	// BENCHMARK KEYGEN SETUP
	for(int i = 0; i < iterationCount; i++) {
		benchK.start();
		hibe.keygen(mpk, mk, id, pk, uf0, bf0, skBlinded2);
		benchK.stop();
		kg_in_ms = benchK.computeTimeInMilliseconds();
	}
	cout << "Keygen avg: " << benchK.getAverage() << " ms" << endl;
	s0 << ID_string_len << " " << benchK.getAverage() << endl;
	outfile0 << s0.str();
    keygenResults[ID_string_len] = benchK.getRawResultString();
	// BENCHMARK KEYGEN SETUP
	hibe.keygen(mpk, mk, id, pk, uf0, bf0, skBlinded);

    M = hibe.group.random(GT_t);
    hibe.encrypt(mpk, pk, M, ct);

    stringstream s1, s2;

    //cout << "ct =\n" << ct << endl;
	for(int i = 0; i < iterationCount; i++) {
		// run TRANSFORM
		benchT.start();
		hibe.transform(pk, skBlinded, ct, transformOutputList);
		benchT.stop();
		//cout << "transformCT =\n" << transformOutputList << endl;
		tf_in_ms = benchT.computeTimeInMilliseconds();

		benchD.start();
		hibe.decout(pk, transformOutputList, bf0, uf0, newM);
		benchD.stop();
		de_in_ms = benchD.computeTimeInMilliseconds();
	}

	cout << "Transform avg: " << benchT.getAverage() << endl;
	s1 << iterationCount << " " << benchT.getAverage() << endl;
	outfile1 << s1.str();
    transformResults[ID_string_len] = benchT.getRawResultString();

	cout << "Decout avg: " << benchD.getAverage() << endl;
	s2 << iterationCount << " " << benchD.getAverage() << endl;
	outfile2 << s2.str();
	decoutResults[ID_string_len] = benchD.getRawResultString();
	// measure ciphertext size
	cout << "CT size: " << measureSize(ct) << " bytes" << endl;
	cout << "CTOut size: " << measureSize(transformOutputList) << " bytes" << endl;

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