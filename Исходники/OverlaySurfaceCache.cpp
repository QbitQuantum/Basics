bool COverlaySurfaceCache::CaptureFromSharedMemory(HDC hdc,LPCRECT prcDest)
{
	
	if(prcDest ==0 ) return false;

	static CFileMapping shared_flags;
	//1.create filemapping object for sharing memory  
	if(!shared_flags.IsOpen())
	{
		if(!shared_flags.Open(kFlagsShareMemory,sizeof(DWORD),false ))
		{
			DebugOutF(filelog::log_error,"open shared_flags failed,could not open shared memory");
			return false;
		}
	}
	DWORD *pFlags = (DWORD *)shared_flags.GetPointer();
	if(*pFlags == 0) return false;
	TrackDebugOut;
	static LONG tick = GetTickCount();//make sure that message HWND_BROADCAST will be handle once.

	static CFileMapping mem;
	//1.create filemapping object for sharing memory  
	if(!mem.IsOpen())
	{
		if(!mem.Open(kChaptureOverlayShareMemory,sizeof(SURFACE_DATA),true ))
		{
			DebugOutF(filelog::log_error,"CaptureFromSharedMemory failed,could not open shared memory");
			return false;
		}
		//2.Notify processes which using DirectDaw overlay.
		SURFACE_DATA*pDate = static_cast<SURFACE_DATA*>( mem.GetPointer());
		pDate->modified = FALSE;
		SendMessageTimeout(HWND_BROADCAST,CAPTURE_SCREEN,++tick,0,SMTO_ABORTIFHUNG,10000,0);
		if(!pDate->modified)
		{
			DebugOutF(filelog::log_debug,"no overlay alive");
			return false;
		}
	}
	// resize shared memory if necessarily  
	int i = 0;
	for(i=0;i<3;++i)
	{
		SURFACE_DATA*pDate = static_cast<SURFACE_DATA*>( mem.GetPointer());
		if(pDate->size + sizeof(SURFACE_DATA ) > mem.GetSize() )
		{
			if(!mem.Open(kChaptureOverlayShareMemory,pDate->size + sizeof(SURFACE_DATA ),true ))
			{
				DebugOutF(filelog::log_error,"CaptureFromSharedMemory failed,could not open shared memory");
				return false;
			}
			pDate = static_cast<SURFACE_DATA*>( mem.GetPointer());
		}
		//Notify processes which using DirectDaw overlay.
		pDate->modified = FALSE;
		SendMessageTimeout(HWND_BROADCAST,CAPTURE_SCREEN,++tick,0,SMTO_ABORTIFHUNG,10000,0);
		if(!pDate->modified ) 
		{
			DebugOutF(filelog::log_debug,"no overlay alive");
			return false;
		}
		if(pDate->size + sizeof(SURFACE_DATA ) > mem.GetSize() ) continue;
		break;
	}
	/*return false;*/
	if(i == 3) return false;
	CAutoLockEx<CMutexLock> lock(g_mLock);
	//open and get the size of shared memory
	//CFileMapping mem;
// 	if(!mem.Open(kChaptureOverlayShareMemory,sizeof(SURFACE_DATA),false))
// 	{
// 		DebugOutF(filelog::log_error,"CaptureFromSharedMemory failed,could not open shared memory");
// 		return false;
// 	}
// 	SURFACE_DATA* pData = (SURFACE_DATA*)mem.GetPointer();
// 	DWORD size = pData->size;
// 	mem.Destroy();
// 	if(size < sizeof(SURFACE_DATA)) return false;
// 	// then get open again with the size
// 	if(!mem.Open(kChaptureOverlayShareMemory,size,false))
// 	{
// 		DebugOutF(filelog::log_error,"CaptureFromSharedMemory failed,could not open shared memory as size %d",size);
// 		return false;
// 	}

	SURFACE_DATA*pData = (SURFACE_DATA*)mem.GetPointer();
	// the area to be copy
	RECT dest ={0},src={0},intersect={0};
	if(IsRectEmpty(&pData->rcDst)) 
	{
		DebugOutF(filelog::log_debug,"CaptureFromSharedMemory dest rect is empty");
		return true;
	}
	IntersectRect(&intersect,prcDest,&pData->rcDst);
	if(IsRectEmpty(&intersect)) 
	{
		DebugOutF(filelog::log_debug,"CaptureFromSharedMemory dest rect is empty");
		return true;
	}

	HRGN hrgn = 0;
	HBITMAP hBmp = 0;
	HDC hMemDC = 0;

	dest.left = intersect.left - prcDest->left;
	dest.top = intersect.top - prcDest->top;
	int w = intersect.right-intersect.left;
	int h = intersect.bottom-intersect.top;
	dest.right = dest.left +w;
	dest.bottom = dest.top +h;

	src.left = (intersect.left - pData->rcDst.left)*pData->desc.dwWidth/(pData->rcDst.right-pData->rcDst.left);
	src.top = (intersect .top -pData->rcDst.top)*pData->desc.dwHeight/(pData->rcDst.bottom-pData->rcDst.top);
	w = w*pData->desc.dwWidth/(pData->rcDst.right-pData->rcDst.left);
	h = h*pData->desc.dwHeight/(pData->rcDst.bottom-pData->rcDst.top);
	src.right = src.left +w;
	src.bottom = src.top +h;


	bool bOK = true;
	try
	{

		if (pData->desc.ddpfPixelFormat.dwFlags & DDPF_FOURCC)
		{
			DebugOutF(filelog::log_error,"unsupport color space 0x%x",pData->desc.ddpfPixelFormat.dwFourCC);
			throw false;
		}
// 		if(pData->rdh.nCount )
// 		{
// 			hrgn = ExtCreateRegion(0,pData->rdh.nRgnSize,(RGNDATA*)&pData->rdh);
// 			if(prcDest) OffsetRgn(hrgn,-prcDest->left,-prcDest->top);
// 			SelectClipRgn(hdc,hrgn);
// 		}
		{
			BITMAPINFOHEADER infhead ;
			ZeroMemory(&infhead,sizeof(infhead));

			infhead.biSize = sizeof(BITMAPINFOHEADER);

			infhead.biBitCount = (WORD)pData->desc.ddpfPixelFormat.dwRGBBitCount;

			int imagesize =  pData->desc.lPitch* pData->desc.dwHeight;

			infhead.biPlanes	= 1;
			infhead.biHeight	= -LONG(pData->desc.dwHeight);
			infhead.biWidth		= pData->desc.dwWidth;
			infhead.biSizeImage	= imagesize ;
			infhead.biCompression = BI_RGB;
			hMemDC  = CreateCompatibleDC(hdc);

			if(hMemDC == NULL){
				DebugOutF(filelog::log_error,"CreateCompatibleDC failed with %d",GetLastError());
				throw false;
			}


			{
				hBmp = CreateDIBSection(hMemDC,
					(BITMAPINFO *)&infhead,
					DIB_RGB_COLORS, 0,mem.GetHandle(), FIELD_OFFSET(SURFACE_DATA,data) + (pData->rdh.nRgnSize?pData->rdh.nRgnSize-sizeof(RGNDATAHEADER):0));

				if(hBmp == NULL){
					DebugOutF(filelog::log_error,"CreateDIBSection failed with %d",GetLastError() );
					throw false;
				}
			}

			SelectObject(hMemDC,hBmp);

			if (((dest.right-dest.left) == (src.right-src.left)) &&
				((dest.bottom-dest.top) == (src.bottom-src.top))
				)
			{
				if(!BitBlt( hdc,
					dest.left,
					dest.top,
					dest.right-dest.left,
					dest.bottom-dest.top,
					hMemDC,
					src.left,
					src.top,
					SRCCOPY))
				{
					DebugOutF( filelog::log_error,"StretchBlt failed with %d",GetLastError() );
					throw false;
				}
			}
			else
			{
				if(!StretchBlt (hdc,
					dest.left,
					dest.top,
					dest.right-dest.left,
					dest.bottom-dest.top,
					hMemDC,
					src.left,
					src.top,
					src.right-src.left,
					src.bottom-src.top,
					SRCCOPY))
				{
					DebugOutF(filelog::log_error,"StretchBlt failed with %d",GetLastError());
					throw false;
				}
			}

// 			DebugOutF(filelog::log_info,"CaptureFromSharedMemory (w:%d,h:%d,FourCC:0x%x,RGBBitCount:%d,l:%d,t:%d,r:%d,b:%d)ok",
// 				pData->desc.dwWidth,
// 				pData->desc.dwHeight,
// 				pData->desc.ddpfPixelFormat.dwFourCC,
// 				pData->desc.ddpfPixelFormat.dwRGBBitCount,
// 				pData->rcDst.left,
// 				pData->rcDst.top,
// 				pData->rcDst.right,
// 				pData->rcDst.bottom
// 				);
			//return true;


		}

	}
	catch (bool b1)
	{
		bOK = b1;
	}

	if(hMemDC)DeleteDC(hMemDC);
	if(hBmp)DeleteObject(hBmp);
	if(hrgn)DeleteObject(hrgn);
	DebugOutF(filelog::log_debug,"CaptureFromSharedMemory ok");
	return bOK;
}