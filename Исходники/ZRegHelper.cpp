void CZRegHelper::ParseReg(wchar_t **arg,int num)
{
	wchar_t szApplication[MAX_PATH];
	DWORD cchLength = _countof(szApplication);
	QueryFullProcessImageName(GetCurrentProcess(), 0, szApplication, &cchLength);
	CString appPath;

	appPath.Format(L"%s",szApplication);
	if(2 == num)
	{
		if(0 == _wcsnicmp(arg[1],L"/reg",4) && wcslen(arg[1]) > 4)
		{
			CString para(arg[1]);
			para = para.Right(para.GetLength()-4);
			int index = 0;
			int last = 0;
			CString tmp;

			CString icoIndex ;
			icoIndex.Format(L"%s,0",appPath);
			while(-1 != (index = para.Find('|')))
			{
				tmp = para.Left(index);
				para = para.Right(para.GetLength() - index -1);
				if(0 == tmp.CompareNoCase(L"flac"))
				{					
					RegisterFileRelation(L".FLAC",appPath,L"ZLP.FLAC",icoIndex,L"FLAC");
				}
				else if(0 == tmp.CompareNoCase(L"ape"))
				{
					RegisterFileRelation(L".APE",appPath,L"ZLP.APE",icoIndex,L"APE");
				}
				else if(0 == tmp.CompareNoCase(L"wav"))
				{
					RegisterFileRelation(L".WAV",appPath,L"ZLP.WAV",icoIndex,L"WAV");
				}
				else if(0 == tmp.CompareNoCase(L"mp3"))
				{
					RegisterFileRelation(L".MP3",appPath,L"ZLP.MP3",icoIndex,L"MP3");
				}
				else if(0 == tmp.CompareNoCase(L"cue"))
				{
					RegisterFileRelation(L".CUE",appPath,L"ZLP.CUE",icoIndex,L"CUE");
				}
				else if(0 == tmp.CompareNoCase(L"ofr"))
				{
					RegisterFileRelation(L".OFR",appPath,L"ZLP.OFR",icoIndex,L"OFR");
				}
				else if(0 == tmp.CompareNoCase(L"ogg"))
				{
					RegisterFileRelation(L".OGG",appPath,L"ZLP.OGG",icoIndex,L"OGG");
				}
				else if(0 == tmp.CompareNoCase(L"tak"))
				{
					RegisterFileRelation(L".TAK",appPath,L"ZLP.TAK",icoIndex,L"TAK");
				}
				else if(0 == tmp.CompareNoCase(L"wv"))
				{
					RegisterFileRelation(L".WV",appPath,L"ZLP.WV",icoIndex,L"WV");
				}
				else if(0 == tmp.CompareNoCase(L"aac"))
				{
					RegisterFileRelation(L".AAC",appPath,L"ZLP.AAC",icoIndex,L"AAC");
				}
				else if(0 == tmp.CompareNoCase(L"m4a"))
				{
					RegisterFileRelation(L".M4A",appPath,L"ZLP.M4A",icoIndex,L"M4A");
				}
				else if(0 == tmp.CompareNoCase(L"tta"))
				{
					RegisterFileRelation(L".TTA",appPath,L"ZLP.TTA",icoIndex,L"TTA");
				}
				tmp.Empty();
			}
			tmp.Empty();
			while(-1!=(index = para.Find(',')))
			{
				tmp = para.Left(index);
				para = para.Right(para.GetLength() - index -1);
				if(0 == tmp.CompareNoCase(L"flac"))
				{					
					UnRegisterFileRelation(L".FLAC",L"ZLP.FLAC");
				}
				else if(0 == tmp.CompareNoCase(L"ape"))
				{
					UnRegisterFileRelation(L".APE",L"ZLP.APE");
				}
				else if(0 == tmp.CompareNoCase(L"wav"))
				{
					UnRegisterFileRelation(L".WAV",L"ZLP.WAV");
				}
				else if(0 == tmp.CompareNoCase(L"mp3"))
				{
					UnRegisterFileRelation(L".MP3",L"ZLP.MP3");
				}
				else if(0 == tmp.CompareNoCase(L"cue"))
				{
					UnRegisterFileRelation(L".CUE",L"ZLP.CUE");
				}
				else if(0 == tmp.CompareNoCase(L"ofr"))
				{
					UnRegisterFileRelation(L".OFR",L"ZLP.OFR");
				}
				else if(0 == tmp.CompareNoCase(L"ogg"))
				{
					UnRegisterFileRelation(L".OGG",L"ZLP.OGG");
				}
				else if(0 == tmp.CompareNoCase(L"tak"))
				{
					UnRegisterFileRelation(L".TAK",L"ZLP.TAK");
				}
				else if(0 == tmp.CompareNoCase(L"wv"))
				{
					UnRegisterFileRelation(L".WV",L"ZLP.WV");
				}
				else if(0 == tmp.CompareNoCase(L"aac"))
				{
					UnRegisterFileRelation(L".AAC",L"ZLP.AAC");
				}
				else if(0 == tmp.CompareNoCase(L"m4a"))
				{
					UnRegisterFileRelation(L".M4A",L"ZLP.M4A");
				}
				else if(0 == tmp.CompareNoCase(L"tta"))
				{
					UnRegisterFileRelation(L".TTA",L"ZLP.TTA");
				}
				tmp.Empty();
			}
			icoIndex.Empty();
			para.Empty();
			tmp.Empty();
			SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
			appPath.Empty();
		}
	}
}