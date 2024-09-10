vecD BenchMarkLatex::readVectorFromMatlabeFile(CStr &fileName, CStr &vecName)
{
	ifstream fin(fileName);
	CV_Assert(fin.is_open());
	string lineStr, token = vecName + " = [";
	while (getline(fin, lineStr))
		if (strncmp(_S(lineStr), _S(token), token.size() - 1) == 0)
			break;

	CV_Assert_(lineStr.size(), ("Can't load vector '%s' from: %s\n", _S(vecName), _S(fileName)));
	lineStr = lineStr.substr(token.size());
	istringstream sIn(lineStr);
	vecD scores;
	double s;
	while (sIn>>s)
		scores.push_back(s);
	return scores;
}