int MalieExec::ExportStrByCode(void)
{
	CMalie_VMParse vm(this);
	vector<wstring> chapterName;
	vector<DWORD> chapterIndex;
	vector<DWORD> chapterRegion;
	vector<Malie_Moji> && moji = vm.ParseScenario(chapterName,chapterIndex);

	if (!chapterName.size())
	{
		vector<DWORD>::iterator it = unique(chapterIndex.begin(),chapterIndex.end());
		chapterIndex.erase(it,chapterIndex.end());
	}

	auto exportFunc = [&](pair<DWORD,wstring>(&x),FILE *fp){
		fwprintf(fp,L"○%08d○\n%s●%08d●\n%s◇%08d◇\n\n\n",
			x.first,x.second.c_str(),x.first,x.second.c_str(),x.first);
	};

	fprintf(stderr,"\nStarting dumping text to file...\n");

	if (chapterIndex.size())
	{
		chapterRegion = chapterIndex;
		chapterRegion.erase(chapterRegion.begin());
		chapterRegion.push_back(moji.size());
		for (size_t i=0;i<chapterIndex.size();++i)
		{
			wstring && name = i<chapterName.size()?
				stringf(L"%02d %ls.txt",i,chapterName[i].c_str()):
				stringf(L"%02d.txt",i);

			FILE *fp;
			_wfopen_s(&fp,name.c_str(),L"wt,ccs=UNICODE");

			for_each(moji.begin()+chapterIndex[i],moji.begin()+chapterRegion[i],[&](Malie_Moji x)
			{
				wstring kotoba;
				if (!x.name.empty())
				{
					kotoba = x.name+L"※";
				}
				kotoba += ParseString(x.index);

				exportFunc(pair<DWORD,wstring>(x.index,kotoba),fp);
				fflush(fp);
			});

			fclose(fp);
		}
	}
	else
	{
		FILE *fp;
		_wfopen_s(&fp,L"MalieMoji.txt",L"wb");
        fwrite("\xff\xfe", 1, 2, fp);

        //for_each(moji.begin(), moji.end(), [&](Malie_Moji x)
        //{
        //    wstring kotoba;
        //    if (!x.name.empty())
        //    {
        //        kotoba = x.name + L"※";
        //    }
        //    kotoba += ParseString(x.index);

        //    exportFunc(pair<DWORD, wstring>(x.index, kotoba), fp);
        //});
        auto write_crln = [](FILE* fp) {
            fwrite(L"\r\n", 2, 2, fp);
        };
        for (auto& x : moji) {
            wchar_t tag[100];
            auto cnt = swprintf_s(tag, L"#%05d %s", x.index, x.name.c_str());
            fwrite(tag, 2, cnt, fp);
            write_crln(fp);

            auto s = GetString(x.index);
            MalieString str(s);
            str.init();
            auto v = str.export_str();
            
            for (auto& s : v) {
                fwrite(s.c_str(), 2, s.length(), fp);
                write_crln(fp);
            }
        }

		fclose(fp);

        fp = fopen("str.txt", "wb");
        fwrite("\xff\xfe", 1, 2, fp);
        auto fp2 = fopen("str.idx", "wb");
        auto write_tbl = [&](map<int, wstring>& tbl) {
            for (auto& itr : tbl) {
                fwrite(&itr.first, 1, 4, fp2);
                fwrite(itr.second.c_str(), 2, itr.second.length(), fp);
                write_crln(fp);
            }
        };
        write_tbl(vm.get_name_data_table());
        write_tbl(vm.get_sel_data_table());
        
        fclose(fp);
        fclose(fp2);
	}

	fprintf(stderr,"Done.\n");
	return 0;
}