int32_t GLUE_SYM ( DateFormat ) :: appendAvailable(UnicodeString* strs, int32_t i, int32_t /*count*/) {
   int avail = OICU_udat_countAvailable();
   UErrorCode status = U_ZERO_ERROR;
   OICU_u_init(&status);
#if DATE_FE_DEBUG
   fprintf(stderr,  "VCF " ICUGLUE_VER_STR " avail %d - init %s\n", avail, u_errorName(status));
#endif   
    for(int j=0;j<avail;j++) {
         strs[i+j].append(OICU_udat_getAvailable(j));
         strs[i+j].append("@sp=icu");
         strs[i+j].append( ICUGLUE_VER_STR[0] );  // X_y
         strs[i+j].append( ICUGLUE_VER_STR[2] );  // x_Y
#if DATE_FE_DEBUG
         { 
            char foo[999];
            const UChar *ss = strs[i+j].getTerminatedBuffer();
            u_austrcpy(foo, ss);
            //            fprintf(stderr,  "VCF " ICUGLUE_VER_STR " appending [%d+%d=%d] <<%s>>\n", i, j, i+j, foo);
        }
#endif
    }
    return OICU_ucol_countAvailable();
 }