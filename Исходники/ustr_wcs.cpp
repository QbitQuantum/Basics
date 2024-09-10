U_CAPI UChar* U_EXPORT2
u_strFromWCS(UChar   *dest,
             int32_t destCapacity,
             int32_t *pDestLength,
             const wchar_t *src,
             int32_t srcLength,
             UErrorCode *pErrorCode)
{

    /* args check */
    if(pErrorCode==NULL || U_FAILURE(*pErrorCode)){
        return NULL;
    }

    if( (src==NULL && srcLength!=0) || srcLength < -1 ||
        (destCapacity<0) || (dest == NULL && destCapacity > 0)
    ) {
        *pErrorCode = U_ILLEGAL_ARGUMENT_ERROR;
        return NULL;
    }

#ifdef U_WCHAR_IS_UTF16
    /* wchar_t is UTF-16 just do a memcpy */
    if(srcLength == -1){
        srcLength = u_strlen(src);
    }
    if(0 < srcLength && srcLength <= destCapacity){
        uprv_memcpy(dest,src,srcLength*U_SIZEOF_UCHAR);
    }
    if(pDestLength){
       *pDestLength = srcLength;
    }

    u_terminateUChars(dest,destCapacity,srcLength,pErrorCode);

    return dest;

#elif defined U_WCHAR_IS_UTF32

    return u_strFromUTF32(dest, destCapacity, pDestLength,
                          (UChar32*)src, srcLength, pErrorCode);

#else

    return _strFromWCS(dest,destCapacity,pDestLength,src,srcLength,pErrorCode);

#endif

}