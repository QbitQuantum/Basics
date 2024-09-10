	BitmapWrapperD2D::BitmapWrapperD2D(bitmap bmp)
	{
		IWICBitmap* wic = 0;

		Graphics::locator.getfactory()->CreateBitmapFromMemory(
			bmp.width(), bmp.height(),
			GUID_WICPixelFormat32bppBGRA,
			4 * bmp.width(),
			bmp.length(),
			(BYTE*)bmp.data(),
			&wic);

		if (wic != 0)
		{
			IWICFormatConverter* converter = nullptr;
			IWICBitmap* temp = nullptr;
			int result = Graphics::locator.getfactory()->CreateFormatConverter(&converter);
			if (result == 0)
			{
				converter->Initialize(wic,
					GUID_WICPixelFormat32bppPBGRA,
					WICBitmapDitherTypeNone, 0, 0.f,
					WICBitmapPaletteTypeMedianCut);
				Graphics::locator.getfactory()->CreateBitmapFromSource(converter, WICBitmapNoCache, &temp);
				converter->Release();
			}
			wic->Release();

			ID2D1BitmapRenderTarget* target = Graphics::locator.gettarget();
			if (target)
			{
				target->CreateBitmapFromWicBitmap(temp, &source);
				temp->Release();
				temp = nullptr;
			}
			else
			{
				source = nullptr;
			}
		}
		else
		{
			source = nullptr;
		}
	}