void CLogiTextGate::Draw(CDC* pDC, CLogiView* pView)
   {
   ASSERT_VALID(this);

   // Draw the Bitmap Portion

   if (m_iStyle == 1)
      {
      CRect crBackup = m_position;
      CSize csBackup = m_size;

      m_position = CRect(m_position.TopLeft(), CSize(BITX_TXT, -BITY_TXT));
      m_size = CSize(BITX_TXT, BITY_TXT);

      CLogiGate::Draw(pDC, pView);

      m_position = crBackup;
      m_size     = csBackup;
      }

   // if printing build a bitmap on the fly for the Text.

   if (pDC->IsPrinting() || m_pDocument->m_iZoom)
      {
      CDC MemDC;

      MemDC.CreateCompatibleDC(NULL);

      pOldFont = MemDC.SelectObject(&m_pDocument->m_cfScreen);
      pOldPen = MemDC.SelectObject(&m_pDocument->m_cpBlack);
      pOldBrush = MemDC.SelectObject(&m_pDocument->m_cbWhite);
      int oldBkMode = MemDC.SetBkMode(TRANSPARENT);
      COLORREF oldTextColor = MemDC.SetTextColor(RGB(0, 0, 0));

      // calculate the surrounding rectangle of the text only

      CSize csExtent;

      if (m_bLoaded)
         {
         csExtent = MemDC.GetTextExtent( m_pTextArray[m_uIndex], m_pTextArray[m_uIndex].GetLength() ) + CSize(4,4);
         }
      else
         {
         csExtent = MemDC.GetTextExtent( m_pTextText, m_pTextText.GetLength() ) + CSize(4,4);
         }

      MemDC.GetTextMetrics(&tm);
      if (tm.tmItalic) csExtent += CSize(tm.tmHeight/4,0);

      // crate a temperary bitmap to draw the text to (can't be MemDC?)

      CBitmap cbGate;

      CDC screenDC;
      screenDC.CreateDC(L"DISPLAY", NULL, NULL, NULL);
      cbGate.CreateCompatibleBitmap(&screenDC, csExtent.cx, csExtent.cy);
      screenDC.DeleteDC();

      pOldBmp = MemDC.SelectObject(&cbGate);

      // draw rectangle also inits bitmap with brush

      MemDC.Rectangle(CRect(CPoint(0,0),csExtent));

      // draw text

      if (m_bLoaded)
         {
         MemDC.TextOut(2, 2, m_pTextArray[m_uIndex], m_pTextArray[m_uIndex].GetLength());
         }
      else
         {
         MemDC.TextOut(2, 2, m_pTextText, m_pTextText.GetLength());
         }

      MemDC.SelectObject(pOldPen);
      MemDC.SelectObject(pOldBrush);
      MemDC.SetTextColor(oldTextColor);
      MemDC.SetBkMode(oldBkMode);
      MemDC.SelectObject(pOldFont);
      MemDC.SelectObject(pOldBmp);

      // build a DIB from the bitmap

      m_Bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      m_Bmi.bmiHeader.biHeight = csExtent.cy;
      m_Bmi.bmiHeader.biWidth = csExtent.cx;
      m_Bmi.bmiHeader.biPlanes = 1;
      m_Bmi.bmiHeader.biBitCount = 4;
      m_Bmi.bmiHeader.biCompression = BI_RGB;
      m_Bmi.bmiHeader.biSizeImage = 0;
      m_Bmi.bmiHeader.biXPelsPerMeter = 0;
      m_Bmi.bmiHeader.biYPelsPerMeter = 0;
      m_Bmi.bmiHeader.biClrUsed = 16;
      m_Bmi.bmiHeader.biClrImportant = 16;

      if(!::GetDIBits(MemDC.GetSafeHdc(), (HBITMAP) cbGate.m_hObject, 0, (UINT) m_Bmi.bmiHeader.biHeight, NULL, (LPBITMAPINFO) &m_Bmi, DIB_RGB_COLORS)) return;

      if (m_Bmi.bmiHeader.biSizeImage == 0) return;

      LPBYTE lpImage = (LPBYTE) new char[m_Bmi.bmiHeader.biSizeImage];
      ::GetDIBits(MemDC.GetSafeHdc(), (HBITMAP) cbGate.m_hObject, 0, (UINT) m_Bmi.bmiHeader.biHeight, lpImage, (LPBITMAPINFO) &m_Bmi, DIB_RGB_COLORS);

      MemDC.DeleteDC();

      // determine where to draw the dib

      CPoint origin;

      if (m_iStyle == 1)
         {
         origin = CPoint(m_position.left+(BITX_TXT-1), m_position.top-csExtent.cy);
         }
      else
         {
         origin = CPoint(m_position.left, m_position.bottom);
         }

      // draw it

      ::StretchDIBits(pDC->GetSafeHdc(), origin.x, origin.y, csExtent.cx, csExtent.cy, 0, 0, m_Bmi.bmiHeader.biWidth, m_Bmi.bmiHeader.biHeight, lpImage, (LPBITMAPINFO) &m_Bmi, DIB_RGB_COLORS, SRCCOPY);

      delete [] lpImage;
      }

   // Else not printing do direct

   else
      {
      pOldPen = pDC->SelectObject(&m_pDocument->m_cpBlack);
      pOldFont = pDC->SelectObject(&m_pDocument->m_cfScreen);
      pOldBrush = pDC->SelectObject(&m_pDocument->m_cbWhite);
      int oldBkMode = pDC->SetBkMode(TRANSPARENT);
      COLORREF oldTextColor = pDC->SetTextColor(RGB(0, 0, 0));

      // calculate the surrounding rectangle of text only

      CSize csExtent;

      if (m_bLoaded)
         {
         csExtent = pDC->GetTextExtent(m_pTextArray[m_uIndex], m_pTextArray[m_uIndex].GetLength() ) + CSize(4,4);
         }
      else
         {
         csExtent = pDC->GetTextExtent(m_pTextText, m_pTextText.GetLength() ) + CSize(4,4);
         }

      pDC->GetTextMetrics(&tm);
      if (tm.tmItalic) csExtent += CSize(tm.tmHeight/4,0);

      // determine where to draw things

      CPoint origin;

      if (m_iStyle == 1)
         {
         origin = CPoint(m_position.left+(BITX_TXT-1), m_position.top-csExtent.cy);
         }
      else
         {
         origin = CPoint(m_position.left, m_position.bottom);
         }

      pDC->Rectangle(CRect(origin,csExtent));

      if (m_bLoaded)
         {
         pDC->TextOut(origin.x+2, origin.y+2, m_pTextArray[m_uIndex], m_pTextArray[m_uIndex].GetLength());
         }
      else
         {
         pDC->TextOut(origin.x+2, origin.y+2, m_pTextText, m_pTextText.GetLength());
         }

      pDC->SelectObject(pOldFont);
      pDC->SelectObject(pOldPen);
      pDC->SetTextColor(oldTextColor);
      pDC->SelectObject(pOldBrush);
      pDC->SetBkMode(oldBkMode);
      }
   }