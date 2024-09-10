  size_t CodePage2UnicodeConverter::convertToUnicode(UChar * pclTarget,
      size_t uiTargetMaxLength,
      const char * cpacSource,
      size_t uiSourceLength)
  /* ----------------------------------------------------------------------- */
  {
    size_t                     uiTargetSize;

    assert(iv_uconverter !=NULL);
    UErrorCode err=(UErrorCode)0;
    uiTargetSize = ucnv_toUChars(iv_uconverter, pclTarget, uiTargetMaxLength, cpacSource, uiSourceLength, &err);

    if (!U_SUCCESS(err) &&  err != U_BUFFER_OVERFLOW_ERROR) {
      cout << "ERROR: convertToUnicode " << err << endl;
      ///cerr << "CodePage2UnicodeConverter::getMaximumLength() rc= " << err << endl;
      ErrorMessage errMsg = ErrorMessage(UIMA_MSG_ID_CODEPAGE_CONV_ERROR);
      errMsg.addParam(err);
      UIMA_EXC_THROW_NEW(CodePageConversionException,
                         UIMA_ERR_CODEPAGE,
                         errMsg,
                         UIMA_MSG_ID_CODEPAGE_CONV_ERROR,
                         ErrorInfo::unrecoverable);
    }
    return uiTargetSize;
    //// return(uiTargetSize / sizeof(UChar));       /* as characters */
  }