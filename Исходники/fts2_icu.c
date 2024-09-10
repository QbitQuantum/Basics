static int icuNext(
  sqlite3_tokenizer_cursor *pCursor,  
  const char **ppToken,               
  int *pnBytes,                       
  int *piStartOffset,                 
  int *piEndOffset,                   
  int *piPosition                     
){
  IcuCursor *pCsr = (IcuCursor *)pCursor;

  int iStart = 0;
  int iEnd = 0;
  int nByte = 0;

  while( iStart==iEnd ){
    UChar32 c;

    iStart = ubrk_current(pCsr->pIter);
    iEnd = ubrk_next(pCsr->pIter);
    if( iEnd==UBRK_DONE ){
      return SQLITE_DONE;
    }

    while( iStart<iEnd ){
      int iWhite = iStart;
      U16_NEXT(pCsr->aChar, iWhite, pCsr->nChar, c);
      if( u_isspace(c) ){
        iStart = iWhite;
      }else{
        break;
      }
    }
    assert(iStart<=iEnd);
  }

  do {
    UErrorCode status = U_ZERO_ERROR;
    if( nByte ){
      char *zNew = sqlite3_realloc(pCsr->zBuffer, nByte);
      if( !zNew ){
        return SQLITE_NOMEM;
      }
      pCsr->zBuffer = zNew;
      pCsr->nBuffer = nByte;
    }

    u_strToUTF8(
        pCsr->zBuffer, pCsr->nBuffer, &nByte,    
        &pCsr->aChar[iStart], iEnd-iStart,       
        &status                                  
    );
  } while( nByte>pCsr->nBuffer );

  *ppToken = pCsr->zBuffer;
  *pnBytes = nByte;
  *piStartOffset = pCsr->aOffset[iStart];
  *piEndOffset = pCsr->aOffset[iEnd];
  *piPosition = pCsr->iToken++;

  return SQLITE_OK;
}