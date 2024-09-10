int aviOpen(HWND hwndOwner, char* filename, int fps)
{
    AVICOMPRESSOPTIONS options;
    AVICOMPRESSOPTIONS* optionsPtr;
    AVISTREAMINFO steamHdr;
    AVISTREAMINFO soundHdr;
    WAVEFORMATEX wfex;
    BITMAPINFOHEADER bi;

    AVIFileInit();

    frameCount = 0;
    sampleCount = 0;
    aviStatusOk  = 0;

    if (AVIFileOpen(&aviFile, filename, OF_WRITE | OF_CREATE, NULL) != 0) {
        return 0;
    }

	memset(&bi, 0, sizeof(bi));      
	bi.biSize       = 0x28;    
	bi.biPlanes     = 1;
	bi.biBitCount   = 32;
	bi.biWidth      = 320 * zoom;
	bi.biHeight     = 240 * zoom;
	bi.biSizeImage  = bi.biWidth * bi.biHeight * bi.biBitCount / 8;

    memset(&steamHdr, 0, sizeof(steamHdr));
    steamHdr.fccType = streamtypeVIDEO;
    steamHdr.dwScale = 1;
    steamHdr.dwRate  = fps;
    steamHdr.dwSuggestedBufferSize = bi.biSizeImage;

    if (AVIFileCreateStream(aviFile, &aviStream, &steamHdr) != 0) {
        return 0;
    }
      
    memset(&options, 0, sizeof(options));
    optionsPtr = &options;
    if (!AVISaveOptions(hwndOwner, 0, 1, &aviStream, &optionsPtr)) {
        return 0;
    }
  
    if (AVIMakeCompressedStream(&aviVidStream, aviStream, &options, NULL) != 0) {
        return 0;
    }
  
    // setup the video stream format
    if (AVIStreamSetFormat(aviVidStream, 0, &bi, bi.biSize + bi.biClrUsed * sizeof(RGBQUAD)) != 0) {
        return 0;
    }

    memset(&wfex, 0, sizeof(wfex));
    wfex.wFormatTag      = WAVE_FORMAT_PCM;
    wfex.nChannels       = 2;
    wfex.nSamplesPerSec  = 44100;
    wfex.wBitsPerSample  = 8 * sizeof(Int16);
    wfex.nBlockAlign     = wfex.nChannels * wfex.wBitsPerSample / 8;
    wfex.nAvgBytesPerSec = wfex.nSamplesPerSec * wfex.nBlockAlign;
    
    memset(&soundHdr, 0, sizeof(soundHdr));
    soundHdr.fccType         = streamtypeAUDIO;
    soundHdr.dwQuality       = (DWORD)-1;
    soundHdr.dwScale         = wfex.nBlockAlign;
    soundHdr.dwInitialFrames = 0;
    soundHdr.dwRate          = wfex.nAvgBytesPerSec;
    soundHdr.dwSampleSize    = wfex.nBlockAlign;

    if (AVIFileCreateStream(aviFile, &aviSndStream, &soundHdr) != 0) {
        return 0;
    }

    if (AVIStreamSetFormat(aviSndStream, 0, (void *)&wfex, sizeof(wfex)) != 0) {
        return 0;
    }

    aviStatusOk = 1;

    return 1;
}