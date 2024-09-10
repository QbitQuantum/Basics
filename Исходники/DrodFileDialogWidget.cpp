//*****************************************************************************
UINT CDrodFileDialogWidget::GetExtensionType(const WSTRING& wFilename)
//Determine file type based on file name extension.
{
	UINT ext;
	for (ext = 0; ext < FileExtension::EXT_COUNT; ++ext)
	{
		WSTRING wstrExt = wszPeriod;
		wstrExt += g_pTheDB->GetMessageText(fileExtension[ext]);
		if (!WCSicmp(wFilename.c_str() + WCSlen(wFilename.c_str()) - wstrExt.size(), wstrExt.c_str()))
		{
			//Recognized file extension.
			return ext;
		}
	}

	//On older OSes, only 3-character extensions are recognized.
	//If none of the above matches worked, try matching against shortened extensions.
	for (ext = 0; ext < FileExtension::EXT_COUNT; ++ext)
	{
		WSTRING wstrExt = wszPeriod;
		wstrExt += g_pTheDB->GetMessageText(fileExtension[ext]);
		if (wstrExt.length() > 4) //don't retest extensions that were already short enough
		{
			wstrExt.resize(4); //.ext
			if (!WCSicmp(wFilename.c_str() + WCSlen(wFilename.c_str()) - wstrExt.size(), wstrExt.c_str()))
			{
				//Recognized file extension.
				return ext;
			}
		}
	}

	return FileExtension::EXT_COUNT; //extension not recognized
}