std::string fromXMLString(const XMLString& str)
{
	std::string result;
	result.reserve(str.size());
	
	for (XMLString::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		char c;
		wctomb(&c, *it);
		result += c;
	}
	return result;
}