U_CAPI UBool U_EXPORT2
u_hasBinaryProperty(UChar32 c, UProperty which) {
    /* c is range-checked in the functions that are called from here */
    if(which<UCHAR_BINARY_START || UCHAR_BINARY_LIMIT<=which) {
        /* not a known binary property */
    } else {
        uint32_t mask=binProps[which].mask;
        int32_t column=binProps[which].column;
        if(mask!=0) {
            /* systematic, directly stored properties */
            return (u_getUnicodeProperties(c, column)&mask)!=0;
        } else {
            if(column==UPROPS_SRC_CASE) {
                return ucase_hasBinaryProperty(c, which);
            } else if(column==UPROPS_SRC_NORM) {
#if !UCONFIG_NO_NORMALIZATION
                /* normalization properties from unorm.icu */
                switch(which) {
                case UCHAR_SEGMENT_STARTER:
                    return unorm_isCanonSafeStart(c);
                default:
                    break;
                }
#endif
            } else if(column==UPROPS_SRC_NFC) {
#if !UCONFIG_NO_NORMALIZATION
                UErrorCode errorCode=U_ZERO_ERROR;
                switch(which) {
                case UCHAR_FULL_COMPOSITION_EXCLUSION: {
                    // By definition, Full_Composition_Exclusion is the same as NFC_QC=No.
                    const Normalizer2Impl *impl=Normalizer2Factory::getNFCImpl(errorCode);
                    return U_SUCCESS(errorCode) && impl->isCompNo(impl->getNorm16(c));
                    break;
                }
                default: {
                    // UCHAR_NF[CD]_INERT properties
                    const Normalizer2 *norm2=Normalizer2Factory::getInstance(
                        (UNormalizationMode)(which-UCHAR_NFD_INERT+UNORM_NFD), errorCode);
                    return U_SUCCESS(errorCode) && norm2->isInert(c);
                }
                }
#endif
            } else if(column==UPROPS_SRC_NFKC) {
#if !UCONFIG_NO_NORMALIZATION
                // UCHAR_NFK[CD]_INERT properties
                UErrorCode errorCode=U_ZERO_ERROR;
                const Normalizer2 *norm2=Normalizer2Factory::getInstance(
                    (UNormalizationMode)(which-UCHAR_NFD_INERT+UNORM_NFD), errorCode);
                return U_SUCCESS(errorCode) && norm2->isInert(c);
#endif
            } else if(column==UPROPS_SRC_NFKC_CF) {
                // currently only for UCHAR_CHANGES_WHEN_NFKC_CASEFOLDED
#if !UCONFIG_NO_NORMALIZATION
                UErrorCode errorCode=U_ZERO_ERROR;
                const Normalizer2Impl *kcf=Normalizer2Factory::getNFKC_CFImpl(errorCode);
                if(U_SUCCESS(errorCode)) {
                    UnicodeString src(c);
                    UnicodeString dest;
                    {
                        // The ReorderingBuffer must be in a block because its destructor
                        // needs to release dest's buffer before we look at its contents.
                        ReorderingBuffer buffer(*kcf, dest);
                        // Small destCapacity for NFKC_CF(c).
                        if(buffer.init(5, errorCode)) {
                            const UChar *srcArray=src.getBuffer();
                            kcf->compose(srcArray, srcArray+src.length(), FALSE,
                                         TRUE, buffer, errorCode);
                        }
                    }
                    return U_SUCCESS(errorCode) && dest!=src;
                }
#endif
            } else if(column==UPROPS_SRC_BIDI) {
                /* bidi/shaping properties */
                const UBiDiProps *bdp=GET_BIDI_PROPS();
                if(bdp!=NULL) {
                    switch(which) {
                    case UCHAR_BIDI_MIRRORED:
                        return ubidi_isMirrored(bdp, c);
                    case UCHAR_BIDI_CONTROL:
                        return ubidi_isBidiControl(bdp, c);
                    case UCHAR_JOIN_CONTROL:
                        return ubidi_isJoinControl(bdp, c);
                    default:
                        break;
                    }
                }
                /* else return FALSE below */
            } else if(column==UPROPS_SRC_CHAR) {
                switch(which) {
                case UCHAR_POSIX_BLANK:
                    return u_isblank(c);
                case UCHAR_POSIX_GRAPH:
                    return u_isgraphPOSIX(c);
                case UCHAR_POSIX_PRINT:
                    return u_isprintPOSIX(c);
                case UCHAR_POSIX_XDIGIT:
                    return u_isxdigit(c);
                default:
                    break;
                }
            } else if(column==UPROPS_SRC_CHAR_AND_PROPSVEC) {
                switch(which) {
                case UCHAR_POSIX_ALNUM:
                    return u_isalnumPOSIX(c);
                default:
                    break;
                }
            } else if(column==UPROPS_SRC_CASE_AND_NORM) {
#if !UCONFIG_NO_NORMALIZATION
                UChar nfdBuffer[4];
                const UChar *nfd;
                int32_t nfdLength;
                UErrorCode errorCode=U_ZERO_ERROR;
                const Normalizer2Impl *nfcImpl=Normalizer2Factory::getNFCImpl(errorCode);
                if(U_FAILURE(errorCode)) {
                    return FALSE;
                }
                switch(which) {
                case UCHAR_CHANGES_WHEN_CASEFOLDED:
                    nfd=nfcImpl->getDecomposition(c, nfdBuffer, nfdLength);
                    if(nfd!=NULL) {
                        /* c has a decomposition */
                        if(nfdLength==1) {
                            c=nfd[0];  /* single BMP code point */
                        } else if(nfdLength<=U16_MAX_LENGTH) {
                            int32_t i=0;
                            U16_NEXT(nfd, i, nfdLength, c);
                            if(i==nfdLength) {
                                /* single supplementary code point */
                            } else {
                                c=U_SENTINEL;
                            }
                        } else {
                            c=U_SENTINEL;
                        }
                    } else if(c<0) {
                        return FALSE;  /* protect against bad input */
                    }
                    errorCode=U_ZERO_ERROR;
                    if(c>=0) {
                        /* single code point */
                        const UCaseProps *csp=ucase_getSingleton(&errorCode);
                        const UChar *resultString;
                        return (UBool)(ucase_toFullFolding(csp, c, &resultString, U_FOLD_CASE_DEFAULT)>=0);
                    } else {
                        /* guess some large but stack-friendly capacity */
                        UChar dest[2*UCASE_MAX_STRING_LENGTH];
                        int32_t destLength;
                        destLength=u_strFoldCase(dest, LENGTHOF(dest), nfd, nfdLength, U_FOLD_CASE_DEFAULT, &errorCode);
                        return (UBool)(U_SUCCESS(errorCode) && 0!=u_strCompare(nfd, nfdLength, dest, destLength, FALSE));
                    }
                default:
                    break;
                }
#endif
            }
        }
    }
    return FALSE;
}