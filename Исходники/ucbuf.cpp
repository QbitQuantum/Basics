/* fill the uchar buffer */
static UCHARBUF*
ucbuf_fillucbuf( UCHARBUF* buf,UErrorCode* error){
    UChar* pTarget=NULL;
    UChar* target=NULL;
    const char* source=NULL;
    char  carr[MAX_IN_BUF] = {'\0'};
    char* cbuf =  carr;
    int32_t inputRead=0;
    int32_t outputWritten=0;
    int32_t offset=0;
    const char* sourceLimit =NULL;
    int32_t cbufSize=0;
    pTarget = buf->buffer;
    /* check if we arrived here without exhausting the buffer*/
    if(buf->currentPos<buf->bufLimit){
        offset = (int32_t)(buf->bufLimit-buf->currentPos);
        memmove(buf->buffer,buf->currentPos,offset* sizeof(UChar));
    }

#if UCBUF_DEBUG
    memset(pTarget+offset,0xff,sizeof(UChar)*(MAX_IN_BUF-offset));
#endif
    if(buf->isBuffered){
        cbufSize = MAX_IN_BUF;
        /* read the file */
        inputRead=T_FileStream_read(buf->in,cbuf,cbufSize-offset);
        buf->remaining-=inputRead;
        
    }else{
        cbufSize = T_FileStream_size(buf->in);
        cbuf = (char*)uprv_malloc(cbufSize);
        if (cbuf == NULL) {
        	*error = U_MEMORY_ALLOCATION_ERROR;
        	return NULL;
        }
        inputRead= T_FileStream_read(buf->in,cbuf,cbufSize);
        buf->remaining-=inputRead;
    }

    /* just to be sure...*/
    if ( 0 == inputRead )
       buf->remaining = 0;

    target=pTarget;
    /* convert the bytes */
    if(buf->conv){
        /* set the callback to stop */
        UConverterToUCallback toUOldAction ;
        void* toUOldContext;
        void* toUNewContext=NULL;
        ucnv_setToUCallBack(buf->conv,
           UCNV_TO_U_CALLBACK_STOP,
           toUNewContext,
           &toUOldAction,
           (const void**)&toUOldContext,
           error);
        /* since state is saved in the converter we add offset to source*/
        target = pTarget+offset;
        source = cbuf;
        sourceLimit = source + inputRead;
        ucnv_toUnicode(buf->conv,&target,target+(buf->bufCapacity-offset),
                        &source,sourceLimit,NULL,
                        (UBool)(buf->remaining==0),error);

        if(U_FAILURE(*error)){
            char context[CONTEXT_LEN+1];
            char preContext[CONTEXT_LEN+1];
            char postContext[CONTEXT_LEN+1];
            int8_t len = CONTEXT_LEN;
            int32_t start=0;
            int32_t stop =0;
            int32_t pos =0;
            /* use erro1 to preserve the error code */
            UErrorCode error1 =U_ZERO_ERROR;
            
            if( buf->showWarning==TRUE){
                fprintf(stderr,"\n###WARNING: Encountered abnormal bytes while"
                               " converting input stream to target encoding: %s\n",
                               u_errorName(*error));
            }


            /* now get the context chars */
            ucnv_getInvalidChars(buf->conv,context,&len,&error1);
            context[len]= 0 ; /* null terminate the buffer */

            pos = (int32_t)(source - cbuf - len);

            /* for pre-context */
            start = (pos <=CONTEXT_LEN)? 0 : (pos - (CONTEXT_LEN-1));
            stop  = pos-len;

            memcpy(preContext,cbuf+start,stop-start);
            /* null terminate the buffer */
            preContext[stop-start] = 0;

            /* for post-context */
            start = pos+len;
            stop  = (int32_t)(((pos+CONTEXT_LEN)<= (sourceLimit-cbuf) )? (pos+(CONTEXT_LEN-1)) : (sourceLimit-cbuf));

            memcpy(postContext,source,stop-start);
            /* null terminate the buffer */
            postContext[stop-start] = 0;

            if(buf->showWarning ==TRUE){
                /* print out the context */
                fprintf(stderr,"\tPre-context: %s\n",preContext);
                fprintf(stderr,"\tContext: %s\n",context);
                fprintf(stderr,"\tPost-context: %s\n", postContext);
            }

            /* reset the converter */
            ucnv_reset(buf->conv);

            /* set the call back to substitute
             * and restart conversion
             */
            ucnv_setToUCallBack(buf->conv,
               UCNV_TO_U_CALLBACK_SUBSTITUTE,
               toUNewContext,
               &toUOldAction,
               (const void**)&toUOldContext,
               &error1);

            /* reset source and target start positions */
            target = pTarget+offset;
            source = cbuf;

            /* re convert */
            ucnv_toUnicode(buf->conv,&target,target+(buf->bufCapacity-offset),
                            &source,sourceLimit,NULL,
                            (UBool)(buf->remaining==0),&error1);

        }
        outputWritten = (int32_t)(target - pTarget);

#if UCBUF_DEBUG
        {
            int i;
            target = pTarget;
            for(i=0;i<numRead;i++){
              /*  printf("%c", (char)(*target++));*/
            }
        }
#endif

    }else{
        u_charsToUChars(cbuf,target+offset,inputRead);
        outputWritten=((buf->remaining>cbufSize)? cbufSize:inputRead+offset);
    }
    buf->currentPos = pTarget;
    buf->bufLimit=pTarget+outputWritten;
    *buf->bufLimit=0; /*NUL terminate*/
    if(cbuf!=carr){
        uprv_free(cbuf);
    }
    return buf;
}