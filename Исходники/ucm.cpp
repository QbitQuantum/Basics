/* parse a mapping line; must not be empty */
U_CAPI UBool U_EXPORT2
ucm_parseMappingLine(UCMapping *m,
                     UChar32 codePoints[UCNV_EXT_MAX_UCHARS],
                     uint8_t bytes[UCNV_EXT_MAX_BYTES],
                     const char *line) {
    const char *s;
    char *end;
    UChar32 cp;
    int32_t u16Length;
    int8_t uLen, bLen, f;

    s=line;
    uLen=bLen=0;

    /* parse code points */
    for(;;) {
        /* skip an optional plus sign */
        if(uLen>0 && *s=='+') {
            ++s;
        }
        if(*s!='<') {
            break;
        }

        if( s[1]!='U' ||
            (cp=(UChar32)uprv_strtoul(s+2, &end, 16), end)==s+2 ||
            *end!='>'
        ) {
            fprintf(stderr, "ucm error: Unicode code point must be formatted as <UXXXX> (1..6 hex digits) - \"%s\"\n", line);
            return FALSE;
        }
        if((uint32_t)cp>0x10ffff || U_IS_SURROGATE(cp)) {
            fprintf(stderr, "ucm error: Unicode code point must be 0..d7ff or e000..10ffff - \"%s\"\n", line);
            return FALSE;
        }

        if(uLen==UCNV_EXT_MAX_UCHARS) {
            fprintf(stderr, "ucm error: too many code points on \"%s\"\n", line);
            return FALSE;
        }
        codePoints[uLen++]=cp;
        s=end+1;
    }

    if(uLen==0) {
        fprintf(stderr, "ucm error: no Unicode code points on \"%s\"\n", line);
        return FALSE;
    } else if(uLen==1) {
        m->u=codePoints[0];
    } else {
        UErrorCode errorCode=U_ZERO_ERROR;
        u_strFromUTF32(NULL, 0, &u16Length, codePoints, uLen, &errorCode);
        if( (U_FAILURE(errorCode) && errorCode!=U_BUFFER_OVERFLOW_ERROR) ||
            u16Length>UCNV_EXT_MAX_UCHARS
        ) {
            fprintf(stderr, "ucm error: too many UChars on \"%s\"\n", line);
            return FALSE;
        }
    }

    s=u_skipWhitespace(s);

    /* parse bytes */
    bLen=ucm_parseBytes(bytes, line, &s);

    if(bLen<0) {
        return FALSE;
    } else if(bLen==0) {
        fprintf(stderr, "ucm error: no bytes on \"%s\"\n", line);
        return FALSE;
    } else if(bLen<=4) {
        uprv_memcpy(m->b.bytes, bytes, bLen);
    }

    /* skip everything until the fallback indicator, even the start of a comment */
    for(;;) {
        if(*s==0) {
            f=-1; /* no fallback indicator */
            break;
        } else if(*s=='|') {
            f=(int8_t)(s[1]-'0');
            if((uint8_t)f>4) {
                fprintf(stderr, "ucm error: fallback indicator must be |0..|4 - \"%s\"\n", line);
                return FALSE;
            }
            break;
        }
        ++s;
    }

    m->uLen=uLen;
    m->bLen=bLen;
    m->f=f;
    return TRUE;
}