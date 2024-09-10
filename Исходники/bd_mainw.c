LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM uParam,LPARAM lParam) {

 TEXTMETRIC tm;
 PAINTSTRUCT ps;
 HDC hdc;

 int i,j,k,t;

 static int cxChar,cyChar;
 static int outRow,outCol;

 CHAR c;
 CHAR lnBuffer[128];
 CHAR *lnPtr;
 int lnLen;
 int outColFlag;

 switch (message) {
 case WM_CREATE:
    hdc = GetDC(hwnd);
    SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
    GetTextMetrics(hdc,&tm);
    cxChar = tm.tmAveCharWidth;
    cyChar = tm.tmHeight;
    ReleaseDC(hwnd,hdc);
    outRow = 0;
    outCol = 0;
    break;

 case WM_SIZE:
    break;

 case WM_SETFOCUS:
    CreateCaret(hwnd,(HBITMAP)1,cxChar,cyChar);
    ShowCaret(hwnd);
    break;

 case WM_KILLFOCUS:
    HideCaret(hwnd);
    DestroyCaret();
    break;

 case WM_PAINT:
    hdc = BeginPaint(hwnd,&ps);
    SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));

    outRow=0;
    outCol=0;
    outColFlag = 0;
    lnPtr = lnBuffer;
    lnLen = 0;

    for (i=1; i <= gCurrStr; i++) {
       k = strlen(&gPutStr[i][0]);
       for (j=0; j < k; j++) {
          c = gPutStr[i][j];
          switch (c) {
          case '\n':
             if (lnLen) TextOut(hdc,(outCol*cxChar),(outRow*cyChar),lnBuffer,lnLen);
             lnPtr = lnBuffer;
             lnLen = 0;
             outCol = 0;
             outRow++;
             break;
          case '\r':
             outColFlag = 1;
             break;
          case '\x0C':  // form-feed (rest of gPutStr[] line ignored)
             // cls
             gCurrStr=0;
             InvalidateRect(gHwnd,NULL,TRUE);
             break;

          default:
             if (c >= 32) {
                *lnPtr++ = c;
                lnLen++;
             }
          }
       }
       if (lnLen) {
          TextOut(hdc,(outCol*cxChar),(outRow*cyChar),lnBuffer,lnLen);
          outCol = outCol + lnLen;
          lnPtr = lnBuffer;
          lnLen = 0;
       }
       if (outColFlag) {
          outCol = 0;
          outColFlag = 0;
       }
    }

    SetCaretPos(outCol*cxChar,outRow*cyChar);
    EndPaint(hwnd,&ps);
    break;

 case WM_CHAR:
    HideCaret(hwnd);
    for (i=0; i < (int)LOWORD(lParam); i++) {
       switch(LOWORD(uParam)) {
       case '\r':
          outRow++;
          outCol=0;
          gGetStr[gCurrChar] = '\x0';
          gInputReady = 1;             // used in GetMsg() in bd_main.c
          break;
       case '\n':
          break;
       case '\b':
          if (gCurrChar > 0) {
             gCurrChar--;
             gGetStr[gCurrChar] = '\x0';
             t = strlen(&gPutStr[gCurrStr][0]);
             if (t > 0) gPutStr[gCurrStr][t-1] = 0;
             if (outCol > 0) outCol--;  // play it safe
             hdc = GetDC(hwnd);
             SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
             TextOut(hdc,(outCol*cxChar),(outRow*cyChar)," ",1);
             ReleaseDC(hwnd, hdc);
          }
          break;
       default:
          if (gCurrChar < sizeof(gGetStr)-1) {
             c = (CHAR)LOWORD(uParam);
             if ((c >= 32) & (c < 127)) {
                gGetStr[gCurrChar] = c;
                t = strlen(&gPutStr[gCurrStr][0]);
                gPutStr[gCurrStr][t] = c;
                gPutStr[gCurrStr][t+1] = '\x0';
                hdc = GetDC(hwnd);
                SelectObject(hdc,GetStockObject(SYSTEM_FIXED_FONT));
                TextOut(hdc,(outCol*cxChar),(outRow*cyChar),&c,1);
                ReleaseDC(hwnd, hdc);
                gCurrChar++;
                outCol++;
             }
          }
          else {
             gGetStr[gCurrChar] = '\x0';
             gInputReady = 1;
          }
          break;
       }
    }
    SetCaretPos(outCol*cxChar,outRow*cyChar);
    ShowCaret(hwnd);
    break;

 case WM_DESTROY:
    PostQuitMessage(0);
    break;

 default:
    return (DefWindowProc(hwnd, message, uParam, lParam));
 }
 return 0;
}