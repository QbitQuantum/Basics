U_CAPI UResourceBundle * U_EXPORT2
ures_openU(const UChar *myPath, 
           const char *localeID, 
           UErrorCode *status)
{
    char pathBuffer[1024];
    int32_t length;
    char *path = pathBuffer;

    if(status==NULL || U_FAILURE(*status)) {
        return NULL;
    }
    if(myPath==NULL) {
        path = NULL;
    }
    else {
        length=u_strlen(myPath);
        if(length>=sizeof(pathBuffer)) {
            *status=U_ILLEGAL_ARGUMENT_ERROR;
            return NULL;
        } else if(uprv_isInvariantUString(myPath, length)) {
            /*
             * the invariant converter is sufficient for package and tree names
             * and is more efficient
             */
            u_UCharsToChars(myPath, path, length+1); /* length+1 to include the NUL */
        } else {
#if !UCONFIG_NO_CONVERSION
            /* use the default converter to support variant-character paths */
            UConverter *cnv=u_getDefaultConverter(status);
            length=ucnv_fromUChars(cnv, path, (int32_t)sizeof(pathBuffer), myPath, length, status);
            u_releaseDefaultConverter(cnv);
            if(U_FAILURE(*status)) {
                return NULL;
            }
            if(length>=sizeof(pathBuffer)) {
                /* not NUL-terminated - path too long */
                *status=U_ILLEGAL_ARGUMENT_ERROR;
                return NULL;
            }
#else
            /* the default converter is not available */
            *status=U_UNSUPPORTED_ERROR;
            return NULL;
#endif
        }
    }

    return ures_open(path, localeID, status);
}