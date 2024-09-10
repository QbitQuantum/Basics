static std::string parseIdentifier( char const*& si)
{
	std::string rt;
	for (; *si && isAlnum(*si); ++si)
	{
		rt.push_back( *si);
	}
	return rt;
}