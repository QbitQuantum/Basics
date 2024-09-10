int CGdiPlusImage::GetEncoderClsid(LPCTSTR format, CLSID* pClsid)
{
	UINT  num = 0;          
	UINT  size = 0;        

	ImageCodecInfo* pImageCodecInfo = NULL;   

	GetImageEncodersSize(&num, &size);   
	if(size == 0)   
		return -1;  

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));   
	if(pImageCodecInfo == NULL)   
		return -1;  

	GetImageEncoders(num, size, pImageCodecInfo);   

	for(UINT j = 0; j < num; ++j)   
	{   
		if( StrCmp(pImageCodecInfo[j].MimeType, format) == 0 )   
		{   
			*pClsid = pImageCodecInfo[j].Clsid;   
			free(pImageCodecInfo);   
			return j; 
		}       
	}   

	free(pImageCodecInfo);   
	return -1;  
}