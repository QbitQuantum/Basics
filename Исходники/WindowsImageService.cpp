			void WindowsImageFrame::Initialize(IWICBitmapSource* bitmapSource)
			{
				IWICImagingFactory* factory=GetWICImagingFactory();
				ComPtr<IWICFormatConverter> converter;
				{
					IWICFormatConverter* formatConverter=0;
					HRESULT hr=factory->CreateFormatConverter(&formatConverter);
					if(SUCCEEDED(hr))
					{
						converter=formatConverter;
						converter->Initialize(
							bitmapSource,
							GUID_WICPixelFormat32bppPBGRA,
							WICBitmapDitherTypeNone,
							NULL,
							0.0f,
							WICBitmapPaletteTypeCustom);
					}
				}

				IWICBitmap* bitmap=0;
				IWICBitmapSource* convertedBitmapSource=0;
				if(converter)
				{
					convertedBitmapSource=converter.Obj();
				}
				else
				{
					convertedBitmapSource=bitmapSource;
				}
				HRESULT hr=factory->CreateBitmapFromSource(convertedBitmapSource, WICBitmapCacheOnLoad, &bitmap);
				if(SUCCEEDED(hr))
				{
					frameBitmap=bitmap;
				}
			}