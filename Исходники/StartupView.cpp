void CStartupView::RepositionButtons()
{
   int x;
   int y;
   int width;
   int height;

   Gdiplus::Rect gdipRcLogoRegion;
   Gdiplus::Rect gdipRcButtonRegion;
   Gdiplus::Rect gdipRcBottomRegion;
   CalculateRegions(gdipRcLogoRegion, gdipRcButtonRegion, gdipRcBottomRegion);

   width = BUTTON_WIDTH;
   height = BUTTON_HEIGHT1;


   // Close button
   CRect rcButton;
   rcButton.SetRect(gdipRcLogoRegion.Width - 19 , 
      OFFSET_Y, 
      gdipRcLogoRegion.Width - 7 , 
      13 + OFFSET_Y );
   m_btnClose.SetWindowPos(NULL, rcButton.left- GetScrollPos(SB_HORZ), rcButton.top- GetScrollPos(SB_VERT), 
      rcButton.Width(), rcButton.Height(), SWP_NOZORDER);
   m_btnClose.SetTextAndImagePos(CPoint(1,1), CPoint(16, 16));

   // Other buttons

   // Left buttons
   Gdiplus::Rect gdipRcLeftButtons;
   CalculateLeftButtonsRegion(gdipRcLeftButtons);

   x = gdipRcLeftButtons.X;

   y = gdipRcLeftButtons.Y + BUTTON_TITLE_HEIGHT + BUTTON_SUBTITLE_HEIGHT + BUTTON_TOP_SPACE ;
   m_btnRecordPowerPoint.SetWindowPos(NULL, x- GetScrollPos(SB_HORZ), y- GetScrollPos(SB_VERT), width, height, SWP_NOZORDER);
   m_btnRecordPowerPoint.SetTextAndImagePos(CPoint(ICON_X_POS - 1, ICON_Y_POS + 1), CPoint(TEXT_X_POS + 8, TEXT_Y_POS + 7));
 
   y += BUTTON_HEIGHT1+10 ;

   m_btnRecordOther.SetWindowPos(NULL, x- GetScrollPos(SB_HORZ), y- GetScrollPos(SB_VERT), width, height, SWP_NOZORDER);
   m_btnRecordOther.SetTextAndImagePos(CPoint(ICON_X_POS - 1, ICON_Y_POS + 1), CPoint(TEXT_X_POS + 8, TEXT_Y_POS + 7));
   y += BUTTON_HEIGHT1+10 ;

   //y += SEPARATOR_HEIGHT;

   y += BUTTON_HEIGHT1+3 ;//+ BUTTON_TITLE_HEIGHT;

   m_btnNewSourceDoc.SetWindowPos(NULL, x- GetScrollPos(SB_HORZ), y - GetScrollPos(SB_VERT), width, height, SWP_NOZORDER);
   m_btnNewSourceDoc.SetTextAndImagePos(CPoint(ICON_X_POS - 1, ICON_Y_POS + 1), CPoint(TEXT_X_POS + 10, TEXT_Y_POS + 7));
   y += BUTTON_HEIGHT1+10;

   

   m_btnImportPowerPoint.SetWindowPos(NULL, x - GetScrollPos(SB_HORZ), y- GetScrollPos(SB_VERT), width, height, SWP_NOZORDER);
   m_btnImportPowerPoint.SetTextAndImagePos(CPoint(ICON_X_POS - 1, ICON_Y_POS + 1), CPoint(TEXT_X_POS + 10, TEXT_Y_POS + 7));

   // Right buttons
   Gdiplus::Rect gdipRcRightButtons;
   CalculateRightButtonsRegion(gdipRcRightButtons);

   

   x = gdipRcRightButtons.X ;
   y = gdipRcRightButtons.Y + 2 * BUTTON_TITLE_HEIGHT + BUTTON_HEIGHT ;
   //height = BUTTON_HEIGHT;
   m_btnOpenSourceDoc.SetWindowPos(NULL, x- GetScrollPos(SB_HORZ), y- GetScrollPos(SB_VERT), width, height, SWP_NOZORDER);
   m_btnOpenSourceDoc.SetTextAndImagePos(CPoint(ICON_X_POS - 1, ICON_Y_POS - 1), CPoint(TEXT_X_POS + 10, TEXT_Y_POS + 7));
   
   y += 3*BUTTON_HEIGHT+3;
   /*for (int i = 0; i < m_arBtnRecentFiles.GetSize(); ++i)
   {
      y = gdipRcRightButtons.Y + BUTTON_TITLE_HEIGHT + i*(BUTTON_HEIGHT+5);
      m_arBtnRecentFiles[i]->SetWindowPos(NULL, x, y, width, height, SWP_NOZORDER);
      m_arBtnRecentFiles[i]->SetTextAndImagePos(CPoint(ICON_X_POS, ICON_Y_POS), CPoint(TEXT_X_POS, TEXT_Y_POS));
   }*/

   CSize siTotal = GetTotalSize();
   CRect rcClient(0, 0, siTotal.cx, siTotal.cy);  
   //Button Tutorial
   x = rcClient.left + 40 ;//gdipRcBottomRegion.X + 40;
   y = rcClient.bottom - FOOT_HEIGHT - LIGHT_BLUE_HEIGHT ;/*gdipRcBottomRegion.Y + 
      (gdipRcBottomRegion.Height - rcBtnShowAgain.Height()) / 2.0;*/
   m_btnTutorial.SetWindowPos(NULL, x- GetScrollPos(SB_HORZ), y- GetScrollPos(SB_VERT), BUTTON_WIDTH1, BUTTON_HEIGHT1, SWP_NOZORDER);
   m_btnTutorial.SetTextAndImagePos(CPoint(ICON_X_POS - 1, ICON_Y_POS + 1), CPoint(TEXT_X_POS + 10, TEXT_Y_POS + 9));

   //Button Guided Tour
   x = (rcClient.left + rcClient.Width() - BUTTON_WIDTH1) / 2;//gdipRcBottomRegion.X + 40;
   y = rcClient.bottom - FOOT_HEIGHT - LIGHT_BLUE_HEIGHT ;/*gdipRcBottomRegion.Y + 
      (gdipRcBottomRegion.Height - rcBtnShowAgain.Height()) / 2.0;*/
   m_btnGuidedTour.SetWindowPos(NULL, x - GetScrollPos(SB_HORZ), y- GetScrollPos(SB_VERT), BUTTON_WIDTH1, BUTTON_HEIGHT1, SWP_NOZORDER);
   m_btnGuidedTour.SetTextAndImagePos(CPoint(ICON_X_POS - 1, ICON_Y_POS + 1), CPoint(TEXT_X_POS + 10, TEXT_Y_POS + 9));

   //Button Community
   x = rcClient.right - 40 - 13 - BUTTON_WIDTH1;//gdipRcBottomRegion.X + 40;
   y = rcClient.bottom - FOOT_HEIGHT - LIGHT_BLUE_HEIGHT ;/*gdipRcBottomRegion.Y + 
      (gdipRcBottomRegion.Height - rcBtnShowAgain.Height()) / 2.0;*/
   m_btnCommunity.SetWindowPos(NULL, x- GetScrollPos(SB_HORZ), y- GetScrollPos(SB_VERT), BUTTON_WIDTH1, BUTTON_HEIGHT1, SWP_NOZORDER);
   m_btnCommunity.SetTextAndImagePos(CPoint(ICON_X_POS - 1, ICON_Y_POS + 1), CPoint(TEXT_X_POS + 10, TEXT_Y_POS + 9));
  
   if (m_btnBuyNow.m_hWnd != NULL) {
       // //Button Buy Now
       x = rcClient.left + m_pLecturnityLogo->GetWidth() + 10 ;//gdipRcBottomRegion.X + 40;
       y = rcClient.top + OFFSET_Y + 4 ;/*gdipRcBottomRegion.Y + 
                                        (gdipRcBottomRegion.Height - rcBtnShowAgain.Height()) / 2.0;*/
       m_btnBuyNow.SetWindowPos(NULL, x- GetScrollPos(SB_HORZ), y- GetScrollPos(SB_VERT), 120, 56, SWP_NOZORDER);
       m_btnBuyNow.SetTextAndImagePos(CPoint( 1, 1), CPoint(56, TEXT_Y_POS + 17));
   }
   
   // Place checkbox 40 pixel from right border (horizontally)
   // in the middle of the bottom region (vertically)
   CRect rcBtnShowAgain;
   m_btnShowAgain.GetClientRect(rcBtnShowAgain);
   
   
   //CRect rcClient(0, 0, siTotal.cx, siTotal.cy);   
   x = rcClient.left + 40 ;//gdipRcBottomRegion.X + 40;
   y = rcClient.bottom - FOOT_HEIGHT;/*gdipRcBottomRegion.Y + 
      (gdipRcBottomRegion.Height - rcBtnShowAgain.Height()) / 2.0;*/
   m_btnShowAgain.SetWindowPos(NULL, x- GetScrollPos(SB_HORZ), y - GetScrollPos(SB_VERT), 250, BUTTON_HEIGHT, SWP_NOZORDER);
   m_btnShowAgain.SetTextAlignment(SS_LEFT);
}