std::string CreateGUID()
{
	std::string guidStr;
#ifdef WIN32
	std::wstring guidWStr;
	guidWStr.resize(50);
	GUID guid;
	CoCreateGuid(&guid);
	StringFromGUID2(guid, (wchar_t*)guidWStr.c_str(), (int)guidWStr.size());
	g_wcstombs(guidStr, guidWStr);
#else
	uuid_t out;
	uuid_generate_time(out);
	for(int i = 0; i < sizeof(out); i++)
	{
	  char num[10] = {0};
	  snprintf(num, 10, "%d", out[i]);
	  guidStr.append(num);
	}
#endif
	return guidStr.c_str();
}