uint64 StringParser::WStringTo(const WStringRef& inString, int base /*= 10*/)
{
#ifdef MEDUSA_WINDOWS
	return _wcstoui64(inString.c_str(), nullptr, base);
#endif
#ifdef MEDUSA_IOS
	return wcstoull(inString.c_str(), nullptr, base);
#endif

#ifdef MEDUSA_ANDROID
	std::wstringstream ss;
	ss << inString.c_str();
	uint64 r;
	ss >> r;
	return r;
#endif

}