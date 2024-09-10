int main()
{
	string s, buf;
	int i;
	int k;
	for (k = 0; k < 9; k++){

		cin >> s;

		cout << s.length() << "\n";
		for (i = 0; i < s.length(); i++)
		{
			if (isalpha(s[i]))
				s[i] = tolower(s[i]);
			else
				s[i] = ' ';

		}

		stringstream ss(s);
		while (ss >> buf)
			dict.insert(buf);
		//cout << buf << "\n";
	}
	
 	set<string>::iterator it;
	int m = 0;
	for (it = dict.begin(); it != dict.end(); it++){
		cout << *it << "\n";
		//m++;
		//cout << m << "\n";
	}
	//cout << *(++dict.begin()) << "\n";
		//cout << s.length() << endl;
	return 0;
}