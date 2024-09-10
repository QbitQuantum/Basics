void benchmarkBGW(Bgw05 & bgw, ofstream & outfile0, ofstream & outfile1, ofstream & outfile2, int numOfRecs, int iterationCount, CharmListStr & keygenResults, CharmListStr & transformResults, CharmListStr & decoutResults)
{
	Benchmark benchT, benchD, benchK;
	CharmList pk, msk, Hdr, ct, skCompleteBlinded, skCompleteBlinded2, transformOutputList;
	CharmListInt S;
//	int receivers[] = {1, 3, 5, 12, 14};
// 	S.init(receivers, 5);
//	int n = 15, i = 1;
	GT K, KDecrypt;
	ZR bf0;
	getRandomReceivers(S, numOfRecs);
	int n = numOfRecs, i = S[(rand() % numOfRecs)];
	double kg_in_ms;

	bgw.setup(n, pk, msk);
//	cout << "pk: " << pk << endl;
//	cout << "msk: " << msk << endl;
	// BENCHMARK KEYGEN SETUP
	for(int i = 0; i < iterationCount; i++) {
		benchK.start();
		bgw.keygen(pk, msk, n, bf0, skCompleteBlinded2);
		benchK.stop();
		kg_in_ms = benchK.computeTimeInMilliseconds();
	}
	cout << "Keygen avg: " << benchK.getAverage() << " ms" << endl;
    stringstream s0;
	s0 << numOfRecs << " " << benchK.getAverage() << endl;
	outfile0 << s0.str();
    keygenResults[numOfRecs] = benchK.getRawResultString();
	// BENCHMARK KEYGEN SETUP
	bgw.keygen(pk, msk, n, bf0, skCompleteBlinded);

//	cout << "tk: " <<  skCompleteBlinded << endl;
//	cout << "bf: " << bf0 << endl;
	cout << "receiver: " << i << endl;
	bgw.encrypt(S, pk, n, ct);

	Hdr = ct[0].getList();
	K = ct[1].getGT();

	double tf_in_ms, de_in_ms;
	stringstream s1, s2;
	for(int j = 0; j < iterationCount; j++) {
		benchT.start();
		bgw.transform(S, i, n, Hdr, pk, skCompleteBlinded, transformOutputList);
		benchT.stop();
		tf_in_ms = benchT.computeTimeInMilliseconds();

		benchD.start();
		bgw.decout(S, i, n, Hdr, pk, skCompleteBlinded, transformOutputList, bf0, KDecrypt);
		benchD.stop();
		de_in_ms = benchD.computeTimeInMilliseconds();
	}
	cout << "Transform avg: " << benchT.getAverage() << endl;
	s1 << numOfRecs << " " << benchT.getAverage() << endl;
	outfile1 << s1.str();
    transformResults[numOfRecs] = benchT.getRawResultString();

	cout << "Decout avg: " << benchD.getAverage() << endl;
	s2 << numOfRecs << " " << benchD.getAverage() << endl;
	outfile2 << s2.str();
	decoutResults[numOfRecs] = benchD.getRawResultString();
	// measure ciphertext size
	cout << "CT size: " << measureSize(ct) << " bytes" << endl;
	cout << "CTOut size: " << measureSize(transformOutputList) << " bytes" << endl;

//    cout << convert_str(K) << endl;
//    cout << convert_str(KDecrypt) << endl;
    if(K == KDecrypt) {
      cout << "Successful Decryption!" << endl;
    }
    else {
      cout << "FAILED Decryption." << endl;
    }
}