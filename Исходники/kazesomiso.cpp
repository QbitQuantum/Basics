LRESULT CALLBACK VersionProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_INITDIALOG:
    {
      HWND h = GetDlgItem(hDlg,IDC_DEVICEINFO);
      std::string buf;
      buf += "* * * * * * * *\r\n";
      buf += "* ディスプレイ情報\r\n";
      buf += "* * * * * * * *\r\n";
      buf += GetMaxMinDisplayColors(NULL,NULL);
      buf += "---\r\n";
      if(gdiplus_useable){
        HMODULE hmd = GetModuleHandle("gdiplus.dll");
        char b[MAX_PATH] = "";
        GetModuleFileName(hmd,b,sizeof(b)-1);
        buf += "GDI+: 使用可->\"";
        buf += b;
        buf += "\"\r\n";
      }else{
        buf += "GDI+: 使用不可->gdiplus.dllが見つからない\r\n";
      }
      buf += "---\r\n";
      DWORD r;
      const int dcnum1[]     = { RASTERCAPS , CURVECAPS , LINECAPS , POLYGONALCAPS , TEXTCAPS };
      const char * dcname1[] = {"RASTERCAPS","CURVECAPS","LINECAPS","POLYGONALCAPS","TEXTCAPS"};
      const int dcnum2[]     = { 
       NUMBRUSHES , NUMPENS , NUMFONTS , NUMCOLORS ,
       HORZSIZE , VERTSIZE , HORZRES , VERTRES , LOGPIXELSX , LOGPIXELSY ,
       BITSPIXEL , PLANES , ASPECTX , ASPECTY , ASPECTXY , CLIPCAPS , 
       PHYSICALWIDTH , PHYSICALHEIGHT , PHYSICALOFFSETX , PHYSICALOFFSETY , SCALINGFACTORX , SCALINGFACTORY };
      const char * dcname2[] = {
       "NUMBRUSHES","NUMPENS","NUMFONTS","NUMCOLORS",
       "HORZSIZE","VERTSIZE","HORZRES","VERTRES","LOGPIXELSX","LOGPIXELSY",
       "BITSPIXEL","PLANES","ASPECTX","ASPECTY","ASPECTXY","CLIPCAPS",
       "PHYSICALWIDTH","PHYSICALHEIGHT","PHYSICALOFFSETX","PHYSICALOFFSETY","SCALINGFACTORX","SCALINGFACTORY"};
      
      HDC hdc = CreateDC("DISPLAY",NULL,NULL,NULL);
      for(int i = 0; i < sizeof(dcnum1)/sizeof(*dcnum1); i++){
        char b[16];
        r = GetDeviceCaps(hdc,dcnum1[i]);
        wsprintf(b,"%08X",r);
        buf += dcname1[i];
        buf += ": ";
        buf += b;
        buf += "\r\n";
      }
      DeleteDC(hdc);
      buf += "* * * * * * * *\r\n";
      buf += "* プリンタ情報 \r\n";
      buf += "* * * * * * * *\r\n";
      if(hPrintDC == NULL){
        buf += "プリンタDCを取得できません\r\n";
      }else{
        if(hDevNames == NULL){
          buf += "DEVNAMES が NULL です\r\n";
        }else{
          DEVNAMES * pdn = (DEVNAMES *)GlobalLock(hDevNames);
          buf += "デバイスドライバ: ";
          buf += (char *)pdn + pdn->wDriverOffset;
          buf += "\r\n";
          buf += "デバイス名: ";
          buf += (char *)pdn + pdn->wDeviceOffset;
          buf += "\r\n";
          buf += "出力メディア: ";
          buf += (char *)pdn + pdn->wOutputOffset;
          buf += "\r\n";
          GlobalUnlock(hDevNames);
        }
        buf += "---\r\n";
        if(hDevMode == NULL){
          buf += "DEVMODE が NULL です\r\n";
        }else{
          DEVMODE * pdv = (DEVMODE *)GlobalLock(hDevMode);
          char bb[16];
          if(pdv->dmFields & DM_ORIENTATION){wsprintf(bb,"%d",pdv->dmOrientation );buf +=           "ORIENTATION: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_PAPERSIZE){wsprintf(bb,"%d",pdv->dmPaperSize );buf +=               "PAPERSIZE: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_PAPERLENGTH){wsprintf(bb,"%d",pdv->dmPaperLength );buf +=           "PAPERLENGTH: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_PAPERWIDTH){wsprintf(bb,"%d",pdv->dmPaperWidth );buf +=             "PAPERWIDTH: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_POSITION){wsprintf(bb,"%d",pdv->dmPosition );buf +=                 "POSITION: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_SCALE){wsprintf(bb,"%d",pdv->dmScale );buf +=                       "SCALE: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_COPIES){wsprintf(bb,"%d",pdv->dmCopies );buf +=                     "COPIES: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_DEFAULTSOURCE){wsprintf(bb,"%d",pdv->dmDefaultSource );buf +=       "DEFAULTSOURCE: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_PRINTQUALITY){wsprintf(bb,"%d",pdv->dmPrintQuality );buf +=         "PRINTQUALITY: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_COLOR){
            buf += "COLOR: ";
            if(pdv->dmColor == DMCOLOR_COLOR){
              buf += "COLOR";
            }else if(pdv->dmColor == DMCOLOR_MONOCHROME){
              buf += "MONOCHROME";
            }else{
              wsprintf(bb,"%d",pdv->dmColor);
              buf += bb;
            }
            buf+="\r\n";
          }
          if(pdv->dmFields & DM_DUPLEX){wsprintf(bb,"%d",pdv->dmDuplex );buf +=                     "DUPLEX: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_YRESOLUTION){wsprintf(bb,"%d",pdv->dmYResolution );buf +=           "YRESOLUTION: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_TTOPTION){
            buf += "TTOPTION: ";
            if(pdv->dmTTOption == DMTT_BITMAP){
              buf += "BITMAP";
            }else if(pdv->dmTTOption == DMTT_DOWNLOAD){
              buf += "DOWNLOAD";
            }else if(pdv->dmTTOption == DMTT_DOWNLOAD_OUTLINE){
              buf += "DOWNLOAD_OUTLINE";
            }else if(pdv->dmTTOption == DMTT_SUBDEV){
              buf += "SUBDEV";
            }else{
              wsprintf(bb,"%d",pdv->dmTTOption);
              buf += bb;
            }
            buf+="\r\n";
          }
          if(pdv->dmFields & DM_COLLATE){wsprintf(bb,"%d",pdv->dmCollate );buf +=                   "COLLATE: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_FORMNAME){
            buf += "FORMNAME: ";
            buf += (char *)(pdv->dmFormName);
            buf+="\r\n";
          }
          if(pdv->dmFields & DM_LOGPIXELS){wsprintf(bb,"%d",pdv->dmLogPixels );buf +=               "LOGPIXELS: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_BITSPERPEL){wsprintf(bb,"%d",pdv->dmBitsPerPel );buf +=             "BITSPERPEL: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_PELSWIDTH){wsprintf(bb,"%d",pdv->dmPelsWidth );buf +=               "PELSWIDTH: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_PELSHEIGHT){wsprintf(bb,"%d",pdv->dmPelsHeight );buf +=             "PELSHEIGHT: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_DISPLAYFLAGS){wsprintf(bb,"%d",pdv->dmDisplayFlags );buf +=         "DISPLAYFLAGS: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_NUP){wsprintf(bb,"%d",pdv->dmNup );buf +=                           "NUP: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_DISPLAYFREQUENCY){wsprintf(bb,"%d",pdv->dmDisplayFrequency );buf += "DISPLAYFREQUENCY: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_ICMMETHOD){wsprintf(bb,"%d",pdv->dmICMMethod );buf +=               "ICMMETHOD: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_ICMINTENT){wsprintf(bb,"%d",pdv->dmICMIntent );buf +=               "ICMINTENT: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_MEDIATYPE){wsprintf(bb,"%d",pdv->dmMediaType );buf +=               "MEDIATYPE: "; buf += bb; buf+="\r\n";}
          if(pdv->dmFields & DM_DITHERTYPE){wsprintf(bb,"%d",pdv->dmDitherType );buf +=             "DITHERTYPE: "; buf += bb; buf+="\r\n";}
          GlobalUnlock(hDevMode);
        }
        buf += "---\r\n";
        for(int i = 0; i < sizeof(dcnum2)/sizeof(*dcnum2); i++){
          char b[16];
          r = GetDeviceCaps(hPrintDC,dcnum2[i]);
          wsprintf(b,"%d",r);
          buf += dcname2[i];
          buf += ": ";
          buf += b;
          buf += "\r\n";
        }
        for(int i = 0; i < sizeof(dcnum1)/sizeof(*dcnum1); i++){
          char b[16];
          r = GetDeviceCaps(hPrintDC,dcnum1[i]);
          wsprintf(b,"%08X",r);
          buf += dcname1[i];
          buf += ": ";
          buf += b;
          buf += "\r\n";
        }
      }
      buf += "-- 以上 --\r\n";
      SetWindowText(h,buf.c_str());
    }
    return TRUE;
    break;
  case WM_COMMAND:
    {
      int iEvent = HIWORD(wParam);
      int iId = LOWORD(wParam);
      switch(iId){
      case IDOK: case IDCANCEL:
        {
          EndDialog(hDlg,0);
        }
        break;
      }
    }
    return FALSE;
    break;
  }
  return FALSE;
}