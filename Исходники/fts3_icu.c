/*
** Prepare to begin tokenizing a particular string.  The input
** string to be tokenized is pInput[0..nBytes-1].  A cursor
** used to incrementally tokenize this string is returned in 
** *ppCursor.
*/
static int icuOpen(
  sqlite3_tokenizer *pTokenizer,         /* The tokenizer */
  const char *zInput,                    /* Input string */
  int nInput,                            /* Length of zInput in bytes */
  sqlite3_tokenizer_cursor **ppCursor    /* OUT: Tokenization cursor */
){
  IcuTokenizer *p = (IcuTokenizer *)pTokenizer;
  IcuCursor *pCsr;

  const int32_t opt = U_FOLD_CASE_DEFAULT;
  UErrorCode status = U_ZERO_ERROR;
  int nChar;

  UChar32 c;
  int iInput = 0;
  int iOut = 0;

  *ppCursor = 0;

  if( nInput<0 ){
    nInput = strlen(zInput);
  }
  nChar = nInput+1;
  pCsr = (IcuCursor *)sqlite3_malloc(
      sizeof(IcuCursor) +                /* IcuCursor */
      nChar * sizeof(UChar) +            /* IcuCursor.aChar[] */
      (nChar+1) * sizeof(int)            /* IcuCursor.aOffset[] */
  );
  if( !pCsr ){
    return SQLITE_NOMEM;
  }
  memset(pCsr, 0, sizeof(IcuCursor));
  pCsr->aChar = (UChar *)&pCsr[1];
  pCsr->aOffset = (int *)&pCsr->aChar[nChar];

  pCsr->aOffset[iOut] = iInput;
  U8_NEXT(zInput, iInput, nInput, c); 
  while( c>0 ){
    int isError = 0;
    c = u_foldCase(c, opt);
    U16_APPEND(pCsr->aChar, iOut, nChar, c, isError);
    if( isError ){
      sqlite3_free(pCsr);
      return SQLITE_ERROR;
    }
    pCsr->aOffset[iOut] = iInput;

    if( iInput<nInput ){
      U8_NEXT(zInput, iInput, nInput, c);
    }else{
      c = 0;
    }
  }

  pCsr->pIter = ubrk_open(UBRK_WORD, p->zLocale, pCsr->aChar, iOut, &status);
  if( !U_SUCCESS(status) ){
    sqlite3_free(pCsr);
    return SQLITE_ERROR;
  }
  pCsr->nChar = iOut;

  ubrk_first(pCsr->pIter);
  *ppCursor = (sqlite3_tokenizer_cursor *)pCsr;
  return SQLITE_OK;
}