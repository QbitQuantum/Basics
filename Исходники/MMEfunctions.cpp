void TakeScreenshot() {
    if(RealDevice==NULL) return;
    HRESULT hr;
    IDirect3DSurface* surface;
	RECT r;
	RECT* pRect=0;
//#ifndef RELEASE
//	hr=RealDevice->CreateOffscreenPlainSurface(1280,1024,
//        D3DFMT_A8R8G8B8,D3DPOOL_SCRATCH,&surface,NULL);
//#else
	DWORD width, height;
	if(JointInfo.WNDwindowed) {
		D3DDISPLAYMODE mode;
		RealDevice->GetDisplayMode(0, &mode);
		hr=RealDevice->CreateOffscreenPlainSurface(mode.Width,mode.Height,D3DFMT_A8R8G8B8,D3DPOOL_SCRATCH,&surface,NULL);
		HWND win=FindWindow("morrowind", "morrowind");
		//GetWindowRect(win, &r);
		POINT p; p.x = 0; p.y = 0;
		ClientToScreen(win, &p);
		GetClientRect(win, &r);
		r.left += p.x;
		r.top += p.y;
		r.right += p.x;
		r.bottom += p.y;
		if(r.left < 0) r.left = 0;
		if(r.top < 0) r.top = 0;
		if((UINT)r.right >= mode.Width) r.right = (LONG)mode.Width - 1;
		if((UINT)r.bottom >= mode.Height) r.bottom = (LONG)mode.Height - 1;
		pRect=&r;
		width=mode.Width;
		height=mode.Height;
	} else {
		width=JointInfo.GraphicsWidth;
		height=JointInfo.GraphicsHeight;
		hr=RealDevice->CreateOffscreenPlainSurface(JointInfo.GraphicsWidth,JointInfo.GraphicsHeight, D3DFMT_A8R8G8B8,D3DPOOL_SCRATCH,&surface,NULL);
	}
//#endif
	if(hr!=D3D_OK) return;
	hr=RealDevice->GetFrontBufferData(0,surface);
	if(hr==D3D_OK) {
		D3DLOCKED_RECT rect2;
		hr=surface->LockRect(&rect2, 0, 0);
		if(hr==D3D_OK&&!(rect2.Pitch%4)) {
			DWORD *ptr=(DWORD*)rect2.pBits;
			rect2.Pitch/=4;
			for(DWORD y=0;y<height;y++) {
				DWORD offset=y*rect2.Pitch;
				for(DWORD x=0;x<width;x++) {
					ptr[offset+x]|=0xff000000;
				}
			}

			surface->UnlockRect();
		}
		char FileNameEnds[40]=".bmp\0\0\0\0.jpg\0\0\0\0.dds\0\0\0\0.png\0\0\0\0.tga\0\0\0";
		char FileNameEnd[8];
		char FileNameStart[240];
		char FileName[256];
		char Number[6];
		FileNameStart[0] = '\0';
		struct _stat64i32 unused;
		if (strlen(SSDir) > 0) {
			bool usedir = true;
			if (_stat64i32(SSDir, &unused) == -1 && !CreateDirectory(SSDir, NULL)) usedir = false;
			if (usedir) {
				strcat_s(FileNameStart, 240, SSDir);
				strcat_s(FileNameStart, 240, "\\");
			}
		}
		strcat_s(FileNameStart, 240, SSName);
		for (int i = 0; i < 8; ++i) FileNameEnd[i] = FileNameEnds[i + SSFormat * 8];
		for (unsigned long ui = 1; ui <= 99999; ++ui) {
			FileName[0] = '\0';
			strcat_s(FileName, 256, FileNameStart);
			char* FNamEnd = FileName + strlen(FileName);
			_ultoa_s(ui, Number, 6, 10);
			for (int i = strlen(Number); i < SSMinNumChars; ++i) *(FNamEnd++) = '0';
			*FNamEnd = '\0';
			strcat_s(FileName, 256, Number);
			strcat_s(FileName, FileNameEnd);
			if (_stat64i32(FileName, &unused) == -1) {
				switch (SSFormat) {
					case 0:
						hr = D3DXSaveSurfaceToFile(FileName, D3DXIFF_BMP, surface, NULL, pRect);
						break;
					case 1:
						hr = D3DXSaveSurfaceToFile(FileName, D3DXIFF_JPG, surface, NULL, pRect);
						break;
					case 2:
						hr = D3DXSaveSurfaceToFile(FileName, D3DXIFF_DDS, surface, NULL, pRect);
						break;
					case 3:
						hr = D3DXSaveSurfaceToFile(FileName, D3DXIFF_PNG, surface, NULL, pRect);
						break;
					case 4:
						hr = D3DXSaveSurfaceToFile(FileName, D3DXIFF_TGA, surface, NULL, pRect);
						break;
					default:
						hr = -1;                    
				}
			break;
			}
		}
	}
	if(hr == D3D_OK) {
		SETSTATUS("Screen shot saved");
	} else {
		SETSTATUS("Screen shot failed");
	}
	surface->Release();
}