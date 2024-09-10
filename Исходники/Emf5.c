int CALLBACK EnhMetaFileProc (HDC hdc, HANDLETABLE * pHandleTable,
                              CONST ENHMETARECORD * pEmfRecord, 
                              int iHandles, LPARAM pData)
{
     PlayEnhMetaFileRecord (hdc, pHandleTable, pEmfRecord, iHandles) ;
     
     return TRUE ;
}