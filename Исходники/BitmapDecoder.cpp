    //@https://msdn.microsoft.com/de-de/library/windows/desktop/dd756686(v=vs.85).aspx
    HRESULT BitmapDecoder::LoadBitmapFromFile(ID2D1RenderTarget * pRenderTarget, PCWSTR uri, ID2D1Bitmap ** ppBitmap)
    {

      IWICImagingFactory* pFactory;


      HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IWICImagingFactory,
        (LPVOID*)&pFactory
      );



      //IWICStream *pStream = NULL; //?

      //IWICBitmapScaler *pScaler = NULL; //?

      IWICBitmapDecoder *pDecoder = NULL;
      if (SUCCEEDED(hr))
      {
        hr = pFactory->CreateDecoderFromFilename(uri, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
      }
      IWICBitmapFrameDecode *pSource = NULL;
      if (SUCCEEDED(hr))
      {
        hr = pDecoder->GetFrame(0, &pSource);
      }

      IWICFormatConverter *pConverter = NULL;
      if (SUCCEEDED(hr))
      {
        hr = pFactory->CreateFormatConverter(&pConverter);
      }

      if (SUCCEEDED(hr))
      {
        hr = pConverter->Initialize(
          pSource,
          GUID_WICPixelFormat32bppPBGRA,
          WICBitmapDitherTypeNone,
          NULL,
          0.f,
          WICBitmapPaletteTypeMedianCut
        );
      }

      if (SUCCEEDED(hr))
      {
        pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, ppBitmap);
      }
      if (pDecoder != nullptr)
      {
        pDecoder->Release();//SafeRelease(&pDecoder);
      }
      if (pSource != nullptr)
      {
        pSource->Release();
      }
      //SafeRelease(&pSource);
     // pStream->Release();//SafeRelease(&pStream);
      if(pConverter!= nullptr)
      {
        pConverter->Release();
      }
      //SafeRelease(&pConverter);
     // pScaler->Release();//SafeRelease(&pScaler);
      if (pFactory != nullptr)
      {
        pFactory->Release();
      }

      return hr;
    }