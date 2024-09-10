static bool ASCOM_Image(IDispatch *cam, usImage& Image, bool takeSubframe, const wxRect& subframe, EXCEPINFO *excep)
{
    // returns true on error, false if OK

    DISPPARAMS dispParms;
    dispParms.cArgs = 0;
    dispParms.rgvarg = NULL;
    dispParms.cNamedArgs = 0;
    dispParms.rgdispidNamedArgs = NULL;

    Variant vRes;
    HRESULT hr;

    if (FAILED(hr = cam->Invoke(dispid_imagearray, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET,
        &dispParms, &vRes, excep, NULL)))
    {
        LogExcep(hr, "invoke imagearray", *excep);
        return true;
    }

    SAFEARRAY *rawarray = vRes.parray;

    long ubound1, ubound2, lbound1, lbound2;
    SafeArrayGetUBound(rawarray, 1, &ubound1);
    SafeArrayGetUBound(rawarray, 2, &ubound2);
    SafeArrayGetLBound(rawarray, 1, &lbound1);
    SafeArrayGetLBound(rawarray, 2, &lbound2);

    long *rawdata;
    hr = SafeArrayAccessData(rawarray, (void**)&rawdata);
    if (hr != S_OK)
    {
        hr = SafeArrayDestroyData(rawarray);
        return true;
    }

    long xsize = ubound1 - lbound1 + 1;
    long ysize = ubound2 - lbound2 + 1;
    if ((xsize < ysize) && (Image.Size.GetWidth() > Image.Size.GetHeight())) // array has dim #'s switched, Tom..
    {
        std::swap(xsize, ysize);
    }

    if (takeSubframe)
    {
        Image.Subframe = subframe;

        // Clear out the image
        Image.Clear();

        int i = 0;
        for (int y = 0; y < subframe.height; y++)
        {
            unsigned short *dataptr = Image.ImageData + (y + subframe.y) * Image.Size.GetWidth() + subframe.x;
            for (int x = 0; x < subframe.width; x++, i++)
                *dataptr++ = (unsigned short) rawdata[i];
        }
    }
    else
    {
        for (int i = 0; i < Image.NPixels; i++)
            Image.ImageData[i] = (unsigned short) rawdata[i];
    }

    hr = SafeArrayUnaccessData(rawarray);
    hr = SafeArrayDestroyData(rawarray);

    return false;
}