void CEditorRoot::SetMasterFolder()
{
	CHAR sFolder[_MAX_PATH];

	GetModuleFileNameA( GetModuleHandle(NULL), sFolder, sizeof(sFolder));
	PathRemoveFileSpecA(sFolder);

	CHAR *lpPath = StrStrIA(sFolder,"\\Bin32");
	if (lpPath)
		*lpPath = 0;
	lpPath = StrStrIA(sFolder,"\\Bin64");
	if (lpPath)
		*lpPath = 0;

	m_masterFolder = sFolder;
	if (!m_masterFolder.IsEmpty())
	{
		if (m_masterFolder[m_masterFolder.GetLength()-1] != '\\')
			m_masterFolder += '\\';
	}

	SetCurrentDirectoryA( sFolder );
}