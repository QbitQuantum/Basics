static void verifyEnumeration(int line, UEnumeration *u, const char * const * compareToChar, const UChar * const * compareToUChar, int32_t expect_count) {
  UErrorCode status = U_ZERO_ERROR;
  int32_t got_count,i,len;
  const char *c;
  UChar buf[1024];

  log_verbose("%s:%d: verifying enumeration..\n", __FILE__, line);

  uenum_reset(u, &status);
  if(U_FAILURE(status)) {
    log_err("%s:%d: FAIL: could not reset char strings enumeration: %s\n", __FILE__, line, u_errorName(status));
    return;
  }

  got_count = uenum_count(u, &status);
  if(U_FAILURE(status)) {
    log_err("%s:%d: FAIL: could not count char strings enumeration: %s\n", __FILE__, line, u_errorName(status));
    return;
  }
  
  if(got_count!=expect_count) {
    log_err("%s:%d: FAIL: expect count %d got %d\n", __FILE__, line, expect_count, got_count);
  } else {
    log_verbose("%s:%d: OK: got count %d\n", __FILE__, line, got_count);
  }

  if(compareToChar!=NULL) { /* else, not invariant */
    for(i=0;i<got_count;i++) {
      c = uenum_next(u,&len, &status);
      if(U_FAILURE(status)) {
        log_err("%s:%d: FAIL: could not iterate to next after %d: %s\n", __FILE__, line, i, u_errorName(status));
        return;
      }
      if(c==NULL) {
        log_err("%s:%d: FAIL: got NULL for next after %d: %s\n", __FILE__, line, i, u_errorName(status));
        return;
      }
      
      if(strcmp(c,compareToChar[i])) {
        log_err("%s:%d: FAIL: string #%d expected '%s' got '%s'\n", __FILE__, line, i, compareToChar[i], c);
      } else {
        log_verbose("%s:%d: OK: string #%d got '%s'\n", __FILE__, line, i, c);
      }
      
      if(len!=strlen(compareToChar[i])) {
        log_err("%s:%d: FAIL: string #%d expected len %d got %d\n", __FILE__, line, i, strlen(compareToChar[i]), len);
      } else {
        log_verbose("%s:%d: OK: string #%d got len %d\n", __FILE__, line, i, len);
      }
    }
  }

  /* now try U */
  uenum_reset(u, &status);
  if(U_FAILURE(status)) {
    log_err("%s:%d: FAIL: could not reset again char strings enumeration: %s\n", __FILE__, line, u_errorName(status));
    return;
  }

  for(i=0;i<got_count;i++) {
    const UChar *ustr = uenum_unext(u,&len, &status);
    if(U_FAILURE(status)) {
      log_err("%s:%d: FAIL: could not iterate to unext after %d: %s\n", __FILE__, line, i, u_errorName(status));
      return;
    }
    if(ustr==NULL) {
      log_err("%s:%d: FAIL: got NULL for unext after %d: %s\n", __FILE__, line, i, u_errorName(status));
      return;
    }
    if(compareToChar!=NULL) {
      u_charsToUChars(compareToChar[i], buf, strlen(compareToChar[i])+1);
      if(u_strncmp(ustr,buf,len)) {
        int j;
        log_err("%s:%d: FAIL: ustring #%d expected '%s' got '%s'\n", __FILE__, line, i, compareToChar[i], austrdup(ustr));
        for(j=0;ustr[j]&&buf[j];j++) {
          log_verbose("  @ %d\t<U+%04X> vs <U+%04X>\n", j, ustr[j],buf[j]);
        }
      } else {
        log_verbose("%s:%d: OK: ustring #%d got '%s'\n", __FILE__, line, i, compareToChar[i]);
      }
      
      if(len!=strlen(compareToChar[i])) {
        log_err("%s:%d: FAIL: ustring #%d expected len %d got %d\n", __FILE__, line, i, strlen(compareToChar[i]), len);
      } else {
        log_verbose("%s:%d: OK: ustring #%d got len %d\n", __FILE__, line, i, len);
      }
    }

    if(compareToUChar!=NULL) {
      if(u_strcmp(ustr,compareToUChar[i])) {
        int j;
        log_err("%s:%d: FAIL: ustring #%d expected '%s' got '%s'\n", __FILE__, line, i, austrdup(compareToUChar[i]), austrdup(ustr));
        for(j=0;ustr[j]&&compareToUChar[j];j++) {
          log_verbose("  @ %d\t<U+%04X> vs <U+%04X>\n", j, ustr[j],compareToUChar[j]);
        }
      } else {
        log_verbose("%s:%d: OK: ustring #%d got '%s'\n", __FILE__, line, i, austrdup(compareToUChar[i]));
      }
      
      if(len!=u_strlen(compareToUChar[i])) {
        log_err("%s:%d: FAIL: ustring #%d expected len %d got %d\n", __FILE__, line, i, u_strlen(compareToUChar[i]), len);
      } else {
        log_verbose("%s:%d: OK: ustring #%d got len %d\n", __FILE__, line, i, len);
      }
    }
  }
}