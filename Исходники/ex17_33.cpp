int main() {
	typedef pair<string, string> ps;
	ifstream i("d.txt");
	vector<ps> dict;
	string str1, str2;
	// read wirds from dictionary
	while (i >> str1 >> str2) {
		dict.emplace_back(str1, str2);
	}
	i.close();
	// sort words in vector
	sort(dict.begin(), dict.end(), [](const ps &_ps1, const ps &_ps2){ return _ps1.first < _ps2.first; });
	i.open("i.txt");
	default_random_engine e(time(0));
	// read words from text
	while (i >> str1) {
	  // find word in dictionary
		vector<ps>::const_iterator it = find_if(dict.cbegin(), dict.cend(),
		  [&str1](const ps &_ps){ return _ps.first == str1; });
		// if word doesn't exist in dictionary
		if (it == dict.cend()) {
		  // write it itself
			cout << str1 << ' ';
		}
		else {
		  // get random meaning of word 
			uniform_int_distribution<unsigned> u (0, find_if(dict.cbegin(), dict.cend(),
			 [&str1](const ps &_ps){ return _ps.first > str1; }) - it - 1);
			// write random meaning
			cout << (it + u(e))->second << ' ';
		}
	}

	return 0;
}