string generatePhrase(string a1[20], string a2[20], string a3[20] )
{
	std::stringstream ss;	
	char s[256];
	int i1, i2, i3;

	i1 = rand() % 6;
	i2 = rand() % 5;
	i3 = rand() % 7;

	ss << a1[i1] SPC a2[i2] SPC a3[i3];

	ss.getline(s, 256);

	return s;
}