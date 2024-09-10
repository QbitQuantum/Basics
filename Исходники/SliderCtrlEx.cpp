/////////////////////////////////////////////////////////////////////////////////////////
// Utility to save a bitmap to file for later examination. Used for debugging only.
// Based on an article by "gelbert" on www.experts-exchange.com at
// http://www.experts-exchange.com/Programming/Programming_Languages/MFC/Q_20193761.html
//
// This version is a member function and instead of taking an HBITMAP as the 2nd
// parameter, it take a reference to a CBitmap. Otherwise, it is identical.
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CSliderCtrlEx::SaveBitmap(LPCSTR lpFileName, CBitmap &hBitmap, HPALETTE hPal)
{
	BOOL bResult = FALSE;
	
	PICTDESC stPictDesc;
	stPictDesc.cbSizeofstruct = sizeof(PICTDESC);
	stPictDesc.picType = PICTYPE_BITMAP;
	stPictDesc.bmp.hbitmap = hBitmap;
	stPictDesc.bmp.hpal = hPal;
	
	LPPICTURE pPicture;
	HRESULT hr = OleCreatePictureIndirect( &stPictDesc, IID_IPicture, FALSE,
		reinterpret_cast<void**>(&pPicture) );
	if ( SUCCEEDED(hr) )
	{
		LPSTREAM pStream;
		hr = CreateStreamOnHGlobal( NULL, TRUE, &pStream );
		if ( SUCCEEDED(hr) )
		{
			long lBytesStreamed = 0;
			hr = pPicture->SaveAsFile( pStream, TRUE, &lBytesStreamed );
			if ( SUCCEEDED(hr) )
			{
				HANDLE hFile = CreateFile(_T(lpFileName), 
					GENERIC_WRITE, 
					FILE_SHARE_READ, 
					NULL,
					CREATE_ALWAYS, 
					FILE_ATTRIBUTE_NORMAL, 
					NULL );
				if ( hFile )
				{
					HGLOBAL hMem = NULL;
					GetHGlobalFromStream( pStream, &hMem );
					LPVOID lpData = GlobalLock( hMem );
					
					DWORD dwBytesWritten;
					bResult = WriteFile( hFile, lpData, lBytesStreamed, &dwBytesWritten, NULL );
					bResult &= ( dwBytesWritten == (DWORD)lBytesStreamed );
					
					// clean up
					GlobalUnlock(hMem);
					CloseHandle(hFile);
				}
			}
			// clean up         
			pStream->Release();
		}
		// clean up      
		pPicture->Release();
	}
	
	return bResult;   
}