static bool MakeCompressedVideoStream(size_t WidthFrame, size_t HeightFrame, AVICOMPRESSOPTIONS *pVideoOptions,
                               PAVISTREAM pStreamVideo, PAVISTREAM *ppCompressedStreamVideo)
{
  BITMAPINFO bi;
  ZeroMemory(&bi, sizeof(BITMAPINFO));
  bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bi.bmiHeader.biWidth = WidthFrame;
  bi.bmiHeader.biHeight = HeightFrame;
  bi.bmiHeader.biSizeImage = WidthFrame * HeightFrame * 3;
  bi.bmiHeader.biPlanes = 1;
  bi.bmiHeader.biBitCount = 24;
  bi.bmiHeader.biCompression = BI_RGB;
  void *pBits = ((LPBYTE)&bi) + bi.bmiHeader.biSize + bi.bmiHeader.biClrUsed * sizeof(RGBQUAD);
  if(AVIERR_OK==AVIMakeCompressedStream(ppCompressedStreamVideo, pStreamVideo, pVideoOptions, NULL))
  {
    if (AVIERR_OK == AVIStreamSetFormat(*ppCompressedStreamVideo, 0, &bi, ((LPBYTE)pBits) - ((LPBYTE) &bi)))
      return true;

    AVIStreamRelease(*ppCompressedStreamVideo);
    *ppCompressedStreamVideo = 0;
  }

  bi.bmiHeader.biBitCount = 16;
  if(AVIERR_OK==AVIMakeCompressedStream(ppCompressedStreamVideo, pStreamVideo, pVideoOptions, NULL))
  {
    if (AVIERR_OK == AVIStreamSetFormat(*ppCompressedStreamVideo, 0, &bi, ((LPBYTE)pBits) - ((LPBYTE) &bi)))
      return true;

    AVIStreamRelease(*ppCompressedStreamVideo);
    *ppCompressedStreamVideo = 0;
  }

  bi.bmiHeader.biBitCount = 8;
  if(AVIERR_OK==AVIMakeCompressedStream(ppCompressedStreamVideo, pStreamVideo, pVideoOptions, NULL))
  {
    if (AVIERR_OK == AVIStreamSetFormat(*ppCompressedStreamVideo, 0, &bi, ((LPBYTE)pBits) - ((LPBYTE) &bi)))
      return true;

    AVIStreamRelease(*ppCompressedStreamVideo);
    *ppCompressedStreamVideo = 0;
  }

  return false;
}