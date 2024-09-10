//The implementation code of CreateButton.
HANDLE CreateBitmapButton(HANDLE hParent,TCHAR* pszText,
                                                          DWORD dwButtonId,int x,int y,
                                                          int cxbmp,int cybmp,
                                                          LPVOID pBitmap,
                                                          LPVOID pExtension)
{
         HANDLE                hButton  = NULL;
         __WINDOW*             pBtnWnd  = NULL;
         __BITMAP_BUTTON*      pButton  = NULL;
         BOOL                  bResult  = FALSE;
         __WINDOW*             pParent  = (__WINDOW*)hParent;
         __WINDOW_MESSAGE      msg;
         int                   height   = 0;  //Total width.
         int                   width    = 0;  //Total height.
         int                   txtheight = 0;
         int                   txtwidth = 0;
         int                   ntxtlen  = 0;
         HANDLE                hDC      = NULL;
 
         if(NULL == hParent)  //Invalid.
         {
                   return NULL;
         }
 
         hDC = GetWindowDC(hParent);
         pButton = (__BITMAP_BUTTON*)KMemAlloc(sizeof(__BITMAP_BUTTON),KMEM_SIZE_TYPE_ANY);
         if(NULL == pButton)
         {
                   goto __TERMINAL;
         }
         //Initialize button.
         pButton->dwBmpButtonId = dwButtonId;
 
         ntxtlen = strlen(pszText);
         if(ntxtlen >= BMPBTN_TEXT_LENGTH - 1)  //Text too long.
         {
                   goto __TERMINAL;
         }
         strcpy(pButton->ButtonText,pszText);
         pButton->x = x; //+ pParent->xclient;
         pButton->y = y; //+ pParent->yclient;
 
         txtheight  = GetTextMetric(hDC,pszText,TM_HEIGHT);
         txtheight  += TXT_MARGIN;  //Uper margin.
         txtheight  += TXT_MARGIN;  //Bottom margin.
         pButton->cy = cybmp + txtheight;
         pButton->txtheight = txtheight;
 
         width = GetTextMetric(hDC,pszText,TM_WIDTH);
         if(width > cxbmp - TXT_MARGIN * 2)  //Too long.
         {
                   goto __TERMINAL;
         }
         pButton->cx = cxbmp;
 
         pButton->xtxt = (pButton->cx - width) / 2;
         pButton->ytxt = cybmp + TXT_MARGIN;
         pButton->txtwidth = width;
 
         pButton->dwBmpBtnStatus = BUTTON_STATUS_NORMAL;
         pButton->pBmpData    = pBitmap;
         pButton->pButtonExtension = pExtension;
 
         //Set default button colors.
         pButton->FaceClr        = DEFAULT_BMPBTN_FACECOLOR;
         pButton->TxtBackground  = DEFAULT_BMPBTN_TXTBACKGROUND;
         pButton->TxtColor       = DEFAULT_BMPBTN_TXTCOLOR;
 
         //Allocate memory for bitmap data.
         if(pBitmap)
         {
                   pButton->pBmpData = KMemAlloc(cxbmp * cybmp * sizeof(__COLOR),KMEM_SIZE_TYPE_ANY);
                   if(NULL == pButton->pBmpData)
                   {
                            goto __TERMINAL;
                   }
                   memcpy(pButton->pBmpData,pBitmap,cxbmp * cybmp * sizeof(__COLOR));
         }
 
         //Create the button window.
         hButton = CreateWindow(0,  //Without any caption and border.
                   NULL,  //Without title.
                   pButton->x + pParent->x,
                   pButton->y + pParent->y,
                   pButton->cx,
                   pButton->cy,
                   BmpButtonWndProc,
                   hParent,
                   NULL,
                   GlobalParams.COLOR_BTNFACE,
                   NULL);
         if(NULL == hButton)
         {
                   goto __TERMINAL;
         }
         pBtnWnd = (__WINDOW*)hButton;
         pBtnWnd->lpWndExtension = (LPVOID)pButton;  //Save button information to window's ext.
 
         //Send WM_PAINT message to button to re-draw itself.
         msg.hWnd = hButton;
         msg.message = WM_PAINT;
         msg.wParam  = 0;
         msg.lParam  = 0;
         SendWindowMessage(hButton,&msg);
         bResult = TRUE;
 
__TERMINAL:
         if(!bResult)
         {
                   if(pButton)
                   {
                            if(pButton->pBmpData)
                            {
                                     KMemFree(pButton->pBmpData,KMEM_SIZE_TYPE_ANY,0);
                            }
                            KMemFree(pButton,KMEM_SIZE_TYPE_ANY,0);
                   }
                   if(hButton)
                   {
                            CloseWindow(hButton);
                   }
                   hButton = NULL;
         }
         return hButton;
}