const char *SurfacePrint(SDL_Surface * surf, const char *printcfg,
			 int showdialog)
{
  const char *res = NULL;
  HWND hWnd;
  DOCINFO di;
  int nError;
  SDL_SysWMinfo wminfo;
  BITMAPINFOHEADER bmih;
  SDL_Surface *surf24 = NULL;
  RECT rcDst;
  float sX, sY;
  int pageWidth, pageHeight;
  int hDCCaps;
  HBITMAP hbm = NULL;
  HDC hdcMem = NULL;
  int scaling = SCALE_TO_FIT;

  SDL_VERSION(&wminfo.version);
  if (!SDL_GetWMInfo(&wminfo))
    return "win32_print: SDL_GetWMInfo() failed.";

  hWnd = wminfo.window;
  if (!GetPrinterDC(hWnd, printcfg, showdialog))
  {
    ShowWindow(hWnd, SW_SHOWNORMAL);
    return NULL;
  }

  if (!hDCprinter)
    return "win32_print: GetPrinterDC() failed.";

  EnableWindow(hWnd, FALSE);

  di.cbSize = sizeof(DOCINFO);
  di.lpszDocName = "Tux Paint";
  di.lpszOutput = (LPTSTR) NULL;
  di.lpszDatatype = (LPTSTR) NULL;
  di.fwType = 0;

  nError = StartDoc(hDCprinter, &di);
  if (nError == SP_ERROR)
  {
    res = "win32_print: StartDoc() failed.";
    goto error;
  }

  nError = StartPage(hDCprinter);
  if (nError <= 0)
  {
    res = "win32_print: StartPage() failed.";
    goto error;
  }

//////////////////////////////////////////////////////////////////////////////////////

  surf24 = make24bitDIB(surf);
  if (!surf24)
  {
    res = "win32_print: make24bitDIB() failed.";
    goto error;
  }

  memset(&bmih, 0, sizeof(bmih));
  bmih.biSize = sizeof(bmih);
  bmih.biPlanes = 1;
  bmih.biCompression = BI_RGB;
  bmih.biBitCount = 24;
  bmih.biWidth = surf24->w;
  bmih.biHeight = surf24->h;

  pageWidth  = GetDeviceCaps(hDCprinter, HORZRES);
  pageHeight = GetDeviceCaps(hDCprinter, VERTRES);
  sX  = GetDeviceCaps(hDCprinter, LOGPIXELSX);
  sY  = GetDeviceCaps(hDCprinter, LOGPIXELSY);

  switch (scaling)
  {
    case STRETCH_TO_FIT:
    {
        /* stretches x and y dimensions independently to fit the page */
        /* doesn't preserve image aspect-ratio */
        rcDst.top = 0; rcDst.left = 0;
        rcDst.bottom = pageHeight; rcDst.right = pageWidth;
        break;
    }
    case SCALE_TO_FIT:
    {
        /* maximises image size on the page */
        /* preserves aspect-ratio, alignment is top and center */
        int width  = bmih.biWidth;
        int height = bmih.biHeight;

        if (width < pageWidth && height < pageHeight)
        {
            float   dW = (float)pageWidth  / width;
            float   dH = (float)pageHeight / height;

            if (dW < dH)
            {
                width  = pageWidth;
                height = (int)((height * dW * (sY/sX)) + 0.5f);
            }
            else
            {
                width  = (int)((width  * dH * (sX/sY)) + 0.5f);
                height = pageHeight;
            }
        }
        if (width > pageWidth)
        {
            height= height*width/pageWidth;
            width = pageWidth;
        }
        if (height > pageHeight)
        {
            width= width*height/pageHeight;
            height = pageHeight;
        }

        rcDst.top = 0;
        rcDst.left = (pageWidth-width)/2;
        rcDst.bottom = rcDst.top+height;
        rcDst.right  = rcDst.left+width;
        break;
    }
    default:
        res = "win32_print: invalid scaling option.";
        goto error;
  }

  hDCCaps = GetDeviceCaps(hDCprinter, RASTERCAPS);

  if (hDCCaps & RC_PALETTE)
  {
    res = "win32_print: printer context requires palette.";
    goto error;
  }

  if (hDCCaps & RC_STRETCHDIB)
  {
    SetStretchBltMode(hDCprinter, COLORONCOLOR);

    nError = StretchDIBits(hDCprinter, rcDst.left, rcDst.top,
      		     rcDst.right  - rcDst.left,
                           rcDst.bottom - rcDst.top,
      		     0, 0, bmih.biWidth, bmih.biHeight,
      		     surf24->pixels, (BITMAPINFO *) & bmih,
      		     DIB_RGB_COLORS, SRCCOPY);
    if (nError == GDI_ERROR)
    {
      res = "win32_print: StretchDIBits() failed.";
      goto error;
    }
  }
  else
  {
    res = "win32_print: StretchDIBits() not available.";
    goto error;
  }

//////////////////////////////////////////////////////////////////////////////////////

  nError = EndPage(hDCprinter);
  if (nError <= 0)
  {
    res = "win32_print: EndPage() failed.";
    goto error;
  }

  EndDoc(hDCprinter);

error:
  if (hdcMem)
    DeleteDC(hdcMem);
  if (hbm)
    DeleteObject(hbm);
  if (surf24)
    SDL_FreeSurface(surf24);

  EnableWindow(hWnd, TRUE);
  ShowWindow(hWnd, SW_SHOWNORMAL);
  DeleteDC(hDCprinter);

  return res;
}