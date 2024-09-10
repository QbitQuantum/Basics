void benchmarkBGW(Bgw05 & bgw, ofstream & outfile0, ofstream & outfile1, ofstream & outfile2, int numOfRecs, int iterationCount, CharmListStr & keygenResults, CharmListStr & encryptResults, CharmListStr & decryptResults)
{
	Benchmark benchE, benchD, benchK;
	CharmList pk, msk, Hdr, ct;
	CharmMetaListG1 sk, sk2;
	CharmListInt S;
//	int receivers[] = {1, 3, 5, 12, 14};
// 	S.init(receivers, 5);
//	int n = 15, i = 1;
	GT K, KDecrypt;
	ZR bf0;
	getRandomReceivers(S, numOfRecs);
	int i, n = numOfRecs;
	double kg_in_ms;

	bgw.setup(n, pk, msk);
//	cout << "pk: " << pk << endl;
//	cout << "msk: " << msk << endl;
	// BENCHMARK KEYGEN SETUP
	for(int j = 0; j < iterationCount; j++) {
		benchK.start();
		bgw.keygen(pk, msk, n, sk2);
		benchK.stop();
		kg_in_ms = benchK.computeTimeInMilliseconds();
	}
	cout << "Keygen avg: " << benchK.getAverage() << " ms" << endl;
    stringstream s0;
	s0 << numOfRecs << " " << benchK.getAverage() << endl;
	outfile0 << s0.str();
    keygenResults[numOfRecs] = benchK.getRawResultString();

	// BENCHMARK KEYGEN SETUP

	bgw.keygen(pk, msk, n, sk);
//	cout << "tk: " <<  skCompleteBlinded << endl;
//	cout << "bf: " << bf0 << endl;

	double de_in_ms;
	stringstream s2;
	cout << "receiver: ";
	for(int j = 0; j < iterationCount; j++) {
		benchE.start();
		bgw.encrypt(S, pk, n, ct);
		benchE.stop();
		kg_in_ms = benchE.computeTimeInMilliseconds();

		Hdr = ct[0].getList();
		K = ct[1].getGT();

		i = S[(rand() % numOfRecs)];
		cout << i;
		benchD.start();
		bgw.decrypt(S, i, n, Hdr, pk, sk, KDecrypt);
		benchD.stop();
		de_in_ms = benchD.computeTimeInMilliseconds();
	}
	cout << "Encrypt avg: " << benchE.getAverage() << " ms" << endl;
    stringstream s1;
	s1 << numOfRecs << " " << benchE.getAverage() << endl;
	outfile1 << s1.str();
    encryptResults[numOfRecs] = benchE.getRawResultString();

	cout << "Decrypt avg: " << benchD.getAverage() << " ms" << endl;
	s2 << numOfRecs << " " << benchD.getAverage() << endl;
	outfile2 << s2.str();
	decryptResults[numOfRecs] = benchD.getRawResultString();
//    cout << convert_str(K) << endl;
//    cout << convert_str(KDecrypt) << endl;
    if(K == KDecrypt) {
      cout << "Successful Decryption!" << endl;
    }
    else {
      cout << "FAILED Decryption." << endl;
    }
}