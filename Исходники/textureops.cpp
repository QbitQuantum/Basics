bool LoadImageFromBitmap(HDC hdc, HBITMAP hbit, Image& img)
{
	BITMAP bit;

	if (!GetObject(hbit, sizeof(BITMAP), (LPSTR)&bit)) 
	{
		FatalError("couldnt get object");
		return false;
	}

	switch(bit.bmBitsPixel)
	{
	case 8:
		img.format = Image::A8;
		break;
	case 16: //why not R5G6B5?
		img.format = Image::R8G8B8;
		break;
	case 24: //why not A8R8G8B8?
	case 32:
		img.format = Image::R8G8B8;
		break;
	default:
		FatalError("Unknown bitmap color depth, %d", bit.bmBitsPixel);
		return NULL;
		break;
	}

	img.initialize(bit.bmWidth,bit.bmHeight,img.format);

	BITMAPINFO bi;
	ZeroMemory(&bi, sizeof(bi));
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = img.w;
	bi.bmiHeader.biHeight = img.h;
	bi.bmiHeader.biBitCount = img.pixelBPP();
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biSizeImage = 0;
	bi.bmiHeader.biCompression = BI_RGB;

	if( 0 == GetDIBits(hdc, hbit, 0, img.h, img.data, &bi, DIB_RGB_COLORS))
	{
		FatalError("couldnt get bits!");
		return false;
	}

	return true;
}