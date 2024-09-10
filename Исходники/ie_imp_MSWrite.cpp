bool IE_Imp_MSWrite_Sniffer::getDlgLabels (const char **szDesc,
                                           const char **szSuffixList,
                                           IEFileType *ft)
{
	*szDesc = "Microsoft Write (.wri)";
	*szSuffixList = "*.wri";
	*ft = getFileType();

	return true;
}