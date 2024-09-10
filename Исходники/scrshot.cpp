WINERROR ScrGetEncoderClsid(
	const WCHAR*	format, 
	CLSID*			pClsid
	)
{
	Gdiplus::GdiplusStartupInput input;
	ULONG_PTR token;
	PVOID MemToFree = NULL;
	
	Gdiplus::Status status = Gdiplus::GdiplusStartup(&token, &input, 0);
		
	if (status == Gdiplus::Ok)
	{
		UINT num = 0;
		UINT size = 0;

		Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

		Gdiplus::GetImageEncodersSize(&num, &size);
		
		if(size == 0)
		{
			return ERROR_UNSUCCESSFULL;
		}

		pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(AppAlloc(size));
		
		if(pImageCodecInfo == NULL)
		{
			return ERROR_UNSUCCESSFULL;
		}

		GetImageEncoders(num, size, pImageCodecInfo);

		for(UINT i = 0; i < num; ++i)
		{
			if(wcscmp(pImageCodecInfo[i].MimeType, format) == 0 )
			{
				MemToFree = (PVOID)pImageCodecInfo;
				*pClsid = pImageCodecInfo[i].Clsid;
				AppFree(MemToFree);
				
				return NO_ERROR;
			}
		}

		MemToFree = (PVOID)pImageCodecInfo;
		AppFree(MemToFree);
	}

	return ERROR_UNSUCCESSFULL;
}