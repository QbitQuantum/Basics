CString CClipCompare::SaveToFile(int id, CClip *pClip, bool saveW, bool SaveA)
{
	CString path;
	wchar_t wchPath[MAX_PATH];
	if (GetTempPathW(MAX_PATH, wchPath))
	{
		CString cs;
		cs.Format(_T("%sditto_compare_%d.txt"), wchPath, id);

		if(FileExists(cs))
		{
			for(int i = 0; i < 1000; i++)
			{			
				cs.Format(_T("%sditto_compare_%d.txt"), wchPath, id);
				if(FileExists(cs))
				{
					path = cs;
					break;
				}
			}
		}
		else
		{
			path = cs;
		}

		if(path != _T("") && 
			pClip != NULL)
		{
			pClip->WriteTextToFile(path, saveW, SaveA, false);
		}
	}

	return path;
}