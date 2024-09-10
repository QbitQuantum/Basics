void DizList::Read(const string& Path, const string* DizName)
{
	Reset();

	struct DizPreRedrawItem : public PreRedrawItem
	{
		DizPreRedrawItem() : PreRedrawItem(PR_ReadingMsg) {}
	};

	SCOPED_ACTION(TPreRedrawFuncGuard)(std::make_unique<DizPreRedrawItem>());
	const wchar_t *NamePtr=Global->Opt->Diz.strListNames.data();

	for (;;)
	{
		if (DizName)
		{
			strDizFileName = *DizName;
		}
		else
		{
			strDizFileName = Path;

			if (!PathCanHoldRegularFile(strDizFileName))
				break;

			string strArgName;
			NamePtr = GetCommaWord(NamePtr, strArgName);

			if (!NamePtr)
				break;

			AddEndSlash(strDizFileName);
			strDizFileName += strArgName;
		}

		os::fs::file DizFile;
		if (DizFile.Open(strDizFileName,GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING))
		{
			clock_t StartTime=clock();
			uintptr_t CodePage=CP_DEFAULT;
			bool bSigFound=false;

			if (!GetFileFormat(DizFile,CodePage,&bSigFound,false) || !bSigFound)
				CodePage = Global->Opt->Diz.AnsiByDefault ? CP_ACP : CP_OEMCP;

			GetFileString GetStr(DizFile, CodePage);

			auto LastAdded = DizData.end(); 
			string DizText;
			while (GetStr.GetString(DizText))
			{
				if (!(DizData.size() & 127) && clock() - StartTime > CLOCKS_PER_SEC)
				{
					SetCursorType(false, 0);
					PR_ReadingMsg();

					if (CheckForEsc())
						break;
				}

				RemoveTrailingSpaces(DizText);

				if (!DizText.empty())
				{
					if(!IsSpace(DizText.front()))
					{
						LastAdded = AddRecord(DizText);
					}
					else
					{
						if (LastAdded != DizData.end())
						{
							LastAdded->second.emplace_back(DizText);
						}
					}
				}
			}

			OrigCodePage=CodePage;
			Modified=false;
			DizFile.Close();
			return;
		}

		if (DizName)
			break;
	}

	Modified=false;
	strDizFileName.clear();
}