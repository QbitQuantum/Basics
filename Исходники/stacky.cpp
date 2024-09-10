    static bool convert_file_icon(const HICON icon, Bmp& bmp) {
        static IWICImagingFactory* img_factory = 0;
        if (!img_factory) {
            // In VS 2011 beta, clsid has to be changed to CLSID_WICImagingFactory1 (from CLSID_WICImagingFactory)
            if (!SUCCEEDED(::CoInitialize(0)) || !SUCCEEDED(::CoCreateInstance(CLSID_WICImagingFactory1, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&img_factory)))) {
                return false;
            }
        }
        IWICBitmap* pBitmap = 0;
        IWICFormatConverter* pConverter = 0;
        UINT cx = 0, cy = 0;
	    if (SUCCEEDED(img_factory->CreateBitmapFromHICON(icon, &pBitmap))) {
		    if (SUCCEEDED(img_factory->CreateFormatConverter(&pConverter))) {
			    if (SUCCEEDED(pConverter->Initialize(pBitmap, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, 0, 0.0f, WICBitmapPaletteTypeCustom))) {
				    if (SUCCEEDED(pConverter->GetSize(&cx, &cy))) {
						const UINT stride = cx * sizeof(DWORD);
						const UINT buf_size = cy * stride;
                        Byte* buf = new Byte[buf_size];
						pConverter->CopyPixels(0, stride, buf_size, buf);
                        bmp.load_bits_only(buf, buf_size, cx, -(int)cy);
                        delete [] buf;
				    }
			    }
			    pConverter->Release();
		    }
		    pBitmap->Release();
	    }
        return true;
    }