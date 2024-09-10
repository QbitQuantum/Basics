void CSoftUninstall::GetPinYin(const std::wstring &name, std::wstring &whole, std::wstring &acronym)
{
	typedef list<string>					str_list;
	typedef str_list::iterator				str_iter;
	typedef string_tokeniser<string, char>	string_tokeniser_a;

	typedef void (string::*PFPushback)(char);
	typedef string& (string::*PFAppend)(const char*);

	PFAppend pfAppend = &string::append;
	PFPushback pfPushback = &string::push_back;

	char mbcs[5];
	str_list wholeList, acronymList;
	wholeList.push_back(string());
	acronymList.push_back(string());

	for(wstring::size_type i = 0; i < name.size(); ++i)
	{
		if(iswascii(name[i]) == 0)
		{	// 非ASCII码
			int ret;
			if(wctomb_s(&ret, mbcs, sizeof(mbcs), name[i]) != 0) continue;
			mbcs[ret] = '\0';

			PinYinCIter itPinYin = _hashPinYin.find(mbcs);
			if(itPinYin != _hashPinYin.end())
			{
				const PinYin &pinyin = itPinYin->second;

				// M X N组合
				{
					string_tokeniser_a tokeniser(pinyin._whole, ' ');

					str_list resultList;
					string_tokeniser_a::const_iterator end = tokeniser.end();
					for(string_tokeniser_a::const_iterator it = tokeniser.begin(); it != end; ++it)
					{
						str_iter endList = wholeList.end();
						for(str_iter itList = wholeList.begin(); itList != endList; ++itList)
							resultList.push_back(*itList + *it);
					}
					wholeList.swap(resultList);
				}
				{
					string_tokeniser_a tokeniser(pinyin._acronym, ' ');

					str_list resultList;
					string_tokeniser_a::const_iterator end = tokeniser.end();
					for(string_tokeniser_a::const_iterator it = tokeniser.begin(); it != end; ++it)
					{
						str_iter endList = acronymList.end();
						for(str_iter itList = acronymList.begin(); itList != endList; ++itList)
							resultList.push_back(*itList + *it);
					}
					acronymList.swap(resultList);
				}
			}
			else
			{
				for_each(wholeList.begin(), wholeList.end(), bind2nd(mem_fun1_ref(pfAppend), mbcs));
				for_each(acronymList.begin(), acronymList.end(), bind2nd(mem_fun1_ref(pfAppend), mbcs));
			}
		}
		else
		{
			// ASCII码直接组合
			for_each(wholeList.begin(), wholeList.end(), bind2nd(mem_fun1_ref(pfPushback), (char)towlower(name[i])));
			for_each(acronymList.begin(), acronymList.end(), bind2nd(mem_fun1_ref(pfPushback), (char)tolower(name[i])));
		}
	}

	// 合并结果
	{
		ostringstream os;
		copy(wholeList.begin(), wholeList.end(), ostream_iterator<string>(os, " "));

		whole = CA2W(os.str().c_str());
		trim_right(whole);
	}

	{
		ostringstream os;
		copy(acronymList.begin(), acronymList.end(), ostream_iterator<string>(os, " "));

		acronym = CA2W(os.str().c_str());
		trim_right(acronym);
	}
}