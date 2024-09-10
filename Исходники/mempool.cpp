LPSTR CMemPool::GetDuplicateStringA(LPCSTR szSrc)  
{  
    assert(szSrc);  
  
    DWORD dwBytes = (_mbslen((const unsigned char*)szSrc) + 1) * sizeof(CHAR);  
    LPSTR pString = (LPSTR)GetAlignedMemory(dwBytes, sizeof(CHAR));  
  
    if (pString)   
    {  
        _mbscpy_s((unsigned char*)pString, dwBytes, (const unsigned char*)szSrc);  
    }  
    return pString;  
}  