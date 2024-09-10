NS_IMETHODIMP 
sbStringTransformImpl::NormalizeString(const nsAString & aCharset, 
                                       PRUint32 aTransformFlags, 
                                       const nsAString & aInput, 
                                       nsAString & _retval)
{
  nsString finalStr;
  nsString inStr(aInput);

  if(inStr.IsEmpty()) {
    _retval.Truncate();
    return NS_OK;
  }

  nsTArray<WORD> excludeChars[NTYPES];
  nsTArray<WORD> includeChars[NTYPES];
  DWORD dwFlags = MakeFlags(aTransformFlags, 
                            excludeChars,
                            includeChars);

  if(aTransformFlags & sbIStringTransform::TRANSFORM_LOWERCASE ||
     aTransformFlags & sbIStringTransform::TRANSFORM_UPPERCASE) {

    WCHAR *wszJunk = {0};
    int requiredBufferSize = ::LCMapStringW(LOCALE_USER_DEFAULT,
                                            dwFlags,
                                            inStr.BeginReading(),
                                            inStr.Length(),
                                            wszJunk,
                                            0);

    nsString bufferStr;
    int convertedChars = 
      ::LCMapStringW(LOCALE_USER_DEFAULT, 
                     dwFlags, 
                     inStr.BeginReading(), 
                     inStr.Length(), 
                     bufferStr.BeginWriting(requiredBufferSize),
                     requiredBufferSize);

    NS_ENSURE_TRUE(convertedChars == requiredBufferSize, 
                   NS_ERROR_CANNOT_CONVERT_DATA);

    finalStr = bufferStr;
    inStr = bufferStr;
  }

  if(aTransformFlags & sbIStringTransform::TRANSFORM_IGNORE_NONSPACE ||
     aTransformFlags & sbIStringTransform::TRANSFORM_IGNORE_SYMBOLS ||
     aTransformFlags & sbIStringTransform::TRANSFORM_IGNORE_NONALPHANUM ||
     aTransformFlags & sbIStringTransform::TRANSFORM_IGNORE_NONALPHANUM_IGNORE_SPACE) {
    PRBool leadingOnly = aTransformFlags & 
                         sbIStringTransform::TRANSFORM_IGNORE_LEADING;
    PRBool bypassTest = PR_FALSE;
    LPWSTR wszJunk = {0};
    int requiredBufferSize = ::FoldStringW(MAP_COMPOSITE, 
                                           inStr.BeginReading(), 
                                           inStr.Length(), 
                                           wszJunk, 
                                           0);

    nsString bufferStr;
    int convertedChars = 
      ::FoldStringW(MAP_COMPOSITE, 
                    inStr.BeginReading(),
                    inStr.Length(),
                    bufferStr.BeginWriting(requiredBufferSize),
                    requiredBufferSize);

    NS_ENSURE_TRUE(convertedChars == requiredBufferSize,
                   NS_ERROR_CANNOT_CONVERT_DATA);

    LPWORD ct1 = new WORD[requiredBufferSize];
    BOOL success = GetStringTypeW(CT_CTYPE1,
                                  (LPWSTR) bufferStr.BeginReading(), 
                                  bufferStr.Length(), 
                                  &ct1[0]);

    if(!success) {
      delete [] ct1;
      _retval.Truncate();
      return NS_ERROR_CANNOT_CONVERT_DATA;
    }

    LPWORD ct2 = new WORD[requiredBufferSize];
    success = GetStringTypeW(CT_CTYPE2,
                             (LPWSTR) bufferStr.BeginReading(), 
                             bufferStr.Length(), 
                             &ct2[0]);

    if(!success) {
     delete [] ct1;
     delete [] ct2;
     _retval.Truncate();
     return NS_ERROR_CANNOT_CONVERT_DATA;
    }

    LPWORD ct3 = new WORD[requiredBufferSize];
    success = GetStringTypeW(CT_CTYPE3,
                             (LPWSTR) bufferStr.BeginReading(), 
                             bufferStr.Length(), 
                             &ct3[0]);

    if(!success) {
     delete [] ct1;
     delete [] ct2;
     delete [] ct3;
     _retval.Truncate();
     return NS_ERROR_CANNOT_CONVERT_DATA;
    }

    LPWORD charTypes[NTYPES] = {ct1, ct2, ct3};

    for(int current = 0; current < requiredBufferSize; ++current) {
      PRBool validChar = PR_TRUE;
      PRInt32 skipChars = 0;

      if (!bypassTest) {
        if (aTransformFlags & sbIStringTransform::TRANSFORM_IGNORE_KEEPNUMBERSYMBOLS) {
          PRInt32 numberLength;
          SB_ExtractLeadingNumber(bufferStr.BeginReading() + current, NULL, NULL, &numberLength);
          if (numberLength > 0) {
            finalStr.Append(bufferStr.BeginReading() + current, numberLength);
            current += numberLength-1;
            if (leadingOnly) {
              bypassTest = PR_TRUE;
            }
            continue;
          }
        }
        
        // first check if the char is excluded by any of its type flags
        for (int type = FIRSTTYPE; type <= LASTTYPE && validChar; type++) {
          PRUint32 excludeCharsLength = excludeChars[type].Length();
          for(PRUint32 invalid = 0; invalid < excludeCharsLength; ++invalid) {
            if(excludeChars[type][invalid] & charTypes[type][current]) {
              validChar = PR_FALSE;
              break;
            }
          }
        }
        // next, check if the char is in the included chars arrays. if all
        // arrays are empty, allow all chars instead of none
        PRBool found = PR_FALSE;
        PRBool testedAnything = PR_FALSE;
        for (int type = FIRSTTYPE; 
             type <= LASTTYPE && validChar && !found; 
             type++) {
          PRUint32 includeCharsLength = includeChars[type].Length();
          for(PRUint32 valid = 0; valid < includeCharsLength; ++valid) {
            testedAnything = PR_TRUE;
            if (includeChars[type][valid] & charTypes[type][current]) {
              found = PR_TRUE;
              break;
            }
          }
        }
        if (testedAnything && 
            !found) {
          validChar = PR_FALSE;    
        }
      }
            
      if(validChar) {
        if (leadingOnly) {
          bypassTest = PR_TRUE;
        }
        finalStr.Append(bufferStr.CharAt(current));
      }
      current += skipChars;
    }

    delete [] ct1;
    delete [] ct2;
    delete [] ct3;
  }

  _retval = finalStr;

  return NS_OK;
}