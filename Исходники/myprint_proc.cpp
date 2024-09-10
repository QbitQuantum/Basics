LRESULT CALLBACK MyPrintProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
  switch(message){
  case WM_INITDIALOG:
    {
      hDialog = hDlg;

      SetDlgItemText(hDlg,IDC_PM_LEFT,"15");
      SetDlgItemText(hDlg,IDC_PM_RIGHT,"15");
      SetDlgItemText(hDlg,IDC_PM_TOP,"21");
      SetDlgItemText(hDlg,IDC_PM_BOTTOM,"21");
      SetDlgItemText(hDlg,IDC_BAIRITU,"100");
      HWND hOk = GetDlgItem(hDlg,IDOK);
      if(hPrintDC == NULL){
        EnableWindow(hOk,FALSE);
      }
      SendDlgItemMessage(hDlg,IDOK,WM_COMMAND,(WPARAM)(BN_DISABLE),(LPARAM)0);
      HWND hPreview = GetDlgItem(hDlg,IDC_PREVIEW);
      oldMyPrintPreviewProc = (WNDPROC)SetWindowLongPtr(hPreview,GWL_WNDPROC,(LONG)MyPrintPreviewProc);
      char printername[256];
      GetCurrentPrinterName(printername);
      SetDlgItemText(hDlg,IDC_SELECTEDPRINTER,printername);
    }
    break;
  case WM_VSCROLL:
    {
      int iId = LOWORD(wParam);

      int id = GetDlgCtrlID((HWND)lParam);

      HWND hChange = NULL;
      int maximum = -1;
      int minimum = -1;
      if(id == IDC_SCR_BAIRITU){
        hChange = GetDlgItem(hDlg,IDC_BAIRITU);
        minimum = 1;
      }else if(id == IDC_PM_SCR_LEFT){
        hChange = GetDlgItem(hDlg,IDC_PM_LEFT);
        minimum = 0;
      }else if(id == IDC_PM_SCR_RIGHT){
        hChange = GetDlgItem(hDlg,IDC_PM_RIGHT);
        minimum = 0;
      }else if(id == IDC_PM_SCR_TOP){
        hChange = GetDlgItem(hDlg,IDC_PM_TOP);
        minimum = 0;
      }else if(id == IDC_PM_SCR_BOTTOM){
        hChange = GetDlgItem(hDlg,IDC_PM_BOTTOM);
        minimum = 0;
      }
      if(hChange != NULL){
        DoWhenVscroll(hChange,iId,minimum,maximum);
      }
    }
    break;
  case WM_COMMAND:
    {
      int iEvent = HIWORD(wParam);
      int iId = LOWORD(wParam);
      switch(iId){
      case IDC_SETTOKYOUGI:
        {
          char buf[32];
          double bai = 74.0 / (double)currentdesign.height * 600.0;
          sprintf(buf,"%.4f",bai);
          SetDlgItemText(hDlg,IDC_BAIRITU,buf);
        }
        break;
      case IDC_PM_LEFT: case IDC_PM_RIGHT: case IDC_PM_TOP: case IDC_PM_BOTTOM:
      case IDC_BAIRITU:
        {
          if(iEvent == EN_CHANGE && hPrintDC != NULL){
            HWND h = GetDlgItem(hDlg,IDC_PREVIEW);
            InvalidateRect(h,NULL,FALSE);
            UpdateWindow(h);
            int pages = CountPages(hDlg,hPrintDC);
            char buf[16];
            wsprintf(buf,"%d",pages);
            SetDlgItemText(hDlg,IDC_PAGENUM,buf);
          }
        }
        break;
      case IDC_SELPRINTER:
        {
          SelPrinter(hDlg);

          HWND hPreview = GetDlgItem(hDlg,IDC_PREVIEW);
          InvalidateRect(hPreview,NULL,TRUE);
          UpdateWindow(hPreview);

          HWND hOk = GetDlgItem(hDlg,IDOK);
          if(hPrintDC != NULL){
            EnableWindow(hOk,TRUE);
            int pages = CountPages(hDlg,hPrintDC);
            char buf[16];
            wsprintf(buf,"%d",pages);
            SetDlgItemText(hDlg,IDC_PAGENUM,buf);
          }else{
            EnableWindow(hOk,FALSE);
          }
          char printername[256];
          GetCurrentPrinterName(printername);
          SetDlgItemText(hDlg,IDC_SELECTEDPRINTER,printername);
        }
        break;
      case IDOK:
        {
          if(hPrintDC == NULL){
            break;
          }
          char buf[512];
          char printername[256];
          GetCurrentPrinterName(printername);
          int pages = CountPages(hDlg,hPrintDC);
          int nCopies = GetCurrentPrinterCopies();
          wsprintf(buf,"プリンタ名: [ %s ]\r\n一部当たり [ %d ページ ] で\r\n全部で [ %d 部 ] 印刷します\r\nよろしいですか？",printername,pages,nCopies);
          if(MessageBox(hDlg,buf,"確認",MB_YESNO)==IDYES){

            ChangeDisplayColorToMax();
            DOCINFO di;
            ZeroMemory(&di,sizeof(DOCINFO));
            di.cbSize = sizeof(DOCINFO);
            di.lpszDocName = "KAZESOMISO";
            double dotpermm_x = GetDeviceCaps(hPrintDC,LOGPIXELSX) / 25.4;
            double dotpermm_y = GetDeviceCaps(hPrintDC,LOGPIXELSY) / 25.4;
            double bairitu = GetFudaBairitu(hDlg);

            fudascale_x = bairitu * dotpermm_x;
            fudascale_y = bairitu * dotpermm_y;

            if(!gdiplus_useable){
              fudascale = fudascale_y;
            }else{
              fudascale = bairitu;
            }
            LoadImageToDC(hPrintDC,currentdesign);

            fudaunit = Gdiplus::UnitMillimeter;

            StartDoc(hPrintDC,&di);
            int rows,cols,sukima_x,sukima_y;
            CountOnePageFudaNum(hDlg,hPrintDC,&cols,&rows);
            GetFudaSukima(hDlg,hPrintDC,&sukima_x,&sukima_y);
            int left,right,top,bottom;
            GetPrintMargin(hDlg,&left,&top,&right,&bottom);

            int maxfudanum = 0;
            if(tori_or_yomi == TORI){
              maxfudanum = torifuda.size();
            }else{
              maxfudanum = yomifuda.size();
            }
            int fudanum = 0;
            for(int p = 0; p < pages; p++){
              StartPage(hPrintDC);
              for(int i = cols -1 ; i >= 0; i --){
                for(int j = 0; j < rows; j ++){
                  for(; fudanum < maxfudanum; fudanum++){
                    if(tori_or_yomi == TORI && torifuda[fudanum].saveasimage ||
                       tori_or_yomi == YOMI && yomifuda[fudanum].saveasimage
                    ){
                      break;
                    }
                  }
                  if(fudanum >= maxfudanum){
                    break;
                  }
                  class ToriYomiDesign design;
                  if(tori_or_yomi == TORI){
                    design.simonoku = torifuda[fudanum].simonoku;
                    design.kimariji = torifuda[fudanum].kimariji;
                    design.tori = currentdesign.tori;
                  }else{
                    design.waka = yomifuda[fudanum].waka;
                    design.yomi = currentdesign.yomi;
                  }
                  design.UpdateSize();
                  double x,y;
                  if(!gdiplus_useable){
                    x = left / bairitu + i * ( design.width + sukima_x / (bairitu * dotpermm_x) );
                    y = top / bairitu + j * ( design.height + sukima_y / (bairitu * dotpermm_y));
                  }else{
                    x = left / fudascale+ i * ( design.width + sukima_x / (dotpermm_x*fudascale) );
                    y = top / fudascale + j * ( design.height + sukima_y / (dotpermm_y*fudascale));
                  }
                  MYRECT rect;
                  rect.left = x;
                  rect.top = y;
                  rect.right = -1;
                  rect.bottom = -1;
                  DrawFuda(design,hPrintDC,&rect);
                  fudanum++;
                }
              }
              EndPage(hPrintDC);
            }

            EndDoc(hPrintDC);

            fudaunit = Gdiplus::UnitDisplay;
            fudascale = -1.0;
            HDC hdc = GetDC(hWndMain);
            LoadImageToDC(hdc,currentdesign);
            ReleaseDC(hWndMain,hdc);

            MessageBox(hDlg,"プリンタに出力しました。","完了",MB_OK);
          }
        }
        break;
      case IDCANCEL:
        {
          EndDialog(hDlg,0);
        }
        break;
      }
    }
    break;
  }
  return FALSE;
}