bool	IE_Exp_WordPerfect_Sniffer::getDlgLabels (const char ** pszDesc,
												  const char ** pszSuffixList,
												  IEFileType * ft)
{
	*pszDesc = "WordPerfect 6/7/8/9 (.wpd)";
	*pszSuffixList = "*.wpd";
	*ft = getFileType();
	return true;
}