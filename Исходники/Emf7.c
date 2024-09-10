int CALLBACK EnhMetaFileProc (HDC hdc, HANDLETABLE * pHandleTable,
                              CONST ENHMETARECORD * pEmfRecord, 
                              int iHandles, LPARAM pData)
{
     HBRUSH   hBrush ;
     HPEN     hPen ;
     LOGBRUSH lb ;
     
     if (pEmfRecord->iType != EMR_HEADER && pEmfRecord->iType != EMR_EOF)
          
          PlayEnhMetaFileRecord (hdc, pHandleTable, pEmfRecord, iHandles) ;
     
     if (pEmfRecord->iType == EMR_RECTANGLE)
     {
          hBrush = SelectObject (hdc, GetStockObject (NULL_BRUSH)) ;
          
          lb.lbStyle = BS_SOLID ;
          lb.lbColor = RGB (0, 255, 0) ;
          lb.lbHatch = 0 ;
          
          hPen = SelectObject (hdc,
               ExtCreatePen (PS_SOLID | PS_GEOMETRIC, 5, &lb, 0, NULL)) ;
          
          Ellipse (hdc, 100, 100, 200, 200) ;
          
          DeleteObject (SelectObject (hdc, hPen)) ;
          SelectObject (hdc, hBrush) ;
     }
     return TRUE ;
}