/* helper function */
static UChar* 
_strFromWCS( UChar   *dest,
             int32_t destCapacity, 
             int32_t *pDestLength,
             const wchar_t *src,
             int32_t srcLength,
             UErrorCode *pErrorCode)
{
    int32_t retVal =0, count =0 ;
    UConverter* conv = NULL;
    UChar* pTarget = NULL;
    UChar* pTargetLimit = NULL;
    UChar* target = NULL;
    
    UChar uStack [_STACK_BUFFER_CAPACITY];

    wchar_t wStack[_STACK_BUFFER_CAPACITY];
    wchar_t* pWStack = wStack;


    char cStack[_STACK_BUFFER_CAPACITY];
    int32_t cStackCap = _STACK_BUFFER_CAPACITY;
    char* pCSrc=cStack;
    char* pCSave=pCSrc;
    char* pCSrcLimit=NULL;

    const wchar_t* pSrc = src;
    const wchar_t* pSrcLimit = NULL;

    if(srcLength ==-1){
        /* if the wchar_t source is null terminated we can safely
         * assume that there are no embedded nulls, this is a fast
         * path for null terminated strings.
         */
        for(;;){
            /* convert wchars  to chars */
            retVal = uprv_wcstombs(pCSrc,src, cStackCap);
    
            if(retVal == -1){
                *pErrorCode = U_ILLEGAL_CHAR_FOUND;
                goto cleanup;
            }else if(retVal >= (cStackCap-1)){
                /* Should rarely occur */
                u_growAnyBufferFromStatic(cStack,(void**)&pCSrc,&cStackCap,
                    cStackCap * _BUFFER_CAPACITY_MULTIPLIER, 0, sizeof(char));
                pCSave = pCSrc;
            }else{
                /* converted every thing */
                pCSrc = pCSrc+retVal;
                break;
            }
        }
        
    }else{
        /* here the source is not null terminated 
         * so it may have nulls embeded and we need to
         * do some extra processing 
         */
        int32_t remaining =cStackCap;
        
        pSrcLimit = src + srcLength;

        for(;;){
            register int32_t nulLen = 0;

            /* find nulls in the string */
            while(nulLen<srcLength && pSrc[nulLen++]!=0){
            }

            if((pSrc+nulLen) < pSrcLimit){
                /* check if we have enough room in pCSrc */
                if(remaining < (nulLen * MB_CUR_MAX)){
                    /* should rarely occur */
                    int32_t len = (pCSrc-pCSave);
                    pCSrc = pCSave;
                    /* we do not have enough room so grow the buffer*/
                    u_growAnyBufferFromStatic(cStack,(void**)&pCSrc,&cStackCap,
                           _BUFFER_CAPACITY_MULTIPLIER*cStackCap+(nulLen*MB_CUR_MAX),len,sizeof(char));

                    pCSave = pCSrc;
                    pCSrc = pCSave+len;
                    remaining = cStackCap-(pCSrc - pCSave);
                }

                /* we have found a null  so convert the 
                 * chunk from begining of non-null char to null
                 */
                retVal = uprv_wcstombs(pCSrc,pSrc,remaining);

                if(retVal==-1){
                    /* an error occurred bail out */
                    *pErrorCode = U_ILLEGAL_CHAR_FOUND;
                    goto cleanup;
                }

                pCSrc += retVal+1 /* already null terminated */;

                pSrc += nulLen; /* skip past the null */
                srcLength-=nulLen; /* decrement the srcLength */
                remaining -= (pCSrc-pCSave);


            }else{
                /* the source is not null terminated and we are 
                 * end of source so we copy the source to a temp buffer
                 * null terminate it and convert wchar_ts to chars
                 */
                if(nulLen >= _STACK_BUFFER_CAPACITY){
                    /* Should rarely occcur */
                    /* allocate new buffer buffer */
                    pWStack =(wchar_t*) uprv_malloc(sizeof(wchar_t) * (nulLen + 1));
                    if(pWStack==NULL){
                        *pErrorCode = U_MEMORY_ALLOCATION_ERROR;
                        goto cleanup;
                    }
                }
                if(nulLen>0){
                    /* copy the contents to tempStack */
                    uprv_memcpy(pWStack,pSrc,nulLen*sizeof(wchar_t));
                }
            
                /* null terminate the tempBuffer */
                pWStack[nulLen] =0 ;
            
                if(remaining < (nulLen * MB_CUR_MAX)){
                    /* Should rarely occur */
                    int32_t len = (pCSrc-pCSave);
                    pCSrc = pCSave;
                    /* we do not have enough room so grow the buffer*/
                    u_growAnyBufferFromStatic(cStack,(void**)&pCSrc,&cStackCap,
                           cStackCap+(nulLen*MB_CUR_MAX),len,sizeof(char));

                    pCSave = pCSrc;
                    pCSrc = pCSave+len;
                    remaining = cStackCap-(pCSrc - pCSave);
                }
                /* convert to chars */
                retVal = uprv_wcstombs(pCSrc,pWStack,remaining);
            
                pCSrc += retVal;
                pSrc  += nulLen;
                srcLength-=nulLen; /* decrement the srcLength */
                break;
            }
        }
    }

    /* OK..now we have converted from wchar_ts to chars now 
     * convert chars to UChars 
     */
    pCSrcLimit = pCSrc;
    pCSrc = pCSave;
    pTarget = target= dest;
    pTargetLimit = dest + destCapacity;    
    
    conv= u_getDefaultConverter(pErrorCode);
    
    if(U_FAILURE(*pErrorCode)|| conv==NULL){
        goto cleanup;
    }
    
    for(;;) {
        
        *pErrorCode = U_ZERO_ERROR;
        
        /* convert to stack buffer*/
        ucnv_toUnicode(conv,&pTarget,pTargetLimit,(const char**)&pCSrc,pCSrcLimit,NULL,(UBool)(pCSrc==pCSrcLimit),pErrorCode);
        
        /* increment count to number written to stack */
        count+= pTarget - target;
        
        if(*pErrorCode==U_BUFFER_OVERFLOW_ERROR){
            target = uStack;
            pTarget = uStack;
            pTargetLimit = uStack + _STACK_BUFFER_CAPACITY;
        } else {
            break;
        }
        
    }
    
    if(pDestLength){
        *pDestLength =count;
    }

    u_terminateUChars(dest,destCapacity,count,pErrorCode);
    
cleanup:
 
    if(cStack != pCSave){
        uprv_free(pCSave);
    }

    if(wStack != pWStack){
        uprv_free(pWStack);
    }
    
    u_releaseDefaultConverter(conv);

    return dest;
}