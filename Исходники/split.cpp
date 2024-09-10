vector<string> split(const string& s)
{
	vector<string> ret;

	typedef string::size_type s_type;
	s_type i = 0;

	while(i != s.size())
	{
		while(isspace(s[i]) && i != s.size())
			++i;

		s_type j = i;

		while(!isspace(s[j]) && j != s.size())
			j++;

		if(i != j)
		{
			ret.push_back(s.substr(i, j-i));
			i = j;
		}
	}
	return ret;
}