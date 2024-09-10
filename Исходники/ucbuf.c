/* getc and escape it */
U_CAPI int32_t U_EXPORT2
ucbuf_getcx32(UCHARBUF* buf,UErrorCode* error) {
    int32_t length;
    int32_t offset;
    UChar32 c32,c1,c2;
    if(error==NULL || U_FAILURE(*error)){
        return FALSE;
    }
    /* Fill the buffer if it is empty */
    if (buf->currentPos >=buf->bufLimit-2) {
        ucbuf_fillucbuf(buf,error);
    }

    /* Get the next character in the buffer */
    if (buf->currentPos < buf->bufLimit) {
        c1 = *(buf->currentPos)++;
    } else {
        c1 = U_EOF;
    }

    c2 = *(buf->currentPos);

    /* If it isn't a backslash, return it */
    if (c1 != 0x005C) {
        return c1;
    }

    /* Determine the amount of data in the buffer */
    length = (int32_t)(buf->bufLimit - buf->currentPos);

    /* The longest escape sequence is \Uhhhhhhhh; make sure
       we have at least that many characters */
    if (length < 10) {

        /* fill the buffer */
        ucbuf_fillucbuf(buf,error);
        length = (int32_t)(buf->bufLimit - buf->buffer);
    }

    /* Process the escape */
    offset = 0;
    c32 = u_unescapeAt(_charAt, &offset, length, (void*)buf);

    /* check if u_unescapeAt unescaped and converted
     * to c32 or not
     */
    if(c32==0xFFFFFFFF){
        if(buf->showWarning) {
            char context[CONTEXT_LEN+1];
            int32_t len = CONTEXT_LEN;
            if(length < len) {
                len = length; 
            }
            context[len]= 0 ; /* null terminate the buffer */
            u_UCharsToChars( buf->currentPos, context, len);
            fprintf(stderr,"Bad escape: [%c%s]...\n", (int)c1, context);
        }
        *error= U_ILLEGAL_ESCAPE_SEQUENCE;
        return c1;
    }else if(c32!=c2 || (c32==0x0075 && c2==0x0075 && c1==0x005C) /* for \u0075 c2=0x0075 and c32==0x0075*/){
        /* Update the current buffer position */
        buf->currentPos += offset;
    }else{
        /* unescaping failed so we just return
         * c1 and not consume the buffer
         * this is useful for rules with escapes
         * in resouce bundles
         * eg: \' \\ \"
         */
        return c1;
    }

    return c32;
}