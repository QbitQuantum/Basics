void GetHashInfo(tstring id, std::vector<std::wstring> & info) {
	while(id.size() > 0)
	{
		size_t pos = id.find(L'-');
		
		tstring substr =
			id.substr(0, pos == tstring::npos ? id.length() : pos);
		info.push_back(substr);
		
		if(pos == tstring::npos) id = L"";
		else
		{
			++pos;
			id = id.substr(pos, id.length() - pos);
		}
	}
}