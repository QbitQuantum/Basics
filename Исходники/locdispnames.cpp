/* Instead of having a separate pass for 'special' patterns, reintegrate the two
 * so we don't get bitten by preflight bugs again.  We can be reasonably efficient
 * without two separate code paths, this code isn't that performance-critical.
 *
 * This code is general enough to deal with patterns that have a prefix or swap the
 * language and remainder components, since we gave developers enough rope to do such
 * things if they futz with the pattern data.  But since we don't give them a way to
 * specify a pattern for arbitrary combinations of components, there's not much use in
 * that.  I don't think our data includes such patterns, the only variable I know if is
 * whether there is a space before the open paren, or not.  Oh, and zh uses different
 * chars than the standard open/close paren (which ja and ko use, btw).
 */
U_CAPI int32_t U_EXPORT2
uloc_getDisplayName(const char *locale,
                    const char *displayLocale,
                    UChar *dest, int32_t destCapacity,
                    UErrorCode *pErrorCode)
{
    static const UChar defaultSeparator[9] = { 0x007b, 0x0030, 0x007d, 0x002c, 0x0020, 0x007b, 0x0031, 0x007d, 0x0000 }; /* "{0}, {1}" */
    static const UChar sub0[4] = { 0x007b, 0x0030, 0x007d , 0x0000 } ; /* {0} */
    static const UChar sub1[4] = { 0x007b, 0x0031, 0x007d , 0x0000 } ; /* {1} */
    static const int32_t subLen = 3;
    static const UChar defaultPattern[10] = {
        0x007b, 0x0030, 0x007d, 0x0020, 0x0028, 0x007b, 0x0031, 0x007d, 0x0029, 0x0000
    }; /* {0} ({1}) */
    static const int32_t defaultPatLen = 9;
    static const int32_t defaultSub0Pos = 0;
    static const int32_t defaultSub1Pos = 5;

    int32_t length; /* of formatted result */

    const UChar *separator;
    int32_t sepLen = 0;
    const UChar *pattern;
    int32_t patLen = 0;
    int32_t sub0Pos, sub1Pos;
    
    UChar formatOpenParen         = 0x0028; // (
    UChar formatReplaceOpenParen  = 0x005B; // [
    UChar formatCloseParen        = 0x0029; // )
    UChar formatReplaceCloseParen = 0x005D; // ]

    UBool haveLang = TRUE; /* assume true, set false if we find we don't have
                              a lang component in the locale */
    UBool haveRest = TRUE; /* assume true, set false if we find we don't have
                              any other component in the locale */
    UBool retry = FALSE; /* set true if we need to retry, see below */

    int32_t langi = 0; /* index of the language substitution (0 or 1), virtually always 0 */

    if(pErrorCode==NULL || U_FAILURE(*pErrorCode)) {
        return 0;
    }

    if(destCapacity<0 || (destCapacity>0 && dest==NULL)) {
        *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    {
        UErrorCode status = U_ZERO_ERROR;
        UResourceBundle* locbundle=ures_open(U_ICUDATA_LANG, displayLocale, &status);
        UResourceBundle* dspbundle=ures_getByKeyWithFallback(locbundle, _kLocaleDisplayPattern,
                                                             NULL, &status);

        separator=ures_getStringByKeyWithFallback(dspbundle, _kSeparator, &sepLen, &status);
        pattern=ures_getStringByKeyWithFallback(dspbundle, _kPattern, &patLen, &status);

        ures_close(dspbundle);
        ures_close(locbundle);
    }

    /* If we couldn't find any data, then use the defaults */
    if(sepLen == 0) {
       separator = defaultSeparator;
    }
    /* #10244: Even though separator is now a pattern, it is awkward to handle it as such
     * here since we are trying to build the display string in place in the dest buffer,
     * and to handle it as a pattern would entail having separate storage for the
     * substrings that need to be combined (the first of which may be the result of
     * previous such combinations). So for now we continue to treat the portion between
     * {0} and {1} as a string to be appended when joining substrings, ignoring anything
     * that is before {0} or after {1} (no existing separator pattern has any such thing).
     * This is similar to how pattern is handled below.
     */
    {
        UChar *p0=u_strstr(separator, sub0);
        UChar *p1=u_strstr(separator, sub1);
        if (p0==NULL || p1==NULL || p1<p0) {
            *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
            return 0;
        }
        separator = (const UChar *)p0 + subLen;
        sepLen = p1 - separator;
    }

    if(patLen==0 || (patLen==defaultPatLen && !u_strncmp(pattern, defaultPattern, patLen))) {
        pattern=defaultPattern;
        patLen=defaultPatLen;
        sub0Pos=defaultSub0Pos;
        sub1Pos=defaultSub1Pos;
        // use default formatOpenParen etc. set above
    } else { /* non-default pattern */
        UChar *p0=u_strstr(pattern, sub0);
        UChar *p1=u_strstr(pattern, sub1);
        if (p0==NULL || p1==NULL) {
            *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
            return 0;
        }
        sub0Pos=p0-pattern;
        sub1Pos=p1-pattern;
        if (sub1Pos < sub0Pos) { /* a very odd pattern */
            int32_t t=sub0Pos; sub0Pos=sub1Pos; sub1Pos=t;
            langi=1;
        }
        if (u_strchr(pattern, 0xFF08) != NULL) {
            formatOpenParen         = 0xFF08; // fullwidth (
            formatReplaceOpenParen  = 0xFF3B; // fullwidth [
            formatCloseParen        = 0xFF09; // fullwidth )
            formatReplaceCloseParen = 0xFF3D; // fullwidth ]
        }
    }

    /* We loop here because there is one case in which after the first pass we could need to
     * reextract the data.  If there's initial padding before the first element, we put in
     * the padding and then write that element.  If it turns out there's no second element,
     * we didn't need the padding.  If we do need the data (no preflight), and the first element
     * would have fit but for the padding, we need to reextract.  In this case (only) we
     * adjust the parameters so padding is not added, and repeat.
     */
    do {
        UChar* p=dest;
        int32_t patPos=0; /* position in the pattern, used for non-substitution portions */
        int32_t langLen=0; /* length of language substitution */
        int32_t langPos=0; /* position in output of language substitution */
        int32_t restLen=0; /* length of 'everything else' substitution */
        int32_t restPos=0; /* position in output of 'everything else' substitution */
        UEnumeration* kenum = NULL; /* keyword enumeration */

        /* prefix of pattern, extremely likely to be empty */
        if(sub0Pos) {
            if(destCapacity >= sub0Pos) {
                while (patPos < sub0Pos) {
                    *p++ = pattern[patPos++];
                }
            } else {
                patPos=sub0Pos;
            }
            length=sub0Pos;
        } else {
            length=0;
        }

        for(int32_t subi=0,resti=0;subi<2;) { /* iterate through patterns 0 and 1*/
            UBool subdone = FALSE; /* set true when ready to move to next substitution */

            /* prep p and cap for calls to get display components, pin cap to 0 since
               they complain if cap is negative */
            int32_t cap=destCapacity-length;
            if (cap <= 0) {
                cap=0;
            } else {
                p=dest+length;
            }

            if (subi == langi) { /* {0}*/
                if(haveLang) {
                    langPos=length;
                    langLen=uloc_getDisplayLanguage(locale, displayLocale, p, cap, pErrorCode);
                    length+=langLen;
                    haveLang=langLen>0;
                }
                subdone=TRUE;
            } else { /* {1} */
                if(!haveRest) {
                    subdone=TRUE;
                } else {
                    int32_t len; /* length of component (plus other stuff) we just fetched */
                    switch(resti++) {
                        case 0:
                            restPos=length;
                            len=uloc_getDisplayScriptInContext(locale, displayLocale, p, cap, pErrorCode);
                            break;
                        case 1:
                            len=uloc_getDisplayCountry(locale, displayLocale, p, cap, pErrorCode);
                            break;
                        case 2:
                            len=uloc_getDisplayVariant(locale, displayLocale, p, cap, pErrorCode);
                            break;
                        case 3:
                            kenum = uloc_openKeywords(locale, pErrorCode);
                            /* fall through */
                        default: {
                            const char* kw=uenum_next(kenum, &len, pErrorCode);
                            if (kw == NULL) {
                                uenum_close(kenum);
                                len=0; /* mark that we didn't add a component */
                                subdone=TRUE;
                            } else {
                                /* incorporating this behavior into the loop made it even more complex,
                                   so just special case it here */
                                len = uloc_getDisplayKeyword(kw, displayLocale, p, cap, pErrorCode);
                                if(len) {
                                    if(len < cap) {
                                        p[len]=0x3d; /* '=', assume we'll need it */
                                    }
                                    len+=1;

                                    /* adjust for call to get keyword */
                                    cap-=len;
                                    if(cap <= 0) {
                                        cap=0;
                                    } else {
                                        p+=len;
                                    }
                                }
                                /* reset for call below */
                                if(*pErrorCode == U_BUFFER_OVERFLOW_ERROR) {
                                    *pErrorCode=U_ZERO_ERROR;
                                }
                                int32_t vlen = uloc_getDisplayKeywordValue(locale, kw, displayLocale,
                                                                           p, cap, pErrorCode);
                                if(len) {
                                    if(vlen==0) {
                                        --len; /* remove unneeded '=' */
                                    }
                                    /* restore cap and p to what they were at start */
                                    cap=destCapacity-length;
                                    if(cap <= 0) {
                                        cap=0;
                                    } else {
                                        p=dest+length;
                                    }
                                }
                                len+=vlen; /* total we added for key + '=' + value */
                            }
                        } break;
                    } /* end switch */

                    if (len>0) {
                        /* we addeed a component, so add separator and write it if there's room. */
                        if(len+sepLen<=cap) {
                            const UChar * plimit = p + len;
                            for (; p < plimit; p++) {
                                if (*p == formatOpenParen) {
                                    *p = formatReplaceOpenParen;
                                } else if (*p == formatCloseParen) {
                                    *p = formatReplaceCloseParen;
                                }
                            }
                            for(int32_t i=0;i<sepLen;++i) {
                                *p++=separator[i];
                            }
                        }
                        length+=len+sepLen;
                    } else if(subdone) {
                        /* remove separator if we added it */
                        if (length!=restPos) {
                            length-=sepLen;
                        }
                        restLen=length-restPos;
                        haveRest=restLen>0;
                    }
                }
            }

            if(*pErrorCode == U_BUFFER_OVERFLOW_ERROR) {
                *pErrorCode=U_ZERO_ERROR;
            }

            if(subdone) {
                if(haveLang && haveRest) {
                    /* append internal portion of pattern, the first time,
                       or last portion of pattern the second time */
                    int32_t padLen;
                    patPos+=subLen;
                    padLen=(subi==0 ? sub1Pos : patLen)-patPos;
                    if(length+padLen < destCapacity) {
                        p=dest+length;
                        for(int32_t i=0;i<padLen;++i) {
                            *p++=pattern[patPos++];
                        }
                    } else {
                        patPos+=padLen;
                    }
                    length+=padLen;
                } else if(subi==0) {
                    /* don't have first component, reset for second component */
                    sub0Pos=0;
                    length=0;
                } else if(length>0) {
                    /* true length is the length of just the component we got. */
                    length=haveLang?langLen:restLen;
                    if(dest && sub0Pos!=0) {
                        if (sub0Pos+length<=destCapacity) {
                            /* first component not at start of result,
                               but we have full component in buffer. */
                            u_memmove(dest, dest+(haveLang?langPos:restPos), length);
                        } else {
                            /* would have fit, but didn't because of pattern prefix. */
                            sub0Pos=0; /* stops initial padding (and a second retry,
                                          so we won't end up here again) */
                            retry=TRUE;
                        }
                    }
                }

                ++subi; /* move on to next substitution */
            }
        }
    } while(retry);

    return u_terminateUChars(dest, destCapacity, length, pErrorCode);
}