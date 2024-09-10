void RemoveApostrophes(std::string &s)
{
	for(unsigned int i = 0; i < s.length(); ++i)
		if(s[i] == '\'')
			 s[i] = '_';
}