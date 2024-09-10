void CSVOutputStream::writeUtf8(size32_t len, const char * data)
{
    append(prefix);
    if (oldOutputFormat) {
        append(quote).append(rtlUtf8Size(len, data), data).append(quote); 
    }
    else if (len) {
        // is this OTT?
        // not sure if best way but generate an array of utf8 sizes
        MemoryAttr ma;
        size32_t * cl;
        if (len>256) 
            cl = (size32_t *)ma.allocate(sizeof(size32_t)*len);
        else
            cl = (size32_t *)alloca(sizeof(size32_t)*len);
        unsigned start=(unsigned)-1;
        unsigned end=0;
        const byte * s = (const byte *)data;
        unsigned i;
        for (i=0;i<len;i++) {
            const byte *p=s;
            UChar next = readUtf8Character(sizeof(UChar), s);
            cl[i] = (size32_t)(s-p);
            if (!u_isspace(next)) {
                end = i;
                if (start==(unsigned)-1)
                    start = i;
            }
        }
        const byte *e=s;
        // do trim
        if (start!=(unsigned)-1) {
            for (i=0;i<start;i++)
                data += *(cl++);
            len -= start;
            end -= start;
            end++;
            while (end<len)
                e -= cl[--len];
        }
        // now see if need quoting by looking for separator, terminator or quote
        // I *think* this can be done with memcmps as has to be exact
        size32_t sl = separator.length();
        size32_t tl = terminator.length();
        size32_t ql = quote.length();
        bool needquote=false;
        s = (const byte *)data;
        for (i=0;i<len;i++) {
            size32_t l = (size32_t)(e-s);
            if (sl&&(l>=sl)&&(memcmp(separator.get(),s,sl)==0)) {
                needquote = true;
                break;
            }
            if (tl&&(l>=tl)&&(memcmp(terminator.get(),s,tl)==0)) {
                needquote = true;
                break;
            }
            if ((l>=ql)&&(memcmp(quote.get(),s,ql)==0)) {
                needquote = true;
                break;
            }
            s+=cl[i];
        }
        if (needquote) {
            append(quote);
            s = (const byte *)data;
            for (i=0;i<len;i++) {
                size32_t l = (size32_t)(e-s);
                if ((l>=ql)&&(memcmp(quote.get(),s,ql)==0)) 
                    append(quote);
                append(cl[i],(const char *)s);
                s+=cl[i];
            }
            append(quote);
        }
        else 
            append((size32_t)(e-(const byte *)data),data);
    }
    prefix = separator; 
}