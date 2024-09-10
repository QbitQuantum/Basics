int CVoiceGroup::AddSoundStrings(char* sDir)
{
	// Sanity checks...

	if (!sDir) return(0);
	if (sDir[0] == '\0') return(0);


	// Add all of the sound strings in the given rez directory...

	int cSounds = 0;

	FileEntry* pFiles = m_pClientDE->GetFileList(sDir);
	if (!pFiles) return(0);

	FileEntry* pCurFile = pFiles;

	while (pCurFile)
	{
		if (pCurFile->m_Type == TYPE_FILE)
		{
			int nLen = _mbstrlen(pCurFile->m_pBaseFilename);

			if (nLen > 4 && strnicmp(&pCurFile->m_pBaseFilename[nLen - 4], ".wav", 4) == 0)
			{
				if (AddSoundString(pCurFile->m_pFullFilename))
				{
					cSounds++;
				}
			}
		}

		pCurFile= pCurFile->m_pNext;
	}


	// All done...
	m_pClientDE->FreeFileList(pFiles);
	return(cSounds);
}