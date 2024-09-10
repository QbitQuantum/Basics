U_CAPI void U_EXPORT2
uiter_setLenient8(UCharIterator *iter, const char *s, int32_t length) {
    if(iter!=0) {
        if(s!=0 && length>=-1) {
            *iter=lenient8Iterator;
            iter->context=s;
            if(length>=0) {
                iter->limit=length;
            } else {
                iter->limit=strlen(s);
            }
            iter->length= iter->limit<=1 ? iter->limit : -1;
        } else {
            /* set no-op iterator */
            uiter_setString(iter, NULL, 0);
        }
    }
}