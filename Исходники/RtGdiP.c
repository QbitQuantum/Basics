RT_B RT_API RtGdipStretchBitmap(RT_H hBitmap, RT_H hDc, RT_N nWidth, RT_N nHeight, RT_GDIP_INTERPOLATION_MODE nInterpolationMode)
{
  GpGraphics* lpGraphics;
  GpBitmap* lpBitmap;
  GpBrush* lpBrush;
  GpStatus nStatus;
  RT_B bResult;

  lpGraphics = RT_NULL;
  lpBitmap = RT_NULL;
  lpBrush = RT_NULL;

  /* Create destination graphics hDc. */
  nStatus = GdipCreateFromHDC(hDc, &lpGraphics);
  if (nStatus)
  {
    RtGdipSetLastErrorFromGpStatus(nStatus);
    goto handle_error;
  }

  /* Adjust quality. */
  nStatus = GdipSetInterpolationMode(lpGraphics, (InterpolationMode)nInterpolationMode);
  if (nStatus)
  {
    RtGdipSetLastErrorFromGpStatus(nStatus);
    goto handle_error;
  }

  /* Create a brush to fill the background. */
  nStatus = GdipCreateSolidFill(0xFFFFFFFF, &lpBrush);
  if (nStatus)
  {
    RtGdipSetLastErrorFromGpStatus(nStatus);
    goto handle_error;
  }

  /* Fill the destination DC with a background. Necessary to avoid edges artifacts. */
  nStatus = GdipFillRectangleI(lpGraphics, lpBrush, 0, 0, nWidth, nHeight);
  if (nStatus)
  {
    RtGdipSetLastErrorFromGpStatus(nStatus);
    goto handle_error;
  }

  /* Create source image/bitmap from hBitmap. */
  nStatus = GdipCreateBitmapFromHBITMAP(hBitmap, RT_NULL, &lpBitmap);
  if (nStatus)
  {
    RtGdipSetLastErrorFromGpStatus(nStatus);
    goto handle_error;
  }

  /* Stretch. */
  nStatus = GdipDrawImageRectI(lpGraphics, lpBitmap, 0, 0, nWidth, nHeight);
  if (nStatus)
  {
    RtGdipSetLastErrorFromGpStatus(nStatus);
    goto handle_error;
  }

  bResult = RT_TRUE;
  goto free_resources;
handle_error:
  bResult = RT_FALSE;
free_resources:
  if (lpGraphics)
  {
    nStatus = GdipDeleteGraphics(lpGraphics);
    lpGraphics = RT_NULL;
    if (nStatus && bResult)
    {
      RtGdipSetLastErrorFromGpStatus(nStatus);
      goto handle_error;
    }
  }
  if (lpBitmap)
  {
    nStatus = GdipDisposeImage(lpBitmap);
    lpBitmap = RT_NULL;
    if (nStatus && bResult)
    {
      RtGdipSetLastErrorFromGpStatus(nStatus);
      goto handle_error;
    }
  }
  if (lpBrush)
  {
    nStatus = GdipDeleteBrush(lpBrush);
    lpBrush = RT_NULL;
    if (nStatus && bResult)
    {
      RtGdipSetLastErrorFromGpStatus(nStatus);
      goto handle_error;
    }
  }
  return bResult;
}