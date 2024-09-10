BOOL CKatakoi::GetNameIndex(CArcFile* pclArc, YCMemory<BYTE>& clmbtSec, DWORD& dwNameIndex)
{
	// Open the filename represented by the index
	TCHAR szPathToSec[MAX_PATH];

	if (GetPathToSec(szPathToSec, pclArc->GetArcPath()) == FALSE)
	{
		// sec5 file couldn't be found

//		MessageBox(pclArc->GetProg()->GetHandle(), _T("sec5ファイルが見つかりません。\nインストールフォルダ内にsec5ファイルが存在していない可能性があります。"), _T("エラー"), MB_OK);
		return FALSE;
	}

	CFile clfSec;

	if (!clfSec.OpenForRead(szPathToSec))
	{
		// Failed to open the sec5 file

		return FALSE;
	}

	DWORD dwSecSize = clfSec.GetFileSize();

	// Reading
	clmbtSec.resize(dwSecSize);
	clfSec.Read(&clmbtSec[0], dwSecSize);

	if (memcmp(&clmbtSec[0], "SEC5", 4) != 0)
	{
		// Incorrect sec5 file

		TCHAR szError[MAX_PATH * 2];

		_stprintf(szError, _T("%s is incorrect."), szPathToSec);
//		MessageBox(pclArc->GetProg()->GetHandle(), szError, _T("Error"), MB_OK);

		return FALSE;
	}

	// Find the RESR

	for (dwNameIndex = 8; dwNameIndex < dwSecSize; )
	{
		if (memcmp(&clmbtSec[dwNameIndex], "RESR", 4) == 0)
		{
			// Found "RESR"

			DWORD dwNameIndexSize = *(LPDWORD)&clmbtSec[dwNameIndex + 4];
			DWORD dwNameIndexFiles = *(LPDWORD)&clmbtSec[dwNameIndex + 8];

			dwNameIndex += 12;

			// Find the index that matches the name of the archive

			for (DWORD i = 0; i < dwNameIndexFiles; i++)
			{
				DWORD dwWork = 0;
				dwWork += strlen((char*)&clmbtSec[dwNameIndex + dwWork]) + 1;	// File name
				dwWork += strlen((char*)&clmbtSec[dwNameIndex + dwWork]) + 1;	// File type
				dwWork += strlen((char*)&clmbtSec[dwNameIndex + dwWork]) + 1;	// Archive type

				DWORD dwLength = *(LPDWORD)&clmbtSec[dwNameIndex + dwWork];		// Archive name + File number
				dwWork += 4;

				for (DWORD i = (dwNameIndex + dwWork); ; i++)
				{
					if (clmbtSec[i] == '\0')
					{
						// Index dex doesn't match the name of the archive

						break;
					}

					if (lstrcmp((LPCTSTR)&clmbtSec[i], pclArc->GetArcName()) == 0)
					{
						// Found a match with the name of the archive

						// Validity

						if (lstrcmp(PathFindFileName(szPathToSec), _T("toa.sec5")) == 0)
						{
							// 杏奈ちゃんにお願い
							pclArc->SetFlag(TRUE);
						}
						else if (lstrcmp(PathFindFileName(szPathToSec), _T("katakoi.sec5")) == 0)
						{
							// 片恋いの月
							pclArc->SetFlag(TRUE);
						}

						return TRUE;
					}
				}

				dwNameIndex += dwWork + dwLength;
			}
			break;
		}

		dwNameIndex += 8 + *(LPDWORD)&clmbtSec[dwNameIndex + 4];
	}

	// No file in the index was a match

//	MessageBox(pclArc->GetProg()->GetHandle(), _T("ファイル名の取得に失敗しました。\nアーカイブファイル名が変更されている可能性があります。"), _T("Error"), MB_OK);

	return FALSE;
}