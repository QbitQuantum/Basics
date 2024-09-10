static void OnMultiSelectListPaintListItem(WindowControl * Sender, LKSurface& Surface) {

#define PICTO_WIDTH 50

  Surface.SetTextColor(RGB_BLACK);
  if (TaskDrawListIndex < iNO_Tasks)  {
      TCHAR *pToken = NULL;
      TCHAR *pWClast = NULL;
      TCHAR *pWClast2 = NULL;
      TCHAR text[180] = {TEXT("empty")};
      TCHAR text1[180] = {TEXT("empty")};
      TCHAR text2[180] = {TEXT("empty")};

      _tcscpy(text, szTaskStrings [TaskDrawListIndex] );
    unsigned int i=0;
    while (i < _tcslen(text) )  // remove all quotations "
    {
        if(text[i]== '"')    //  quotations found ?
        {
            for (unsigned int j= i ; j < _tcslen(text); j++)
            text[j] =  text[j+1];
        }
        i++;
    }
    pToken = strsep_r(text, TEXT(","), &pWClast) ;
    _tcscpy(text1, pToken );
    if(*text1 == '\0')   _tcscpy(text1, _T("???") );

    pToken = strsep_r(pWClast, TEXT(","), &pWClast2) ;  // remove takeof point
    _tcscpy(text2, pWClast2);

      Surface.SetBkColor(LKColor(0xFF, 0xFF, 0xFF));


      PixelRect rc = {
          0,
          0,
          0, // DLGSCALE(PICTO_WIDTH),
          static_cast<PixelScalar>(Sender->GetHeight())
      };

      /********************
       * show text
       ********************/
      Surface.SetBackgroundTransparent();
      Surface.SetTextColor(RGB_BLACK);
      Surface.DrawText(rc.right + DLGSCALE(2), DLGSCALE(2), text1);
      int ytext2 = Surface.GetTextHeight(text1);
      Surface.SetTextColor(RGB_DARKBLUE);
      Surface.DrawText(rc.right + DLGSCALE(2), ytext2, text2);
  }
}