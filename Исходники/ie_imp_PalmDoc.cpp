bool IE_Imp_PalmDoc_Sniffer::getDlgLabels(const char ** pszDesc,
										  const char ** pszSuffixList,
										  IEFileType * ft)
{
	*pszDesc = "Palm Document (.pdb)";
	*pszSuffixList = "*.pdb";
	*ft = getFileType();
	return true;
}