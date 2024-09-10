SECURITY_STATUS SEC_ENTRY thunk_ImportSecurityContextW(
 SEC_WCHAR *pszPackage, PSecBuffer pPackedContext, void *Token,
 PCtxtHandle phContext)
{
    SECURITY_STATUS ret;
    PSTR package = SECUR32_AllocMultiByteFromWide(pszPackage);

    TRACE("%s %p %p %p\n", debugstr_w(pszPackage), pPackedContext, Token,
     phContext);
    ret = ImportSecurityContextA(package, pPackedContext, Token, phContext);
    HeapFree(GetProcessHeap(), 0, package);
    return ret;
}