    HRESULT YCbCrPixelFormatConverter::ConvertRgbToYCbCr( 
        /* [in] */ const WICRect *prc,
        /* [in] */ UINT cbStride,
        /* [in] */ UINT cbPixelsSize,
        /* [out] */ BYTE *pbPixels)
    {
        HRESULT result = S_OK;
        
        //Sanity check
        WICPixelFormatGUID srcPixelFormat;
        bitmapSource->GetPixelFormat(&srcPixelFormat);
        if (srcPixelFormat != GUID_WICPixelFormat32bppBGRA)
        {
             result = E_UNEXPECTED;
             return result;
        }

        IWICImagingFactory *codecFactory = NULL;
        IWICFormatConverter *formatConverter = NULL;    

        if (SUCCEEDED(result))
        {
            result = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*) &codecFactory);
        }

        if (SUCCEEDED(result))
        {             
            result = codecFactory->CreateFormatConverter(&formatConverter);        
        }
        
        if (SUCCEEDED(result))
        {
            //We will convert to 24RGB first, since it is easier to convert to YCbCr from there
            result = formatConverter->Initialize(bitmapSource,
                GUID_WICPixelFormat24bppBGR, WICBitmapDitherTypeSolid, NULL, 1.0, WICBitmapPaletteTypeFixedWebPalette);
        }

        if (SUCCEEDED(result))
        {
            result = formatConverter->CopyPixels(prc, cbStride, cbPixelsSize, pbPixels);
        }
        //Since the two formats have same number of bytes, we will do an inplace conversion
        UINT width, height;
        if (prc == NULL)
        {
            if (SUCCEEDED(result))
            {
                result = bitmapSource->GetSize(&width, &height);
            }
        }
        else
        {
            width = prc->Width;
            height = prc->Height;
        }

        if (SUCCEEDED(result))
        {
            //Loop on the data and do the conversion
            BYTE *curPos = NULL;            
            curPos = pbPixels;
            for (int i = 0 ; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                BYTE R, G ,B;
                BYTE Y, Cb, Cr;

                B = *curPos;
                G = *(curPos+1);
                R = *(curPos+2);      

                //Do the maths
                Y = Clamp(0, 255, (0.257*R) + (0.504*G) + (0.098*B) + 16);
                Cb = Clamp(0, 255, (-0.148*R) - (0.291*G) + (0.439*B) + 128);
                Cr = Clamp(0, 255, (0.439*R) - (0.368*G) - (0.071*B) + 128);

                *curPos = Cr;
                *(curPos+1) = Cb;
                *(curPos+2) = Y;      
                   
                //Advance to next pixel
                curPos += 3;
                }
                curPos += (cbStride - (width * 3)); //Fast forward remaining part of the stride
            }
        }
        if (formatConverter)
        {
            formatConverter->Release();
        }

        if (codecFactory)
        {
            codecFactory->Release();
        }
        return result;
       }  