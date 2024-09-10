///Convert the given RGB array to a JPEG image. The JPEG image is returned in a BYTE array while the length of the array is returned through parameter
BYTE* convertToJPEG(BYTE* RGBArray, UINT &length) {
    BITMAPINFO bmi;											//Create bitmap header
    memset(&bmi, 0, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = 1920;
    bmi.bmiHeader.biHeight = -1080;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biBitCount = 24;

    Gdiplus::Bitmap* myImage = new Gdiplus::Bitmap(&bmi, RGBArray);		//Form bitmap out of provided RGB array
    IStream *jpgStream;
    CLSID jpgClsid;
    GetEncoderClsid(L"image/jpeg", &jpgClsid);				//Get the encoder
    CreateStreamOnHGlobal(NULL, TRUE, &jpgStream);			//Get direct access to physical memory. Create a stream to save directly into it. Delete when stream is released
    myImage->Save(jpgStream, &jpgClsid);					//Save the jpg image into physical memory
    STATSTG stats;
    jpgStream->Stat(&stats, STATFLAG_NONAME);				//Get stats of the jpg image; more importantly, the size
    BYTE *jpg = new BYTE[stats.cbSize.QuadPart];			//Create byte array for transferring image to.
    ULONG read;
    LARGE_INTEGER lg;
    lg.QuadPart = 0;
    jpgStream->Seek(lg, STREAM_SEEK_SET, NULL);				//Move to beginning of stream
    jpgStream->Read(jpg, stats.cbSize.QuadPart, &read);		//Read entire stream into the array
    jpgStream->Release();									//Release the stream
    length = stats.cbSize.QuadPart;							//Save the length of the byte array
    return jpg;

}