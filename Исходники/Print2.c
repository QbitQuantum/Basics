BOOL PrintMyPage (HWND hwnd)
{
     static DOCINFO di = { sizeof (DOCINFO), TEXT ("Print2: Printing") } ;
     BOOL           bSuccess = TRUE ;
     HDC            hdcPrn ;
     short          xPage, yPage ;
     
     if (NULL == (hdcPrn = GetPrinterDC ()))
          return FALSE ;
     
     xPage = GetDeviceCaps (hdcPrn, HORZRES) ;
     yPage = GetDeviceCaps (hdcPrn, VERTRES) ;
     
     EnableWindow (hwnd, FALSE) ;
     
     SetAbortProc (hdcPrn, AbortProc) ;
     
     if (StartDoc (hdcPrn, &di) > 0)
     {
          if (StartPage (hdcPrn) > 0)
          {
               PageGDICalls (hdcPrn, xPage, yPage) ;
               
               if (EndPage (hdcPrn) > 0)
                    EndDoc (hdcPrn) ;
               else
                    bSuccess = FALSE ;
          }
     }
     else
          bSuccess = FALSE ;
     
     EnableWindow (hwnd, TRUE) ;
     DeleteDC (hdcPrn) ;
     return bSuccess ;
}