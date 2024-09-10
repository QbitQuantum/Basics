BOOL My_LZOpenFileA()
{
    LPSTR lpFileName=NULL;
    LPOFSTRUCT lpReOpenBuf=NULL;
    WORD wStyle=NULL;
    INT returnVal_Real = NULL;
    INT returnVal_Intercepted = NULL;

    DWORD error_Real = 0;
    DWORD error_Intercepted = 0;
    disableInterception();
    returnVal_Real = LZOpenFileA (lpFileName,lpReOpenBuf,wStyle);
    error_Real = GetLastError();
    enableInterception();
    returnVal_Intercepted = LZOpenFileA (lpFileName,lpReOpenBuf,wStyle);
    error_Intercepted = GetLastError();
    return ((returnVal_Real == returnVal_Intercepted) && (error_Real == error_Intercepted));
}