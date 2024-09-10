/*********************************************************************
*
*       GUIDEMO_Speed
*/
void GUIDEMO_Speed(void) {
  int      TimeStart, i;
  U32      PixelsPerSecond;
  unsigned aColorIndex[8];
  int      xSize, ySize, vySize;
  GUI_RECT Rect, ClipRect;
  char     cText[40] = { 0 };

  xSize  = LCD_GetXSize();
  ySize  = LCD_GetYSize();
  vySize = LCD_GetVYSize();
#if GUI_SUPPORT_CURSOR
  GUI_CURSOR_Hide();
#endif
  if (vySize > ySize) {
    ClipRect.x0 = 0;
    ClipRect.y0 = 0;
    ClipRect.x1 = xSize;
    ClipRect.y1 = ySize;
    GUI_SetClipRect(&ClipRect);
  }
  GUIDEMO_ShowIntro("High speed",
                    "Multi layer clipping\n"
                    "Highly optimized drivers");
  for (i = 0; i< 8; i++) {
    aColorIndex[i] = GUI_Color2Index(_aColor[i]);
  }  
  TimeStart = GUIDEMO_GetTime();
  for (i = 0; ((GUIDEMO_GetTime() - TimeStart) < 5000) && (GUIDEMO_CheckCancel() == 0); i++) {
    GUI_SetColorIndex(aColorIndex[i&7]);
    //
    // Calculate random positions
    //
    Rect.x0 = rand() % xSize - xSize / 2;
    Rect.y0 = rand() % ySize - ySize / 2;
    Rect.x1 = Rect.x0 + 20 + rand() % xSize;
    Rect.y1 = Rect.y0 + 20 + rand() % ySize;
    GUI_FillRect(Rect.x0, Rect.y0, Rect.x1, Rect.y1);
    //
    // Clip rectangle to visible area and add the number of pixels (for speed computation)
    //
    if (Rect.x1 >= xSize) {
      Rect.x1 = xSize - 1;
    }
    if (Rect.y1 >= ySize) {
      Rect.y1 = ySize - 1;
    }
    if (Rect.x0 < 0 ) {
      Rect.x0 = 0;
    }
    if (Rect.y1 < 0) {
      Rect.y1 = 0;
    }
    GUI_Exec();
    //
    // Allow short breaks so we do not use all available CPU time ...
    //
  }
  GUIDEMO_NotifyStartNext();
  PixelsPerSecond = _GetPixelsPerSecond();
  GUI_SetClipRect(NULL);
  GUIDEMO_DrawBk(0);
  GUI_SetColor(GUI_WHITE);
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_SetFont(&GUI_FontRounded22);
  GUI_DrawBitmap(&bmSTLogo70x35, 5, 5);
  GUIDEMO_AddStringToString(cText, "Pixels/sec: ");
  GUIDEMO_AddIntToString(cText, PixelsPerSecond);
  GUI_DispStringHCenterAt(cText, xSize >> 1, (ySize - GUI_GetFontSizeY()) >> 1);
  GUIDEMO_Delay(4000);
#if GUI_SUPPORT_CURSOR
  GUI_CURSOR_Show();
#endif
}