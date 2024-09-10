void IndexDict::makeTolerantIndexFromList(list<Document *> doclist, int k) {
	
	
	if(_ctwf)
		makeFuzzyIndexFromList(doclist);
	else
		makeIndexFromList(doclist);

	_k = k;


	cout << "computing kgram index ...\n";
	map< Index, list<Posting> >::iterator iterT = _dict.begin();
	for(iterT; iterT != _dict.end(); iterT++)
	{
		Index t = iterT->first;
		string token = t.getToken();
		int len = token.length();

		if(len < k)
		{
			
			_kgrams[token].push_back(token);
		}
		else
		{
			string kgram = token.substr(0, k-1);
			_kgrams[kgram].push_back(token);
			for(int i = 0; i < (len - k + 1); i++)
			{
				kgram = token.substr(i, k);
				_kgrams[kgram].push_back(token);
			}
			kgram = token.substr(len - k + 1);
			_kgrams[kgram].push_back(token);
		}
	}
	cout << "done!\n";

	
	map<string, list<string> >::iterator iter = _kgrams.begin();
	for(int i = 0; i < 100; i++)
		iter++;

	for(int i = 0; i < 5; i++)
	{
		cout << iter->first << " ====>> ";
		list<string>::iterator str = iter->second.begin();
		for(str; str != iter->second.end(); str++)
		{
			cout << *str << " -> ";
		}
		cout << endl << endl;
		iter++;
	}
	

}