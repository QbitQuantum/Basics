	extern "C" void CreateBMPFile(char *pszFile, HBITMAP hBMP, HDC hDC) 
	//given a handle hBMP of a bitmap that is currently selected in the display context hDC,
	//creates a .bmp file named pszFile containing the bitmap
	//don't remember where I copied this from
	{ 
		int errorLevel;
		HANDLE hf;                  // file handle 
		PBITMAPINFO pbi;			// bitmap info
		BITMAPFILEHEADER hdr;       // bitmap file-header 
		PBITMAPINFOHEADER pbih;     // bitmap info-header 
		LPBYTE lpBits;              // memory pointer 
		DWORD dwTotal;              // total count of bytes 
		DWORD cb;                   // incremental count of bytes 
		BYTE *hp;                   // byte pointer 
		DWORD dwTmp; 
		
		pbi = CreateBitmapInfoStruct(hBMP);
		pbih = (PBITMAPINFOHEADER) pbi; 
		lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

		assert(lpBits);

		// Retrieve the color table (RGBQUAD array) and the bits 
		// (array of palette indices) from the DIB. 
		errorLevel = GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi, DIB_RGB_COLORS);
		assert(errorLevel != 0);

		// Create the .BMP file. 
		hf = CreateFile(pszFile, 
					   GENERIC_READ | GENERIC_WRITE, 
					   (DWORD) 0, 
						NULL, 
					   CREATE_ALWAYS, 
					   FILE_ATTRIBUTE_NORMAL, 
					   (HANDLE) NULL); 
		assert(hf != INVALID_HANDLE_VALUE);
		hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 
		// Compute the size of the entire file. 
		hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
					 pbih->biSize + pbih->biClrUsed 
					 * sizeof(RGBQUAD) + pbih->biSizeImage); 
		hdr.bfReserved1 = 0; 
		hdr.bfReserved2 = 0; 

		// Compute the offset to the array of color indices. 
		hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
						pbih->biSize + pbih->biClrUsed 
						* sizeof (RGBQUAD); 

		// Copy the BITMAPFILEHEADER into the .BMP file. 
		errorLevel = WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), (LPDWORD) &dwTmp,  NULL);
		assert(errorLevel != 0);

		// Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
		errorLevel = WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
					  + pbih->biClrUsed * sizeof (RGBQUAD), 
					  (LPDWORD) &dwTmp, NULL);
		assert(errorLevel != 0);

		// Copy the array of color indices into the .BMP file. 
		dwTotal = cb = pbih->biSizeImage; 
		hp = lpBits; 
		errorLevel = WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL);
		assert(errorLevel != 0);

		// Close the .BMP file. 
		errorLevel = CloseHandle(hf);
		assert(errorLevel != 0);

		// Free memory. 
		GlobalFree((HGLOBAL)lpBits);
	}