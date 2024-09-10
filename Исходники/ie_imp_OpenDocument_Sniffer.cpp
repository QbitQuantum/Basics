/**
 * Get the dialog labels
 * 
 */
bool IE_Imp_OpenDocument_Sniffer::getDlgLabels (const char ** szDesc,
                          const char ** szSuffixList,
                          IEFileType * ft)
{
	*szDesc = "OpenDocument (.odt, .ott)";
	*szSuffixList = "*.odt; *.ott";
	*ft = getFileType();
  
    return true;
}