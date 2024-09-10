COLORREF CAnimationSpooler::TranslateColor(LPDIRECT3DSURFACE9 pSurface, COLORREF clrColor) const
{
   ASSERT(pSurface);
   if( clrColor == CLR_INVALID ) return clrColor;
   // The only way to actually determine what color a certain RGB value gets, is
   // to put a pixel on the surface and taste it.
   HDC hDC = NULL;
   HRESULT Hr = pSurface->GetDC(&hDC);
   if( FAILED(Hr) ) return false;
   COLORREF clrOld = ::GetPixel(hDC, 0, 0);
   ::SetPixel(hDC, 0, 0, clrColor);
   clrColor = ::GetPixel(hDC, 0,0);
   ::SetPixel(hDC, 0, 0, clrOld);
   pSurface->ReleaseDC(hDC);
   return clrColor;
}