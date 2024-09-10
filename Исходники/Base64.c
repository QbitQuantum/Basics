int ToBase64Crypto( const BYTE* pSrc, int nLenSrc, wchar_t* pDst, int nLenDst )
{
   DWORD nLenOut= nLenDst;
   BOOL fRet= CryptBinaryToStringW((const BYTE*)pSrc, nLenSrc,CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF,pDst, &nLenOut);
   if (!fRet) nLenOut=0;
   return( nLenOut );
}