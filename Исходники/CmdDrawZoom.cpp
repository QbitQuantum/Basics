DWORD CmdDrawZoom::CmdDrawAjustZooming::SetPoint(DWORD MouseAction, CPoint pt)
{
   CmdDrawZoom *p = dynamic_cast<CmdDrawZoom*>(m_pOwner);
   if (enCmdMouseNone == MouseAction)
   {
      LP_MATERIALINFO pTempInfo = p->m_pReceiver->getComicStripData()->getSelectedInfo();
      if (NULL == pTempInfo)
      {
         return FALSE;
      }
      CSize size = CSize(pt.x - pTempInfo->GetLTPoint().x, pt.y - pTempInfo->GetLTPoint().y);
      size.cx = max(size.cx, 24);
      size.cy = max(size.cy, 24);

      pTempInfo->SetFinalSize(size);
      if (pTempInfo->isPenDraw) {
         int width = pTempInfo->m_image.GetWidth();
         int height = pTempInfo->m_image.GetHeight();
         if (width<size.cx || height<size.cy)
         {
            int newWidth = max(width, size.cx);
            int newHeight = max(height, size.cy);
            CxImage tempImage = pTempInfo->m_image;
            pTempInfo->m_image.Create(newWidth, newHeight, 24, CXIMAGE_FORMAT_PNG);
            RGBQUAD rgb = pTempInfo->m_image.GetPixelColor(1,1);
            pTempInfo->m_image.SetTransIndex(0);
            pTempInfo->m_image.SetTransColor(rgb);

            HDC     memdcOrg   = CreateCompatibleDC(NULL);
            HBITMAP hbitmapOrg = tempImage.MakeBitmap();
            HGDIOBJ pOldGDIOBJOrg = SelectObject(memdcOrg, hbitmapOrg);

            HDC     memdc   = CreateCompatibleDC(NULL);
            HBITMAP hbitmap = pTempInfo->m_image.MakeBitmap();
            HGDIOBJ pOldGDIOBJ = SelectObject(memdc, hbitmap);
            BitBlt(memdc, 0, 0, width, height, memdcOrg, 0, 0, SRCCOPY);
            pTempInfo->m_image.CreateFromHBITMAP(hbitmap);

            SelectObject(memdc, pOldGDIOBJ);
            DeleteObject(hbitmap);
            DeleteDC(memdc);

            SelectObject(memdcOrg, pOldGDIOBJOrg);
            DeleteObject(hbitmapOrg);
            DeleteDC(memdcOrg);
         }
      }
      p->m_pReceiver->UpdateComicStrip(pTempInfo->nIDOwner);
   }
   else if (enCmdMouseLUp == MouseAction)
   {
      LP_MATERIALINFO pTempInfo = p->m_pReceiver->getComicStripData()->getSelectedInfo();
      if (NULL == pTempInfo)
      {
         return FALSE;
      }
      CSize size = CSize(pt.x - pTempInfo->GetLTPoint().x, pt.y - pTempInfo->GetLTPoint().y);
      size.cx = max(size.cx, 24);
      size.cy = max(size.cy, 24);

      pTempInfo->SetFinalSize(size);
      if (pTempInfo->isPenDraw) {
         int width = pTempInfo->m_image.GetWidth();
         int height = pTempInfo->m_image.GetHeight();
         if (width<size.cx || height<size.cy)
         {
            CxImage tempImage = pTempInfo->m_image;
            pTempInfo->m_image.Create(size.cx, size.cy, 24, CXIMAGE_FORMAT_PNG);
            RGBQUAD rgb = pTempInfo->m_image.GetPixelColor(1,1);
            pTempInfo->m_image.SetTransIndex(0);
            pTempInfo->m_image.SetTransColor(rgb);

            HDC     memdcOrg   = CreateCompatibleDC(NULL);
            HBITMAP hbitmapOrg = tempImage.MakeBitmap();
            HGDIOBJ pOldGDIOBJOrg = SelectObject(memdcOrg, hbitmapOrg);

            HDC     memdc   = CreateCompatibleDC(NULL);
            HBITMAP hbitmap = pTempInfo->m_image.MakeBitmap();
            HGDIOBJ pOldGDIOBJ = SelectObject(memdc, hbitmap);
            BitBlt(memdc, 0, 0, width, height, memdcOrg, 0, 0, SRCCOPY);
            pTempInfo->m_image.CreateFromHBITMAP(hbitmap);
            
            SelectObject(memdc, pOldGDIOBJ);
            DeleteObject(hbitmap);
            DeleteDC(memdc);

            SelectObject(memdcOrg, pOldGDIOBJOrg);
            DeleteObject(hbitmapOrg);
            DeleteDC(memdcOrg);
         }
      }
      p->m_pReceiver->SaveFile();
      p->m_pReceiver->UpdateComicStrip(pTempInfo->nIDOwner);
      p->m_pDsState = &p->m_dsZoomBgn;
      p->m_pReceiver->SetCursor();
      p->m_nDrawState = enDrawIdle;
   }
   return TRUE;
}