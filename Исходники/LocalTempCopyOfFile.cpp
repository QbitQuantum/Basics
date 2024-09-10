bool LocalTempCopyOfFile::IsFullyMessedUpString(CStdString sFileName)
{
	CStdString sFileNameWithoutExtension = RemoveExtension(sFileName);
	
	CPINFO codepageInfo;	
	::GetCPInfo(CP_ACP, &codepageInfo);

	for(unsigned int i=0; i<sFileNameWithoutExtension.length(); i++)
	{
		if ( sFileNameWithoutExtension[i] != codepageInfo.DefaultChar[0])
			return false;
	}

	return true;
}