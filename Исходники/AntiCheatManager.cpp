void CAntiCheatManager::ParseAntiCheatConfig(const char * filename)
{
	CCryFile file;

	CryFixedStringT<128> realFileName;
	realFileName.Format("%s/%s", PathUtil::GetGameFolder().c_str(), filename);
	if (file.Open( realFileName.c_str(), "rb", ICryPak::FOPEN_HINT_QUIET | ICryPak::FOPEN_ONDISK ))
	{
		const size_t fileSize = file.GetLength();
		char* pBuffer = new char [fileSize];

		file.ReadRaw(pBuffer, fileSize);

		XmlNodeRef xmlData = gEnv->pSystem->LoadXmlFromBuffer(pBuffer, fileSize);

		SAFE_DELETE_ARRAY(pBuffer);

		if(xmlData)
		{
			CryLog("Parsing Anti-Cheat Configuration...");
			ParseAntiCheatConfig(xmlData);
		}
		else
		{
			CryLog("Unable to parse Anti-Cheat Configuration");
		}
	}
	else
	{
		CryLog("Unable to load '%s'", realFileName.c_str());
	}
}