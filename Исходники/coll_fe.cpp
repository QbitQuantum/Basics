int32_t GLUE_SYM ( Collator ) :: appendAvailable(UnicodeString* strs, int32_t i, int32_t /*count*/) {
   int avail = OICU_ucol_countAvailable();
   UErrorCode status = U_ZERO_ERROR;
   OICU_u_init(&status);
#if COLL_FE_DEBUG
   fprintf(stderr,  "VCF " ICUGLUE_VER_STR " avail %d - init %s\n", avail, u_errorName(status));
#endif   
    for(int j=0;j<avail;j++) {
         strs[i+j].append(OICU_ucol_getAvailable(j));
         strs[i+j].append("@sp=icu");
         
         if(IS_OLD_VERSTR(ICUGLUE_VER_STR)) {
           strs[i+j].append( ICUGLUE_VER_STR[OLD_VERSTR_MAJ] );  // X_y
           strs[i+j].append( ICUGLUE_VER_STR[OLD_VERSTR_MIN] );  // x_Y
         } else {
           strs[i+j].append( ICUGLUE_VER_STR[NEW_VERSTR_MAJ] );  // Xy_
           strs[i+j].append( ICUGLUE_VER_STR[NEW_VERSTR_MIN] );  // xY_
         }

#if COLL_FE_DEBUG
         { 
            char foo[999];
            const UChar *ss = strs[i+j].getTerminatedBuffer();
            u_austrcpy(foo, ss);
            debugfprintf((stderr,  "VCF " ICUGLUE_VER_STR " appending [%d+%d=%d] <<%s>>\n", i, j, i+j, foo));
        }
#endif
    }
    return OICU_ucol_countAvailable();
 }