void model3::em(int noIterations, sentenceHandler& sHandler1) {

	LogProb all_prob, aprob, temp;
	WordIndex i, j, l, m;
	time_t it_st, st, it_fn, fn;
	string tfile, dfile, nfile, p0file, afile, number;

	st = time(NULL) ;
	cout << "\n" << "Starting Model3:  Training";
	//  sentenceHandler sHandler1(efFilename.c_str());
	sHandler1.rewind();
	for (int it=1; it <= noIterations; it++) {
		it_st = time(NULL) ;
		cout << "\n" << "Model3: Iteration " << it;

		// set up the names of the files where the tables will be printed 
		int n = it;
		number = "";
		do {
			//mj changed next line
			number.insert((size_t) 0, 1, (char)(n % 10 + '0'));
		} while ((n /= 10) > 0);
		tfile = Prefix + ".t3." + number;
		afile = Prefix + ".a3." + number;
		nfile = Prefix + ".n3." + number;
		dfile = Prefix + ".d3." + number;
		p0file = Prefix + ".p0_3." + number;
		//    tCountTable.clear();
		dCountTable.clear();
		nCountTable.clear();
		p0_count = 0.0;
		p1_count = 0.0;
		all_prob = 0;
		sentPair sent;
		while (sHandler1.getNextSentence(sent)) {
			Vector<WordIndex>& es = sent.eSent;
			Vector<WordIndex>& fs = sent.fSent;
			const float count = sent.getCount();
			if ((sent.sentenceNo % 1000) == 0)
				cout <<sent.sentenceNo << '\n';
			Vector<WordIndex> A(fs.size(),/*-1*/0);
			Vector<WordIndex> Fert(es.size(),0);
			LogProb lcount=(LogProb)count;
			l = es.size()-1;
			m = fs.size()-1;
			WordIndex x, y;
			all_prob = prob_of_target_given_source(tTable, fs, es);
			if (all_prob == 0)
				cout << "\n" <<"all_prob = 0";

			for (x = 0; x < pow(l+1.0, double(m)) ; x++) { // For all possible alignmets A
				y = x;
				for (j = 1; j <= m; j++) {
					A[j] = y % (l+1);
					y /= (l+1);
				}
				for (i = 0; i <= l; i++)
					Fert[i] = 0;
				for (j = 1; j <= m; j++)
					Fert[A[j]]++;
				if (2 * Fert[0] <= m) { /* consider alignments that has Fert[0] less than
				 half the number of words in French sentence */
					aprob = prob_of_target_and_alignment_given_source(A, Fert,
							tTable, fs, es);
					temp = aprob/all_prob;
					LogProb templcount = temp*lcount;

					for (j = 1; j <= m; j++) {
						tTable.incCount(es[A[j]], fs[j], templcount);
						if (0 != A[j])
							dCountTable.addValue(j, A[j], l, m, templcount);
					}
					for (i = 0; i <= l; i++) {
						nCountTable.addValue(es[i], Fert[i], templcount);
						//cout << "AFTER INC2: " << templcount << " " << nCountTable.getRef(es[i], Fert[i]) << '\n';
					}
					p1_count += double(temp) * (Fert[0] * count);
					p0_count += double(temp) * ((m - 2 * Fert[0]) * count);
				}
			} /* of looping over all alignments */
		} /* of sentence pair E, F */
		sHandler1.rewind();

		// normalize tables
		if (OutputInAachenFormat==1)
			tTable.printCountTable(tfile.c_str(), Elist.getVocabList(),
					Flist.getVocabList(), 1);
		tTable.normalizeTable(Elist, Flist);
		aCountTable.normalize(aTable);
		dCountTable.normalize(dTable);
		nCountTable.normalize(nTable, &Elist.getVocabList());

		// normalize p1 & p0 

		if (p1_count + p0_count != 0) {
			p1 = p1_count / (p1_count + p0_count );
			p0 = 1 - p1;
		} else {
			p1 = p0 = 0;
		}
		// print tables 
		if (OutputInAachenFormat==0)
			tTable.printProbTable(tfile.c_str(), Elist.getVocabList(),
					Flist.getVocabList(), OutputInAachenFormat);
		dTable.printTable(dfile.c_str());
		nTable.printNTable(Elist.uniqTokens(), nfile.c_str(),
				Elist.getVocabList(), OutputInAachenFormat);
		ofstream of(p0file.c_str());
		of << p0;
		of.close();
		it_fn = time(NULL) ;
		cout << "\n" << "Model3 Iteration "<<it<<" took: " << difftime(it_fn,
				it_st) << " seconds\n";

	} /* of iterations */
	fn = time(NULL) ;
	cout << "\n" << "Entire Model3 Training took: " << difftime(fn, st)
			<< " seconds\n";
}