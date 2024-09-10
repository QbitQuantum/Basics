bool PeekString(std::ifstream & infile, const char * delim, std::string & outStr)
{
	if (true == infile.eof())
	{
		return false;
	}

	std::string line;
	std::streampos pos = infile.tellg();
	std::getline(infile, line);

	char * token = nullptr;
	char * nextToken = nullptr;
	token = strtok_s(&line[0], delim, &nextToken);

	if (token == nullptr)
	{
		return false;
	}

	outStr = std::string(token);

	infile.seekg(pos);

	return true;
}