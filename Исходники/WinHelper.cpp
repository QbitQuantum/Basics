	int loadIcon32(HGDIOBJ& image, HINSTANCE hInst, LPCTSTR id , int size , int bits, bool preferIcon) {
		image = 0;
		HRSRC hr;
		HGLOBAL hg;
		int imageType=-1;
		void * p = 0;
		if (!hInst) {
			FILE * file = fopen(id , "rb");
			if (!file) goto end;
			fseek(file , 0 , SEEK_END);
			int size = ftell(file);
			rewind(file);
			if (size < SIZEOF_NEWHEADER) {fclose(file); return 0;}
			p = malloc(size);
			fread(p , 1 , size , file);
			fclose(file);
		} else {
			hr = FindResource(hInst , id , RT_GROUP_ICON);
			if (!hr) goto end;
			hg = LoadResource(hInst , hr);
			if (!hg) goto end;
			p = LockResource(hg);
			if (!p) goto end;
		}
		NEWHEADER * nh = (NEWHEADER *)p;
		RESDIR * rd;
		rd = (RESDIR *)((long)p+SIZEOF_NEWHEADER);
		RESDIR* found = 0;
		int rsize = 0;
		int sizev = size; // rozmiar pionowy
		for (int i = 0; i < nh->ResCount; i++ , rd++) {
			if (rd->ResInfo.Icon.Width == size || !found) {
				if (!size) size = rd->ResInfo.Icon.Width;
				if (rd->BitCount <= bits || !found) {
					//found = hInst?rd->IconCursorId & 0xFFFF : rd->IconCursorId;
					found = rd;
					rsize = rd->BytesInRes;

					sizev = rd->ResInfo.Icon.Width == rd->ResInfo.Icon.Height 
						?size : ceilf(float(size / rd->ResInfo.Icon.Width) * rd->ResInfo.Icon.Height);
				}
				if (rd->ResInfo.Icon.Width == size && rd->BitCount == bits) break;
			}
			if (hInst) rd = (RESDIR*)((char*)rd - 2); // Korygujemy pozycjê...
		}
		if (!found) goto end;
		void * p2 = 0;
		if (!hInst) {
			p2 = (char*)p + found->IconCursorId;
		} else {
			hr = FindResource(hInst , MAKEINTRESOURCE(found->IconCursorId & 0xFFFF) , RT_ICON);
			if (!hr) goto end;
			hg = LoadResource(hInst , hr);
			//    = SizeofResource(hInst , hr);
			if (!hg || !rsize) goto end;
			p2 = LockResource(hg);
			if (!p2) goto end;
		}
		if (found->BitCount == 32 && (!isComctl(6,0) || !preferIcon)) {
			
			BITMAPV5HEADER bi;
			BITMAPV5HEADER* _bi = (BITMAPV5HEADER*)p2;

			ZeroMemory(&bi,sizeof(BITMAPV5HEADER));
			bi.bV5Size = sizeof(BITMAPV5HEADER);
			bi.bV5Width = _bi->bV5Width;
			bi.bV5Height = _bi->bV5Height / 2;
			bi.bV5Planes = _bi->bV5Planes;
			bi.bV5BitCount = 32;
			bi.bV5Compression = BI_BITFIELDS;
			bi.bV5RedMask   =  0x00FF0000;
			bi.bV5GreenMask =  0x0000FF00;
			bi.bV5BlueMask  =  0x000000FF;
			bi.bV5AlphaMask =  0xFF000000; 

			void * bmpData;
			char* _bmpData = (char*)p2 + _bi->bV5Size;
				
			HDC hdc;
			hdc = GetDC(NULL);
			// Create the DIB section with an alpha channel.
			image = (HGDIOBJ)CreateDIBSection(hdc, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&bmpData, NULL, (DWORD)0);
			memcpy(bmpData, _bmpData, bi.bV5Width * bi.bV5Height * 4);
			ReleaseDC(0, hdc);

			if (found->ResInfo.Icon.Width != size || found->ResInfo.Icon.Height != sizev) {
				// zmiana rozmiaru


			}
			
			imageType = IMAGE_BITMAP;
		} else {
			image = (HGDIOBJ)CreateIconFromResourceEx((PBYTE)p2 , rsize , true , 0x00030000 , size , sizev , 0);
			imageType = IMAGE_ICON;
		}
end:
		if (!hInst && p) 
			free(p);
		return imageType;
	}