WORD
I_MNetLogonControl(
    LPTSTR pszServer,
    DWORD FunctionCode,
    DWORD QueryLevel,
    LPBYTE *Buffer) 
{
    DWORD   nRes;  // return from Netapi

    nRes = I_NetLogonControl(pszServer, FunctionCode, QueryLevel, Buffer) ;
    
    return LOWORD(nRes);
}