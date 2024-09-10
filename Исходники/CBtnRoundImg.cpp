void CBtnRoundImg::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
   CDC dc;
   dc.Attach(lpDrawItemStruct->hDC);       //°´Å¥¿Ø¼þDC  

   COLORREF clrBK = RGB(255,255,255);
   switch(m_nCtrlState)  
   {  
   case CTRL_NOFOCUS:  
      clrBK = m_clrBKUnfocus;
      break;  
   case CTRL_FOCUS:  
      clrBK = m_clrBKFocus;
      break;  
   case CTRL_SELECTED:  
      clrBK = m_clrBKSelected;
      break;  
   default:  
      break;  
   }  

   if (IsWindowEnabled()==FALSE)
   {
      clrBK = m_clrBKDisable;
   }

   //draw background
   CRect rect(lpDrawItemStruct->rcItem);
   //dc.FillSolidRect(&rect,clrBK);
   DrawRoundRect(dc, 5,rect,clrBK);

   //draw image
   if (m_strPngPath != _T(""))
   {
      Gdiplus::Image  imageBtn(m_strPngPath);
      if (imageBtn.GetLastStatus() != Ok)
      {
         ASSERT(FALSE);
      }
      ;
      HRGN hRgnOld = (HRGN)::SelectObject(lpDrawItemStruct->hDC, m_hRgnBtn);

      Gdiplus::Graphics * pGrp = Graphics::FromHDC(lpDrawItemStruct->hDC);
      pGrp->Clear(Color::White);

      CRect rectBtn;
      GetClientRect(&rectBtn);
      int startX = (rectBtn.Width() - imageBtn.GetWidth())/2;
      int startY = (rectBtn.Height() - imageBtn.GetHeight())/2;
      startX = 0;
      startY = 0;
      if (lpDrawItemStruct->itemState & ODS_SELECTED)	//Ñ¡ÖÐ×´Ì¬£¬Í¼Æ¬Æ«ÒÆÒ»¸öÏñËØ
      {
         pGrp->DrawImage(&imageBtn, startX+1, startY+1, startX+imageBtn.GetWidth(), startY+imageBtn.GetHeight());
      }
      else	//Ä¬ÈÏ×´Ì¬
      {
         pGrp->DrawImage(&imageBtn, startX, startY, startX+imageBtn.GetWidth(), startY+imageBtn.GetHeight());
      }

      delete pGrp;
      pGrp = NULL;
      ::SelectObject(lpDrawItemStruct->hDC, hRgnOld);
   }


   CFont* pOldFont;
   if (m_pFont)
   {
      pOldFont = dc.SelectObject(m_pFont); 
   }
   COLORREF clrOld = dc.SetTextColor(m_clrFont);
   CString strText;
   GetWindowText(strText);
   if (strText != _T(""))
   {
      int test = 1;
   }
   int oldMode = dc.SetBkMode(TRANSPARENT);
   dc.DrawText(strText, -1, &lpDrawItemStruct->rcItem, DT_CENTER|DT_SINGLELINE|DT_VCENTER);  
   dc.SetBkMode(oldMode);
   dc.SetTextColor(clrOld);
   if (m_pFont)
   {
      dc.SelectObject(pOldFont);  
   }

   dc.Detach();
}