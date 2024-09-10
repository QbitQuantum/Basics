void QFObjectRenderer::captureFrame(IString saveAsFileName, FOURCC ioProc)
{
  HMMIO frameFile;
  MMIOINFO info = {0};
  LONG bytesWritten;
  MMIMAGEHEADER header = {0};
  PBYTE frameBuffer;
  ULONG scanLineBytes, scanLines;
  LONG errorCode;

  info.fccIOProc = ioProc;
  info.ulTranslate = MMIO_TRANSLATEHEADER | MMIO_TRANSLATEDATA;

  errorCode = DiveBeginImageBufferAccess(dive, frame[currentColumn][currentRow],
                                         &frameBuffer, &scanLineBytes, &scanLines);

  header.ulHeaderLength = sizeof(MMIMAGEHEADER);
  header.ulContentType = MMIO_IMAGE_PHOTO;
  header.ulMediaType = MMIO_MEDIATYPE_IMAGE;
  header.mmXDIBHeader.XDIBHeaderPrefix.ulMemSize = scanLineBytes * scanLines; /*  Length of bitmap. */
  header.mmXDIBHeader.XDIBHeaderPrefix.ulPelFormat = FOURCC_BGR3; /*  FOURCC code defining the pel format. */
  header.mmXDIBHeader.BMPInfoHeader2.cbFix = sizeof (BITMAPINFOHEADER2);
  header.mmXDIBHeader.BMPInfoHeader2.cx = movieSize().width();
  header.mmXDIBHeader.BMPInfoHeader2.cy = movieSize().height();
  header.mmXDIBHeader.BMPInfoHeader2.cPlanes = 1; /*  Number of planes. */
  header.mmXDIBHeader.BMPInfoHeader2.cBitCount = 24; /*  Bits per pel. */
  header.mmXDIBHeader.BMPInfoHeader2.ulCompression = BCA_UNCOMP;
  header.mmXDIBHeader.BMPInfoHeader2.cbImage = header.mmXDIBHeader.XDIBHeaderPrefix.ulMemSize;
  header.mmXDIBHeader.BMPInfoHeader2.usRecording = BRA_BOTTOMUP; /*  Must be BRA_BOTTOMUP. */
  header.mmXDIBHeader.BMPInfoHeader2.usRendering = BRH_NOTHALFTONED; /*  Not used. */

  frameFile = mmioOpen(saveAsFileName, &info, MMIO_CREATE | MMIO_WRITE);
  mmioSetHeader(frameFile, &header, sizeof(MMIMAGEHEADER), &bytesWritten, 0, 0);
  mmioWrite(frameFile, frameBuffer, header.mmXDIBHeader.XDIBHeaderPrefix.ulMemSize);
  mmioClose(frameFile, 0);

  errorCode = DiveEndImageBufferAccess(dive, frame[currentColumn][currentRow]);
}