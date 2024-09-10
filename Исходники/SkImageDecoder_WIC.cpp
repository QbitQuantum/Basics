bool SkImageEncoder_WIC::onEncode(SkWStream* stream
                                , const SkBitmap& bitmapOrig
                                , int quality)
{
    GUID type;
    switch (fType) {
        case kBMP_Type:
            type = GUID_ContainerFormatBmp;
            break;
        case kICO_Type:
            type = GUID_ContainerFormatIco;
            break;
        case kJPEG_Type:
            type = GUID_ContainerFormatJpeg;
            break;
        case kPNG_Type:
            type = GUID_ContainerFormatPng;
            break;
        default:
            return false;
    }

    //Convert to 8888 if needed.
    const SkBitmap* bitmap;
    SkBitmap bitmapCopy;
    if (kN32_SkColorType == bitmapOrig.colorType() && bitmapOrig.isOpaque()) {
        bitmap = &bitmapOrig;
    } else {
        if (!bitmapOrig.copyTo(&bitmapCopy, kN32_SkColorType)) {
            return false;
        }
        bitmap = &bitmapCopy;
    }

    // We cannot use PBGRA so we need to unpremultiply ourselves
    if (!bitmap->isOpaque()) {
        SkAutoLockPixels alp(*bitmap);

        uint8_t* pixels = reinterpret_cast<uint8_t*>(bitmap->getPixels());
        for (int y = 0; y < bitmap->height(); ++y) {
            for (int x = 0; x < bitmap->width(); ++x) {
                uint8_t* bytes = pixels + y * bitmap->rowBytes() + x * bitmap->bytesPerPixel();

                SkPMColor* src = reinterpret_cast<SkPMColor*>(bytes);
                SkColor* dst = reinterpret_cast<SkColor*>(bytes);

                *dst = SkUnPreMultiply::PMColorToColor(*src);
            }
        }
    }

    //Initialize COM.
    SkAutoCoInitialize scopedCo;
    if (!scopedCo.succeeded()) {
        return false;
    }

    HRESULT hr = S_OK;

    //Create Windows Imaging Component ImagingFactory.
    SkTScopedComPtr<IWICImagingFactory> piImagingFactory;
    if (SUCCEEDED(hr)) {
        hr = CoCreateInstance(
            CLSID_WICImagingFactory
            , nullptr
            , CLSCTX_INPROC_SERVER
            , IID_PPV_ARGS(&piImagingFactory)
        );
    }

    //Convert the SkWStream to an IStream.
    SkTScopedComPtr<IStream> piStream;
    if (SUCCEEDED(hr)) {
        hr = SkWIStream::CreateFromSkWStream(stream, &piStream);
    }

    //Create an encode of the appropriate type.
    SkTScopedComPtr<IWICBitmapEncoder> piEncoder;
    if (SUCCEEDED(hr)) {
        hr = piImagingFactory->CreateEncoder(type, nullptr, &piEncoder);
    }

    if (SUCCEEDED(hr)) {
        hr = piEncoder->Initialize(piStream.get(), WICBitmapEncoderNoCache);
    }

    //Create a the frame.
    SkTScopedComPtr<IWICBitmapFrameEncode> piBitmapFrameEncode;
    SkTScopedComPtr<IPropertyBag2> piPropertybag;
    if (SUCCEEDED(hr)) {
        hr = piEncoder->CreateNewFrame(&piBitmapFrameEncode, &piPropertybag);
    }

    if (SUCCEEDED(hr)) {
        PROPBAG2 name = { 0 };
        name.dwType = PROPBAG2_TYPE_DATA;
        name.vt = VT_R4;
        name.pstrName = L"ImageQuality";

        VARIANT value;
        VariantInit(&value);
        value.vt = VT_R4;
        value.fltVal = (FLOAT)(quality / 100.0);

        //Ignore result code.
        //  This returns E_FAIL if the named property is not in the bag.
        //TODO(bungeman) enumerate the properties,
        //  write and set hr iff property exists.
        piPropertybag->Write(1, &name, &value);
    }
    if (SUCCEEDED(hr)) {
        hr = piBitmapFrameEncode->Initialize(piPropertybag.get());
    }

    //Set the size of the frame.
    const UINT width = bitmap->width();
    const UINT height = bitmap->height();
    if (SUCCEEDED(hr)) {
        hr = piBitmapFrameEncode->SetSize(width, height);
    }

    //Set the pixel format of the frame.
    const WICPixelFormatGUID formatDesired = GUID_WICPixelFormat32bppBGRA;
    WICPixelFormatGUID formatGUID = formatDesired;
    if (SUCCEEDED(hr)) {
        hr = piBitmapFrameEncode->SetPixelFormat(&formatGUID);
    }
    if (SUCCEEDED(hr)) {
        //Be sure the image format is the one requested.
        hr = IsEqualGUID(formatGUID, formatDesired) ? S_OK : E_FAIL;
    }

    //Write the pixels into the frame.
    if (SUCCEEDED(hr)) {
        SkAutoLockPixels alp(*bitmap);
        const UINT stride = (UINT) bitmap->rowBytes();
        hr = piBitmapFrameEncode->WritePixels(
            height
            , stride
            , stride * height
            , reinterpret_cast<BYTE*>(bitmap->getPixels()));
    }

    if (SUCCEEDED(hr)) {
        hr = piBitmapFrameEncode->Commit();
    }

    if (SUCCEEDED(hr)) {
        hr = piEncoder->Commit();
    }

    return SUCCEEDED(hr);
}