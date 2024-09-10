	void BaseManager::saveImage(int _width, int _height, MyGUI::PixelFormat _format, void* _texture, const std::string& _filename)
	{
		Gdiplus::PixelFormat format;
		int bpp;

		if (_format == MyGUI::PixelFormat::R8G8B8A8)
		{
			bpp = 4;
			format = PixelFormat32bppARGB;
		}
		else if (_format == MyGUI::PixelFormat::R8G8B8)
		{
			bpp = 3;
			format = PixelFormat24bppRGB;
		}
		else if (_format == MyGUI::PixelFormat::L8A8)
		{
			bpp = 2;
			format = PixelFormat16bppGrayScale;
		}
		else
		{
			MYGUI_LOG(Error, "Unsuitable texture format for saving.");
			return;
		}

		UINT num, size;
		Gdiplus::GetImageEncodersSize(&num, &size);

		Gdiplus::ImageCodecInfo* imageCodecInfo = (Gdiplus::ImageCodecInfo*)malloc(size);
		GetImageEncoders(num, size, imageCodecInfo);

		CLSID* pngClsid = NULL;
		for (UINT j = 0; j < num; ++j)
		{
			if (wcscmp(imageCodecInfo[j].MimeType, L"image/png") == 0)
			{
				pngClsid = &imageCodecInfo[j].Clsid;
				break;
			}
		}

		if (pngClsid == NULL)
		{
			MYGUI_LOG(Error, "png codec not found");
			return;
		}

		Gdiplus::Bitmap image(_width, _height, bpp * _width, format, (BYTE*)_texture);

		HRESULT res = image.Save(MyGUI::UString(_filename).asWStr_c_str(), pngClsid, NULL);
		if (res != S_OK)
			MYGUI_LOG(Error, "Texture saving error. result = " << res);
	}