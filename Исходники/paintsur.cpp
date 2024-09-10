void PaintSur::PolygonImage(const std::vector<RenderVertex> &rgv, HBITMAP hbm, const float left, const float top, const float right, const float bottom, const int bitmapwidth, const int bitmapheight)
{
   const int ix = SCALEXf(left);
   const int iy = SCALEYf(top);
   const int ix2 = SCALEXf(right);
   const int iy2 = SCALEYf(bottom);

   const HDC hdcNew = CreateCompatibleDC(m_hdc);
   const HBITMAP hbmOld = (HBITMAP)SelectObject(hdcNew, hbm);

   std::vector<POINT> rgpt(rgv.size());
   for (size_t i = 0; i < rgv.size(); i++)
   {
      rgpt[i].x = SCALEXf(rgv[i].x);
      rgpt[i].y = SCALEYf(rgv[i].y);
   }

   if (GetWinVersion() >= 2600) // For everything newer than Windows XP: use the alpha in the bitmap (RGB needs to be premultiplied with alpha, too, then! see CopyTo_ConvertAlpha())
   {
      const HRGN hrgn = CreatePolygonRgn(rgpt.data(), (int)rgv.size(), WINDING);
      SelectClipRgn(m_hdc, hrgn);

      const BLENDFUNCTION blendf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
      AlphaBlend(m_hdc, ix, iy, ix2 - ix, iy2 - iy, hdcNew, 0, 0, bitmapwidth, bitmapheight, blendf);

      SelectClipRgn(m_hdc, NULL);
      DeleteObject(hrgn);
   }
   else // do XOR trick for masking (draw image, draw black polygon, draw image again, and the XOR will do an implicit mask op)
   {
      SetStretchBltMode(m_hdc, HALFTONE); // somehow enables filtering
      StretchBlt(m_hdc, ix, iy, ix2 - ix, iy2 - iy, hdcNew, 0, 0, bitmapwidth, bitmapheight, SRCINVERT);

      SelectObject(m_hdc, GetStockObject(BLACK_BRUSH));
      SelectObject(m_hdc, GetStockObject(NULL_PEN));

      ::Polygon(m_hdc, rgpt.data(), (int)rgv.size());

      SetStretchBltMode(m_hdc, HALFTONE); // somehow enables filtering
      StretchBlt(m_hdc, ix, iy, ix2 - ix, iy2 - iy, hdcNew, 0, 0, bitmapwidth, bitmapheight, SRCINVERT);
   }

   SelectObject(hdcNew, hbmOld);
   DeleteDC(hdcNew);
}