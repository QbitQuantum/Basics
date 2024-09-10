void CTextToolView::DoFontSavefontfiles(CString szPathName)
{
  CString	szPNGName = szPathName + ".png";
  CString	szMetricFileName = szPathName + ".fmt";

  CDC	*pDC = GetDC();
  CDC	*pDrawDC = pDC;//new CDC;

  Invalidate(true);
  // pDrawDC->CreateCompatibleDC(pDC);

  if (!pDrawDC)
    return;

  int iImageY = m_iMaxY;

  int iPictureY = iImageY;

  int y2 = 4;

  // find next greater power of two
  while (iPictureY > y2) {
    y2 <<= 1;
  }
  iPictureY = y2;

  // fill the DC with black
  CRect	rect;
  CBrush	blackBrush(RGB(0,0,0));

  COLORREF      rPixel = RGB(0,0,0);

  rect.SetRect(0,0,m_iMaxTextureWidth,iImageY);

  pDrawDC->FillRect(&rect,&blackBrush);
  OnDraw(pDrawDC);

  std::ofstream* f = new std::ofstream(szPNGName, std::ios::out | std::ios::binary);

  int temp = 0; //temporary values for binary file writing
  char tempByte = 0;
  int crc = 0;  //used for running CRC values

  int w = 512, h = iPictureY;
  unsigned long blength = (w + 1) * h * 4;
  char* b = new char[blength];

  // Write PNG headers
  (*f) << "\211PNG\r\n\032\n";
#define	  PNGTAG(t_) ((((int)t_[0]) << 24) | \
		      (((int)t_[1]) << 16) | \
		      (((int)t_[2]) <<  8) | \
			(int)t_[3])

  // IHDR chunk
  temp = htonl((int) 13);       //(length) IHDR is always 13 bytes long
  f->write((char*) &temp, 4);
  temp = htonl(PNGTAG("IHDR")); //(tag) IHDR
  f->write((char*) &temp, 4);
  crc = crc32(crc, (unsigned char*) &temp, 4);
  temp = htonl(w);	      //(data) Image width
  f->write((char*) &temp, 4);
  crc = crc32(crc, (unsigned char*) &temp, 4);
  temp = htonl(h);		//(data) Image height
  f->write((char*) &temp, 4);
  crc = crc32(crc, (unsigned char*) &temp, 4);
  tempByte = 8;		 //(data) Image bitdepth (8 bits/sample = 24 bits/pixel)
  f->write(&tempByte, 1);
  crc = crc32(crc, (unsigned char*) &tempByte, 1);
  tempByte = 6;		 //(data) Color type: RGBA = 6
  f->write(&tempByte, 1);
  crc = crc32(crc, (unsigned char*) &tempByte, 1);
  tempByte = 0;
  int i;
  for (i = 0; i < 3; i++) { //(data) Last three tags are compression (only 0 allowed), filtering (only 0 allowed), and interlacing (we don't use it, so it's 0)
    f->write(&tempByte, 1);
    crc = crc32(crc, (unsigned char*) &tempByte, 1);
  }
  crc = htonl(crc);
  f->write((char*) &crc, 4);    //(crc) write crc

  // IDAT chunk

  // fill buffer with black
  for (i = 0; i < (long)blength; i++)
    b[i] = 0;
  // write image data over buffer
  for (int y = 0; y <= m_iMaxY - 1; y++) {
    const unsigned long line = y * (w * 4 + 1); //beginning of this line
    b[line] = 0;  //filter type byte at the beginning of each scanline (0 = no filter, 1 = sub filter)
    for (int x = 0; x < m_iMaxTextureWidth; x++) {
      // Grab a reference to the current pixel
      rPixel = pDrawDC->GetPixel(x, y);
      // Pixel color values
      b[line + x * 4 + 1] = GetRValue(rPixel);
      b[line + x * 4 + 2] = GetGValue(rPixel);
      b[line + x * 4 + 3] = GetBValue(rPixel);
      // Write Alpha channel as average of RGB, since it's grayscale anyhow
      b[line + x * 4 + 4] =(GetBValue(rPixel) + GetGValue(rPixel) + GetRValue(rPixel)) / 3;
    }
  }

  unsigned long zlength = blength + 15;	    //length of bz[], will be changed by zlib to the length of the compressed string contained therein
  unsigned char* bz = new unsigned char[zlength]; //just like b, but compressed; might get bigger, so give it room
  // compress b into bz
  compress2(bz, &zlength, reinterpret_cast<const unsigned char*>(b), blength, 5);
  temp = htonl(zlength);			  //(length) IDAT length after compression
  f->write((char*) &temp, 4);
  temp = htonl(PNGTAG("IDAT"));		   //(tag) IDAT
  f->write((char*) &temp, 4);
  crc = crc32(crc = 0, (unsigned char*) &temp, 4);
  f->write(reinterpret_cast<char*>(bz), zlength);  //(data) This line of pixels, compressed
  crc = htonl(crc32(crc, bz, zlength));
  f->write((char*) &crc, 4);		       //(crc) write crc

  // tEXt chunk containing bzflag build/version
  temp = htonl(28);//(length) tEXt is "Software\0BZFlag TextTool-W32"
  f->write((char*) &temp, 4);
  temp = htonl(PNGTAG("tEXt"));		   //(tag) tEXt
  f->write((char*) &temp, 4);
  crc = crc32(crc = 0, (unsigned char*) &temp, 4);
  strcpy(b, "Software"); //(data) Keyword
  f->write(reinterpret_cast<char*>(b), strlen(reinterpret_cast<const char*>(b)));
  crc = crc32(crc, reinterpret_cast<const unsigned char*>(b), strlen(b));
  tempByte = 0;					  //(data) Null character separator
  f->write(&tempByte, 1);
  crc = crc32(crc, (unsigned char*) &tempByte, 1);
  strcpy((char*) b, "BZFlag TextTool-W32");       //(data) Text contents (build/version)
  f->write(reinterpret_cast<char*>(b), strlen(reinterpret_cast<const char*>(b)));
  crc = htonl(crc32(crc, reinterpret_cast<const unsigned char*>(b), strlen(b)));
  f->write((char*) &crc, 4);		       //(crc) write crc

  // IEND chunk
  temp = htonl((int) 0);	//(length) IEND is always 0 bytes long
  f->write((char*) &temp, 4);
  temp = htonl(PNGTAG("IEND")); //(tag) IEND
  f->write((char*) &temp, 4);
  crc = htonl(crc32(crc = 0, (unsigned char*) &temp, 4));
  //(data) IEND has no data field
  f->write((char*) &crc, 4);     //(crc) write crc
  delete [] bz;
  delete [] b;
  delete f;

  // pDrawDC->DeleteDC();
  // delete(pDrawDC);
  ReleaseDC(pDC);

  FILE *fp = fopen(szMetricFileName,"wt");
  if (!fp)
    return;

  struct {
    int iInitalDist;
    int iCharWidth;
    int iWhiteSpaceDist;
    int iStartX;
    int iEndX;
    int iStartY;
    int iEndY;
  } rFontMetrics;

  int iNumChars = '~' - ' ';

  fprintf(fp,"NumChars: %d\nTextureWidth: %d\nTextureHeight: %d\nTextZStep: %d\n\n",iNumChars+1,m_iMaxTextureWidth,iPictureY,m_iTextureZStep);

  for (int iChar = 0; iChar <= iNumChars; iChar++) {
    rFontMetrics.iInitalDist = m_aWidths[iChar].abcA;
    rFontMetrics.iCharWidth = m_aWidths[iChar].abcB;
    rFontMetrics.iWhiteSpaceDist = m_aWidths[iChar].abcC;

    rFontMetrics.iStartX = m_arGlyphExtents[iChar].iStartX;
    rFontMetrics.iEndX = m_arGlyphExtents[iChar].iEndX;
    rFontMetrics.iStartY = m_arGlyphExtents[iChar].iStartY;
    rFontMetrics.iEndY = m_arGlyphExtents[iChar].iEndY;

    fprintf(fp,"Char: \"%c\"\nInitialDist: %d\nWidth: %d\nWhitespace: %d\n",iChar+32,rFontMetrics.iInitalDist,rFontMetrics.iCharWidth,rFontMetrics.iWhiteSpaceDist);
    fprintf(fp,"StartX: %d\nEndX: %d\nStartY: %d\nEndY: %d\n\n",rFontMetrics.iStartX,rFontMetrics.iEndX,rFontMetrics.iStartY,rFontMetrics.iEndY);
  }
  fclose(fp);

  Invalidate(true);
}