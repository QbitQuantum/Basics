void benchmarkHIBE(Hibe & hibe, ofstream & outfile1, ofstream & outfile2, int ID_string_len, int iterationCount, CharmListStr & keygenResults, CharmListStr & decryptResults)
{
	int l = 5;
	int z = 32;
	Benchmark benchT, benchD, benchK;
    CharmList mk, mpk, pk, sk, sk2, ct;
    GT M, newM;
    ZR uf0;
    string id = getID(ID_string_len); // "*****@*****.**"; // make this longer?
    double de_in_ms, kg_in_ms;

	hibe.setup(l, z, mpk, mk);
	for(int i = 0; i < iterationCount; i++) {
		benchK.start();
		hibe.keygen(mpk, mk, id, pk, sk2);
		benchK.stop();
		kg_in_ms = benchK.computeTimeInMilliseconds();
	}
	cout << "Keygen avg: " << benchK.getAverage() << " ms" << endl;
    stringstream s1;
	s1 << ID_string_len << " " << benchK.getAverage() << endl;
	outfile1 << s1.str();
    keygenResults[ID_string_len] = benchK.getRawResultString();

	hibe.keygen(mpk, mk, id, pk, sk);
    M = hibe.group.random(GT_t);
    hibe.encrypt(mpk, pk, M, ct);

    stringstream s2;

    //cout << "ct =\n" << ct << endl;
	for(int i = 0; i < iterationCount; i++) {
		benchD.start();
		hibe.decrypt(pk, sk, ct, newM);
		benchD.stop();
		de_in_ms = benchD.computeTimeInMilliseconds();
	}

	cout << "Decrypt avg: " << benchD.getAverage() << " ms" << endl;
	s2 << iterationCount << " " << benchD.getAverage() << endl;
	outfile2 << s2.str();
	decryptResults[ID_string_len] = benchD.getRawResultString();

    //cout << convert_str(M) << endl;
    //cout << convert_str(newM) << endl;
    if(M == newM) {
      cout << "Successful Decryption!" << endl;
    }
    else {
      cout << "FAILED Decryption." << endl;
    }
    return;
}