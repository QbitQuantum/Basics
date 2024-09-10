U_CAPI UChar* U_EXPORT2
u_strFromUTF8(UChar *dest,
              int32_t destCapacity,
              int32_t *pDestLength,
              const char* src,
              int32_t srcLength,
              UErrorCode *pErrorCode){

    UChar *pDest = dest;
    UChar *pDestLimit = dest+destCapacity;
    UChar32 ch=0;
    int32_t index = 0;
    int32_t reqLength = 0;
    uint8_t* pSrc = (uint8_t*) src;

    /* args check */
    if(pErrorCode==NULL || U_FAILURE(*pErrorCode)){
        return NULL;
    }

    if((src==NULL) || (srcLength < -1) || (destCapacity<0) || (!dest && destCapacity > 0)){
        *pErrorCode = U_ILLEGAL_ARGUMENT_ERROR;
        return NULL;
    }

    if(srcLength == -1){
       srcLength = (int32_t)uprv_strlen((char*)pSrc);
    }

    while((index < srcLength)&&(pDest<pDestLimit)){
        ch = pSrc[index++];
        if(ch <=0x7f){
            *pDest++=(UChar)ch;
        }else{
            ch=utf8_nextCharSafeBody(pSrc, &index, srcLength, ch, -1);
            if(ch<0){
                *pErrorCode = U_INVALID_CHAR_FOUND;
                return NULL;
            }else if(ch<=0xFFFF){
                *(pDest++)=(UChar)ch;
            }else{
                *(pDest++)=UTF16_LEAD(ch);
                if(pDest<pDestLimit){
                    *(pDest++)=UTF16_TRAIL(ch);
                }else{
                    reqLength++;
                    break;
                }
            }
        }
    }
    /* donot fill the dest buffer just count the UChars needed */
    while(index < srcLength){
        ch = pSrc[index++];
        if(ch <= 0x7f){
            reqLength++;
        }else{
            ch=utf8_nextCharSafeBody(pSrc, &index, srcLength, ch, -1);
            if(ch<0){
                *pErrorCode = U_INVALID_CHAR_FOUND;
                return NULL;
            }
            reqLength+=UTF_CHAR_LENGTH(ch);
        }
    }

    reqLength+=(int32_t)(pDest - dest);

    if(pDestLength){
        *pDestLength = reqLength;
    }

    /* Terminate the buffer */
    u_terminateUChars(dest,destCapacity,reqLength,pErrorCode);

    return dest;
}