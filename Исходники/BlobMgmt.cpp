LRESULT
BlobMgmt::ShowImage()
{
#ifndef VC6
	HDC             hdc;
	RECT			rectwin;
	wyInt32         renderwidth, renderheight;
	PAINTSTRUCT     ps;
	LPSTREAM        stream = NULL;
	HGLOBAL         glbmem;
	void            *glbbuffer;
    wyWChar         tempfilename[MAX_PATH+1] = {0}, path[MAX_PATH + 1] = {0};
	wyString		tempstr;
	HANDLE          hfile = INVALID_HANDLE_VALUE;
	DWORD           byteswritten = 0;

	if(!m_piub->m_data || m_piub->m_datasize == 0)
	{
		VERIFY(hdc = BeginPaint(m_hwndimage, &ps));
		VERIFY(EndPaint(m_hwndimage, &ps));
		return 0;
	}
	/* allocate global memory and copy image data in it*/
	VERIFY(glbmem = GlobalAlloc(GMEM_MOVEABLE | GMEM_NODISCARD, m_piub->m_datasize));
	if(!glbmem)
        return 0;

	/* lock the global memory and get a pointer */
	glbbuffer = GlobalLock(glbmem);
	/* copy the memory to buffer */
	CopyMemory(glbbuffer, m_piub->m_data, m_piub->m_datasize);
	/* unlock it */
	VERIFY(GlobalUnlock(glbmem)== NO_ERROR);
	/* create the stream */
	VERIFY(CreateStreamOnHGlobal(glbmem, FALSE, &stream)== S_OK);
	/* prepare window for painting */
	VERIFY(hdc = BeginPaint(m_hwndimage, &ps));
	/* clear the window */
	PrepareScreen(ps.hdc);

    if(pGlobals->m_configdirpath.GetLength() || SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, (LPWSTR)path)))
    {
		if(pGlobals->m_configdirpath.GetLength())
		{
			//wcscpy(path, pGlobals->m_configdirpath.GetAsWideChar());			
			wcsncpy(path, pGlobals->m_configdirpath.GetAsWideChar(), MAX_PATH);			
			path[MAX_PATH] = '\0';
		}
		
		else
		{
			wcscat(path, L"\\");
			wcscat(path, L"SQLyog");
		}
        
        VERIFY(GetTempFileName(path, L"img", 0, tempfilename));
 	    hfile = CreateFile(tempfilename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
								   NULL, NULL);
	    VERIFY(hfile != INVALID_HANDLE_VALUE);
	    VERIFY(WriteFile(hfile, m_piub->m_data, m_piub->m_datasize, &byteswritten, NULL));
	    VERIFY(CloseHandle(hfile));
    }
	tempstr.SetAs(tempfilename);
	
	WCHAR *wpath = GetWideString(tempstr.GetString());
	
	Gdiplus::Graphics	graphics(hdc);
	Gdiplus::Image		*image = new Gdiplus::Image(wpath);

	HeapFree(GetProcessHeap(), 0, wpath);
	/* in win95 image will be null so we exit */
	if(!image)
		goto ExitPara;

	/* the binary data might not be image so image.getlastatus will not return Ok */
	if(image->GetLastStatus()!= Gdiplus::Ok)
    {
		delete image;
		goto ExitPara;
	}

	/* get the window width and calculate the correct render stats */
	VERIFY(GetClientRect(m_hwndimage, &rectwin));

	renderheight =(((LONG)image->GetHeight())> rectwin.bottom)?(rectwin.bottom):(image->GetHeight());
	renderwidth  =(((LONG)image->GetWidth())> rectwin.right)?(rectwin.right):(image->GetWidth());

	graphics.DrawImage(image, 0, 0, renderwidth, renderheight);
	delete image;
	EndPaint(m_hwndimage, &ps);

ExitPara:
	/* free up stuff */
	VERIFY(DeleteFile(tempfilename));
	if(stream)
		stream->Release();

	VERIFY(GlobalFree(glbmem)== NULL);
#endif
	
	return 0;
}