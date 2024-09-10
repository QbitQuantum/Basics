//在錄製OpengL動畫之前，首先需要設置AVI文件名稱、錄製幀的大小、錄製幀率、AVI文件壓縮方式等信息，具體的源代碼如下：
bool CAVICapture::start(CString filename,int w, int h,float fps)
{
    if (capturing)
        return false;

    width = w;
    height = h;
    frameRate = fps;

    if (HIWORD(VideoForWindowsVersion()) < 0x010a)
    {
        // 版本號必須大於1.1
        return false;
    }

    int rowBytes = (width * 3 + 3) & ~0x3;
    image = new unsigned char[rowBytes * height]; 
	//  創建AVI文件
    HRESULT hr = AVIFileOpen(&aviFile,
                             filename,
                             OF_WRITE | OF_CREATE,
                             NULL);
    if (hr != AVIERR_OK)
    {
        MessageBox(NULL,"創建AVI文件失敗","錯誤",MB_OK);
        return false;
    }
	//  AVI文件的頭信息
    AVISTREAMINFO info;
    ZeroMemory(&info, sizeof info);
    info.fccType = streamtypeVIDEO;
    info.fccHandler = 0;
    info.dwScale = 1;
    info.dwRate = (DWORD) frameRate;
    info.dwSuggestedBufferSize = rowBytes * height;
    SetRect(&info.rcFrame, 0, 0, width, height);
    hr = AVIFileCreateStream(aviFile, &aviStream, &info);//創建AVI文件流
    if (hr != AVIERR_OK)
    {
        MessageBox(NULL,"創建AVI文件流失敗","錯誤",MB_OK);
        cleanup(); //清空內存
        return false;
    }

    // 允許用戶選擇壓縮方式
    AVICOMPRESSOPTIONS options;
    AVICOMPRESSOPTIONS* arrOptions[1] = { &options };
    ZeroMemory(&options, sizeof options);
    if (!AVISaveOptions(NULL, 0, 1, &aviStream, 
                        (LPAVICOMPRESSOPTIONS*) &arrOptions))
    {
         cleanup();//清空內存
        return false;
    }

	//設置AVI壓縮方式
    hr = AVIMakeCompressedStream(&compAviStream, aviStream, &options, NULL);
    if (hr != AVIERR_OK)
    {
        MessageBox(NULL,"設置AVI壓縮方式失敗", "錯誤",MB_OK);
        cleanup();//清空內存
        return false;
    }

    BITMAPINFOHEADER bi;
    ZeroMemory(&bi, sizeof bi);
    bi.biSize = sizeof bi;
    bi.biWidth = width;
    bi.biHeight = height;
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = rowBytes * height;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;
	//  設置數據格式
    hr = AVIStreamSetFormat(compAviStream, 0, &bi, sizeof bi);
	 
    if (hr != AVIERR_OK)
    {
        MessageBox(NULL,"設置AVI數據格式","錯誤",MB_OK);
        cleanup();//清空內存
        return false;
    }

    capturing = true;
    frameCounter = 0;

    return true;
}