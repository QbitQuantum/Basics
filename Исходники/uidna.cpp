static int32_t
_internal_toASCII(const UChar* src, int32_t srcLength,
                  UChar* dest, int32_t destCapacity,
                  int32_t options,
                  UStringPrepProfile* nameprep,
                  UParseError* parseError,
                  UErrorCode* status)
{

    // TODO Revisit buffer handling. The label should not be over 63 ASCII characters. ICU4J may need to be updated too.
    UChar b1Stack[MAX_LABEL_BUFFER_SIZE], b2Stack[MAX_LABEL_BUFFER_SIZE];
    //initialize pointers to stack buffers
    UChar  *b1 = b1Stack, *b2 = b2Stack;
    int32_t b1Len=0, b2Len,
            b1Capacity = MAX_LABEL_BUFFER_SIZE,
            b2Capacity = MAX_LABEL_BUFFER_SIZE ,
            reqLength=0;

    int32_t namePrepOptions = ((options & UIDNA_ALLOW_UNASSIGNED) != 0) ? USPREP_ALLOW_UNASSIGNED: 0;
    UBool* caseFlags = NULL;

    // the source contains all ascii codepoints
    UBool srcIsASCII  = TRUE;
    // assume the source contains all LDH codepoints
    UBool srcIsLDH = TRUE;

    int32_t j=0;

    //get the options
    UBool useSTD3ASCIIRules = (UBool)((options & UIDNA_USE_STD3_RULES) != 0);

    int32_t failPos = -1;

    if(srcLength == -1){
        srcLength = u_strlen(src);
    }

    if(srcLength > b1Capacity){
        b1 = (UChar*) uprv_malloc(srcLength * U_SIZEOF_UCHAR);
        if(b1==NULL){
            *status = U_MEMORY_ALLOCATION_ERROR;
            goto CLEANUP;
        }
        b1Capacity = srcLength;
    }

    // step 1
    for( j=0;j<srcLength;j++){
        if(src[j] > 0x7F){
            srcIsASCII = FALSE;
        }
        b1[b1Len++] = src[j];
    }

    // step 2 is performed only if the source contains non ASCII
    if(srcIsASCII == FALSE){

        // step 2
        b1Len = usprep_prepare(nameprep, src, srcLength, b1, b1Capacity, namePrepOptions, parseError, status);

        if(*status == U_BUFFER_OVERFLOW_ERROR){
            // redo processing of string
            // we do not have enough room so grow the buffer
            if(b1 != b1Stack){
                uprv_free(b1);
            }
            b1 = (UChar*) uprv_malloc(b1Len * U_SIZEOF_UCHAR);
            if(b1==NULL){
                *status = U_MEMORY_ALLOCATION_ERROR;
                goto CLEANUP;
            }

            *status = U_ZERO_ERROR; // reset error

            b1Len = usprep_prepare(nameprep, src, srcLength, b1, b1Len, namePrepOptions, parseError, status);
        }
    }
    // error bail out
    if(U_FAILURE(*status)){
        goto CLEANUP;
    }
    if(b1Len == 0){
        *status = U_IDNA_ZERO_LENGTH_LABEL_ERROR;
        goto CLEANUP;
    }

    // for step 3 & 4
    srcIsASCII = TRUE;
    for( j=0;j<b1Len;j++){
        // check if output of usprep_prepare is all ASCII
        if(b1[j] > 0x7F){
            srcIsASCII = FALSE;
        }else if(isLDHChar(b1[j])==FALSE){  // if the char is in ASCII range verify that it is an LDH character
            srcIsLDH = FALSE;
            failPos = j;
        }
    }
    if(useSTD3ASCIIRules == TRUE){
        // verify 3a and 3b
        // 3(a) Verify the absence of non-LDH ASCII code points; that is, the
        //  absence of 0..2C, 2E..2F, 3A..40, 5B..60, and 7B..7F.
        // 3(b) Verify the absence of leading and trailing hyphen-minus; that
        //  is, the absence of U+002D at the beginning and end of the
        //  sequence.
        if( srcIsLDH == FALSE /* source at this point should not contain anyLDH characters */
            || b1[0] ==  HYPHEN || b1[b1Len-1] == HYPHEN){
            *status = U_IDNA_STD3_ASCII_RULES_ERROR;

            /* populate the parseError struct */
            if(srcIsLDH==FALSE){
                // failPos is always set the index of failure
                uprv_syntaxError(b1,failPos, b1Len,parseError);
            }else if(b1[0] == HYPHEN){
                // fail position is 0
                uprv_syntaxError(b1,0,b1Len,parseError);
            }else{
                // the last index in the source is always length-1
                uprv_syntaxError(b1, (b1Len>0) ? b1Len-1 : b1Len, b1Len,parseError);
            }

            goto CLEANUP;
        }
    }
    // Step 4: if the source is ASCII then proceed to step 8
    if(srcIsASCII){
        if(b1Len <= destCapacity){
            uprv_memmove(dest, b1, b1Len * U_SIZEOF_UCHAR);
            reqLength = b1Len;
        }else{
            reqLength = b1Len;
            goto CLEANUP;
        }
    }else{
        // step 5 : verify the sequence does not begin with ACE prefix
        if(!startsWithPrefix(b1,b1Len)){

            //step 6: encode the sequence with punycode

            // do not preserve the case flags for now!
            // TODO: Preserve the case while implementing the RFE
            // caseFlags = (UBool*) uprv_malloc(b1Len * sizeof(UBool));
            // uprv_memset(caseFlags,TRUE,b1Len);

            b2Len = u_strToPunycode(b1,b1Len,b2,b2Capacity,caseFlags, status);

            if(*status == U_BUFFER_OVERFLOW_ERROR){
                // redo processing of string
                /* we do not have enough room so grow the buffer*/
                b2 = (UChar*) uprv_malloc(b2Len * U_SIZEOF_UCHAR);
                if(b2 == NULL){
                    *status = U_MEMORY_ALLOCATION_ERROR;
                    goto CLEANUP;
                }

                *status = U_ZERO_ERROR; // reset error

                b2Len = u_strToPunycode(b1,b1Len,b2,b2Len,caseFlags, status);
            }
            //error bail out
            if(U_FAILURE(*status)){
                goto CLEANUP;
            }
            // TODO : Reconsider while implementing the case preserve RFE
            // convert all codepoints to lower case ASCII
            // toASCIILower(b2,b2Len);
            reqLength = b2Len+ACE_PREFIX_LENGTH;

            if(reqLength > destCapacity){
                *status = U_BUFFER_OVERFLOW_ERROR;
                goto CLEANUP;
            }
            //Step 7: prepend the ACE prefix
            uprv_memcpy(dest,ACE_PREFIX,ACE_PREFIX_LENGTH * U_SIZEOF_UCHAR);
            //Step 6: copy the contents in b2 into dest
            uprv_memcpy(dest+ACE_PREFIX_LENGTH, b2, b2Len * U_SIZEOF_UCHAR);

        }else{
            *status = U_IDNA_ACE_PREFIX_ERROR;
            //position of failure is 0
            uprv_syntaxError(b1,0,b1Len,parseError);
            goto CLEANUP;
        }
    }
    // step 8: verify the length of label
    if(reqLength > MAX_LABEL_LENGTH){
        *status = U_IDNA_LABEL_TOO_LONG_ERROR;
    }

CLEANUP:
    if(b1 != b1Stack){
        uprv_free(b1);
    }
    if(b2 != b2Stack){
        uprv_free(b2);
    }
    uprv_free(caseFlags);

    return u_terminateUChars(dest, destCapacity, reqLength, status);
}