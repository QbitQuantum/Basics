void CGT_CDiagMsg::intErr(
    const CG_Edipos* pEdp,
    const TCHAR*     pszCompilerFile, 
    int              nLine, 
    const TCHAR*     pszReason
)
{
    TCHAR     buffer[64];
  
    const TCHAR* ppsz[3];
    ppsz[0] = pszCompilerFile ? pszCompilerFile : _T("??");
    ppsz[1] = ltoa(nLine, buffer, 10);
    ppsz[2] = pszReason ? pszReason : _T("??");
    
    msg(CG_E_INTERNAL, pEdp, ppsz);
}