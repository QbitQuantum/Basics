  //
  // Entry point for conversion
  //
UT_Error IE_ImpGraphic_Win32Native::_convertGraphic(UT_ByteBuf * pBB, std::string& mimetype)
{	
    IPicture* pPicture = NULL;
    IStream* stream;	
    HGLOBAL hG;		
    HBITMAP hBitmap;
    OLE_HANDLE* hB;
    PBITMAPINFO	bi;
    UT_ByteBuf bBufBMP;
    UT_Error err;	

	/* If the system has GDI+, use it*/
	if (isGDIPlusAvailable())
	{
		m_pBB = new UT_ByteBuf();
		return GDIconvertGraphic(pBB, m_pBB, mimetype);		
	}

	// the code below always writes out PNG's for now; we could update it to support
	// native JPEG images as well, or just delete it and always use GDI+.
	mimetype = "image/png";

    // We need to store the incoming bytebuffer in a Windows global heap	
    size_t nBlockLen = pBB->getLength();   	
    hG = GlobalAlloc(GPTR, nBlockLen);
    if (!hG) 
		return UT_IE_NOMEMORY;	
    
    CopyMemory(hG, pBB->getPointer(0), nBlockLen);   	
    
    // Create a stream from heap
    HRESULT hr = CreateStreamOnHGlobal(hG,false,&stream);
    if (!SUCCEEDED(hr) || !stream)
	{
		GlobalFree(hG);
		return UT_IE_NOMEMORY;
	}
    
    hr = OleLoadPicture(stream,0,false,IID_IPicture,(void**)&pPicture);	

    stream->Release();
    GlobalFree(hG);
    
    if (!SUCCEEDED(hr) || !pPicture)
	{
		return UT_IE_UNKNOWNTYPE;
	}

    pPicture->get_Handle((unsigned int*)&hB);
    
    hBitmap = (HBITMAP)CopyImage(hB,IMAGE_BITMAP,0,0,LR_COPYRETURNORG);
    
    HWND hWnd = GetDesktopWindow();
    
    // Create a BMP file from a BITMAP	
    bi = CreateBitmapInfoStruct(hBitmap);						
    CreateBMPFile(hWnd, bBufBMP, bi, hBitmap, GetDC(hWnd));
    LocalFree ((HLOCAL)bi);
    
    InitializePrivateClassData();
    
    /* Read Header Data */
    err = Read_BMP_Header(&bBufBMP);
	
	/* 
	   It's not a bitmap, then we have to rendered it into a device
	   context and get a bitmap from there. Case wmf graphics
	*/
	if (err) 
	{
		if (err!=UT_IE_BOGUSDOCUMENT) 
		{
			pPicture->Release();
			return err;		
		}
		
        long nWidth  = 0;
        long nHeight = 0;
		long nScaleToWidth= 500;
		long nScaleToHeight= 500;		
		RECT rc, rect;				
		BYTE *imagedata;
		HBITMAP hBit;
		HBITMAP hOld;
		BITMAPINFO bmi; 		
		HDC hWndDC = GetDC(hWnd);
		HDC	hMemDC = CreateCompatibleDC(hWndDC);
		HBRUSH hBrush = (HBRUSH)GetCurrentObject(hMemDC, OBJ_BRUSH);
		
		pPicture->get_Width (&nWidth);
		pPicture->get_Height(&nHeight);

		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 	
		bmi.bmiHeader.biWidth = nScaleToWidth;
		bmi.bmiHeader.biHeight = nScaleToHeight;
		bmi.bmiHeader.biPlanes = 1; 
		bmi.bmiHeader.biBitCount = 24; // as we want true-color
		bmi.bmiHeader.biCompression = BI_RGB; // no compression
		bmi.bmiHeader.biSizeImage = (((bmi.bmiHeader.biWidth * bmi.bmiHeader.biBitCount + 31) & ~31) >> 3) * bmi.bmiHeader.biHeight; 
		bmi.bmiHeader.biXPelsPerMeter = 0;
		bmi.bmiHeader.biYPelsPerMeter = 0; 
		bmi.bmiHeader.biClrImportant = 0;
		bmi.bmiHeader.biClrUsed = 0; // we are not using palette
			
		hBit = CreateDIBSection(hMemDC,&bmi,DIB_RGB_COLORS,(void**)&imagedata,0,0);						
		hOld = (HBITMAP) SelectObject(hMemDC, hBit);			

		
		rect.left = 0;
        rect.top = nScaleToHeight;
        rect.right = nScaleToWidth;
        rect.bottom = 0;

		FillRect(hMemDC, &rect,  hBrush);
		pPicture->Render(hMemDC, 0,0,  nScaleToWidth,	nScaleToHeight, 0,  nHeight, 
						 nWidth, -nHeight, &rc);	
		
		hBit =  (HBITMAP)SelectObject(hMemDC, hOld);
		
		bi =  CreateBitmapInfoStruct(hBit);						
		CreateBMPFile(hWnd, bBufBMP, &bmi, hBit, hMemDC);
		LocalFree ((HLOCAL)bi);

		
		DeleteDC(hMemDC);
		DeleteDC(hWndDC);
	    DeleteObject(hBrush); 
		DeleteObject(hBit);	  
    
		err = Read_BMP_Header(&bBufBMP);
		if (err) 
		{
			pPicture->Release();
			return err;				
		}
		
	}

	pPicture->Release();


    if ((err = Initialize_PNG()))
	{   
		return err;
	}	
    
    /* Read Palette, if no palette set Header accordingly */
    if(m_iBitsPerPlane < 24) 
	{
		if ((err = Convert_BMP_Palette(&bBufBMP))) 
			return err;
	}
    else
	{
		UT_uint16 bitsPerChannel;
		UT_uint16 colorType;

		if (m_iBitsPerPlane == 24) {
			bitsPerChannel = 8;
			colorType = PNG_COLOR_TYPE_RGB;
		} else if (m_iBitsPerPlane == 32) {
			bitsPerChannel = 8;
			colorType = PNG_COLOR_TYPE_RGB_ALPHA;
		} else if (m_iBitsPerPlane == 48) {
			bitsPerChannel = 16;
			colorType = PNG_COLOR_TYPE_RGB;
		} else if (m_iBitsPerPlane == 64) {
			bitsPerChannel = 16;
			colorType = PNG_COLOR_TYPE_RGB_ALPHA;
		} else {		   
			return UT_ERROR;
		}
	
		png_set_IHDR ( m_pPNG,
					   m_pPNGInfo,
					   m_iWidth,
					   m_iHeight,
					   bitsPerChannel,
					   colorType,
					   PNG_INTERLACE_NONE,
					   PNG_COMPRESSION_TYPE_DEFAULT,
					   PNG_FILTER_TYPE_DEFAULT );
	
	}
    if ((err = Convert_BMP(&bBufBMP))) 
	{
		return err;
	}
    
    /* Clean Up Memory Used */
		
    FREEP(m_pPNGInfo->palette);	
    png_destroy_write_struct(&m_pPNG, &m_pPNGInfo);
    
    return UT_OK;  	  	
}