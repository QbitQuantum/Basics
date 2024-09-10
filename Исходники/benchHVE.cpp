void benchmarkHVE(Hve08 & hve, ofstream & outfile1, ofstream & outfile2, int vectorSize, int iterationCount, CharmListStr & decryptResults)
{
	Benchmark benchT, benchD;
	CharmList pk, msk, CT, sk;
	CharmListInt S;
	GT M, newM;
	int n = vectorSize;

	CharmListInt xVector, yVector;
	getRandomVector(yVector, vectorSize);
	xVector = yVector;

//	int _vectorX[] = {1, 1, 0, 1};
//	int _vectorY[] = {1, 1, 0, 1};
//	xVector.init(_vectorX, 4); // generate randomly
//	yVector.init(_vectorY, 4);

	hve.setup(n, pk, msk);
//	cout << "pk: " << pk << endl;
//	cout << "msk: " << msk << endl;

	hve.keygen(pk, msk, yVector, sk);

	M = hve.group.random(GT_t);
	hve.encrypt(M, xVector, pk, CT);
//	cout << "ct :=\n" << CT << endl;

	double de_in_ms;
	stringstream s1, s2;

	for(int i = 0; i < iterationCount; i++) {
		benchD.start();
		hve.decrypt(CT, sk, newM);
		benchD.stop();
		de_in_ms = benchD.computeTimeInMilliseconds();
	}
	cout << "Decrypt avg: " << benchD.getAverage() << " ms" << endl;
	s2 << vectorSize << " " << benchD.getAverage() << endl;
	outfile2 << s2.str();
	decryptResults[0] = benchD.getRawResultString();

    //cout << convert_str(M) << endl;
    //cout << convert_str(newM) << endl;
    if(M == newM) {
      cout << "Successful Decryption!" << endl;
    }
    else {
      cout << "FAILED Decryption." << endl;
    }
}