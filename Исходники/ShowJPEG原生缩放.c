LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l)
{
	HDC hdc;// = GetDC(hwnd);
	PAINTSTRUCT ps;
	RECT rect;
	BITMAPINFO bmi;
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(1);
		break;
	case WM_PAINT: {
		hdc=BeginPaint(hwnd,&ps);
		//GetWindowRect(hwnd,&rect);
		//RedrawWindow(hwnd,&rect,0,0);
		if(num==vs.length-1)exit(0);
		readjpeg(vs.strs[num++], &img);
		bmi.bmiHeader.biWidth = img.Width;
		bmi.bmiHeader.biHeight = img.Height;
		//SetDIBitsToDevice(hdc, 0, 0, img.Width, img.Height,0, 0, 0, img.Height, img.Data, &bmi, DIB_RGB_COLORS);
		SetStretchBltMode(hdc,STRETCH_HALFTONE);//注意第二个参数会影响显示质量
		StretchDIBits(hdc, 0, 0, img.Width/2, img.Height/2,0, 0,img.Width,img.Height, img.Data, &bmi, DIB_RGB_COLORS,SRCCOPY);
		free(img.Data);
		EndPaint(hwnd,&ps);
	}
	break;
	default:
		return DefWindowProc(hwnd, msg, w, l);
	}
	return 0;
}