static int32_t convertFromPuny(  const UChar* src, int32_t srcLength,
								 UChar* dest, int32_t destCapacity,
                                 UErrorCode& status){
    char b1Stack[MAX_LABEL_BUFFER_SIZE];
    char* b1 = b1Stack;
    int32_t destLen =0;

    convertUCharsToASCII(src, b1,srcLength);

    uint32_t b2Stack[MAX_LABEL_BUFFER_SIZE];
    uint32_t* b2 = b2Stack;
    int32_t b2Len =MAX_LABEL_BUFFER_SIZE;
    unsigned char* caseFlags = NULL; //(unsigned char*) uprv_malloc(srcLength * sizeof(unsigned char*));
    punycode_status error = punycode_decode(srcLength,b1,(uint32_t*)&b2Len,b2,caseFlags);
    status = getError(error);
    if(status == U_BUFFER_OVERFLOW_ERROR){
        b2 =  (uint32_t*) uprv_malloc(b2Len * sizeof(uint32_t));
        if(b2 == NULL){
            status = U_MEMORY_ALLOCATION_ERROR;
            goto CLEANUP;
        }
        error = punycode_decode(srcLength,b1,(uint32_t*)&b2Len,b2,caseFlags);
        status = getError(error);
    }

    if(U_FAILURE(status)){
        goto CLEANUP;
    }

    u_strFromUTF32(dest,destCapacity,&destLen,(UChar32*)b2,b2Len,&status);

CLEANUP:
    if(b1Stack != b1){
        uprv_free(b1);
    }
    if(b2Stack != b2){
        uprv_free(b2);
    }
    uprv_free(caseFlags);

    return destLen;   
}