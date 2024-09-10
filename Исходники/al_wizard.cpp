void WIZARD::SetGraphic (int idbGraphic16, int idbGraphic256)
{
   LPRGBQUAD pargb = NULL;
   RGBQUAD argb[256];

   m_idbGraphic16 = idbGraphic16;
   m_idbGraphic256 = idbGraphic256;

   if (m_bmpGraphic16 != NULL)
      {
      DeleteObject (m_bmpGraphic16);
      m_bmpGraphic16 = NULL;
      }

   if (m_bmpGraphic256 != NULL)
      {
      DeleteObject (m_bmpGraphic256);
      m_bmpGraphic256 = NULL;
      }

   if (m_palGraphic != NULL)
      {
      DeleteObject (m_palGraphic);
      m_palGraphic = NULL;
      }

   m_bmpGraphic16 = (HBITMAP)TaLocale_LoadImage (idbGraphic16, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

   if ((m_bmpGraphic256 = (HBITMAP)TaLocale_LoadImage (idbGraphic256, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION)) != NULL)
      {
      BITMAP bm;
      GetObject (m_bmpGraphic256, sizeof(BITMAP), &bm);

      if ((bm.bmBitsPixel * bm.bmPlanes) == 8)
         {
         HDC hdc = CreateCompatibleDC (NULL);
         HBITMAP bmpOld = (HBITMAP)SelectObject (hdc, m_bmpGraphic256);

         GetDIBColorTable (hdc, 0, 256, argb);
         pargb = argb;

         SelectObject (hdc, bmpOld);
         DeleteDC (hdc);
         }
      }

   GeneratePalette (pargb);

   if (m_fShowing)
      {
      Refresh (REFRESH_LEFT_PANE);
      }
}