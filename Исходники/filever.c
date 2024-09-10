BOOL
VerpQueryValue16(
        const LPVOID pb,
        LPVOID lpSubBlockX,
        INT    nIndex,
        LPVOID *lplpKey,
        LPVOID *lplpBuffer,
        PUINT puLen,
        BOOL    bUnicodeNeeded
        )
{
   ANSI_STRING AnsiString;
   UNICODE_STRING UnicodeString;
   LPSTR lpSubBlock;
   LPSTR lpSubBlockOrg;
   NTSTATUS Status;

   VERBLOCK16 *pBlock = (VERBLOCK16*)pb;
   LPSTR lpStart, lpEndBlock, lpEndSubBlock;
   CHAR cTemp, cEndBlock;
   BOOL bLastSpec;
   DWORD dwHeadLen, dwTotBlockLen;
   INT  nCmp;

   BOOL bThunkNeeded;

  /*
   * If needs unicode, then we must thunk the input parameter
   * to ansi.  If it's ansi already, we make a copy so we can
   * modify it.
   */

   if (bUnicodeNeeded) {

      //
      // Thunk is not needed if lpSubBlockX == \VarFileInfo\Translation
      // or if lpSubBlockX == \
      //
      bThunkNeeded = (BOOL)((*(LPTSTR)lpSubBlockX != 0) &&
                            (lstrcmp(lpSubBlockX, TEXT("\\")) != 0) &&
                            (lstrcmpi(lpSubBlockX, szTrans) != 0));

      RtlInitUnicodeString(&UnicodeString, lpSubBlockX);
      Status = RtlUnicodeStringToAnsiString(&AnsiString, &UnicodeString, TRUE);

      if (!NT_SUCCESS(Status)) {
         SetLastError(Status);
         return FALSE;
      }
      lpSubBlock = AnsiString.Buffer;

   } else {
     lpSubBlockOrg = (LPSTR)LocalAlloc(LPTR,(lstrlenA(lpSubBlockX)+1)*sizeof(CHAR));
     if (lpSubBlockOrg == NULL ) {
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return FALSE;
     }
     lstrcpyA(lpSubBlockOrg,lpSubBlockX);
     lpSubBlock = lpSubBlockOrg;
   }

   *puLen = 0;

  /* Ensure that the total length is less than 32K but greater than the
   * size of a block header; we will assume that the size of pBlock is at
   * least the value of this first INT.
   */
  if ((INT)pBlock->wTotLen < sizeof(VERBLOCK16))
      goto Fail;

  /*
   * Put a '\0' at the end of the block so that none of the lstrlen's will
   * go past then end of the block.  We will replace it before returning.
   */
  lpEndBlock = ((LPSTR)pBlock) + pBlock->wTotLen - 1;
  cEndBlock = *lpEndBlock;
  *lpEndBlock = '\0';

  bLastSpec = FALSE;

#define NOTDONE() (*lpSubBlock || nIndex != -1)

  while (NOTDONE()) {
      //
      // Ignore leading '\\'s
      //
      while (*lpSubBlock == '\\')
          ++lpSubBlock;

      if (NOTDONE()) {
          /* Make sure we still have some of the block left to play with
           */
          dwTotBlockLen = lpEndBlock - ((LPSTR)pBlock) + 1;
          if ((INT)dwTotBlockLen<sizeof(VERBLOCK16) ||
             pBlock->wTotLen>dwTotBlockLen)

             goto NotFound;

          /* Calculate the length of the "header" (the two length WORDs plus
           * the identifying string) and skip past the value
           */

          dwHeadLen = sizeof(WORD)*2 + DWORDUP(lstrlenA(pBlock->szKey)+1)
                     + DWORDUP(pBlock->wValLen);

          if (dwHeadLen > pBlock->wTotLen)
              goto NotFound;
          lpEndSubBlock = ((LPSTR)pBlock) + pBlock->wTotLen;
          pBlock = (VERBLOCK16 FAR *)((LPSTR)pBlock+dwHeadLen);

          /* Look for the first sub-block name and terminate it
           */
          for (lpStart=lpSubBlock; *lpSubBlock && *lpSubBlock!='\\';
             lpSubBlock=CharNextA(lpSubBlock))
             /* find next '\\' */ ;
          cTemp = *lpSubBlock;
          *lpSubBlock = '\0';

          /* Continue while there are sub-blocks left
           * pBlock->wTotLen should always be a valid pointer here because
           * we have validated dwHeadLen above, and we validated the previous
           * value of pBlock->wTotLen before using it
           */

          nCmp = 1;
          while ((INT)pBlock->wTotLen>sizeof(VERBLOCK16) &&
             (INT)(lpEndSubBlock-((LPSTR)pBlock))>=(INT)pBlock->wTotLen) {

              //
              // Index functionality: if we are at the end of the path
              // (cTemp == 0 set below) and nIndex is NOT -1 (index search)
              // then break on nIndex zero.  Else do normal wscicmp.
              //
              if (bLastSpec && nIndex != -1) {

                  if (!nIndex) {

                      if (lplpKey) {
                          *lplpKey = pBlock->szKey;
                      }
                      nCmp=0;

                      //
                      // Index found, set nInde to -1
                      // so that we exit this loop
                      //
                      nIndex = -1;
                      break;
                  }

                  nIndex--;

              } else {

                  //
                  // Check if the sub-block name is what we are looking for
                  //

                  if (!(nCmp=lstrcmpiA(lpStart, pBlock->szKey)))
                      break;
              }

              /* Skip to the next sub-block
               */
              pBlock=(VERBLOCK16 FAR *)((LPSTR)pBlock+DWORDUP(pBlock->wTotLen));
          }

          /* Restore the char NULLed above and return failure if the sub-block
           * was not found
           */
          *lpSubBlock = cTemp;
          if (nCmp)
              goto NotFound;
        }
        bLastSpec = !cTemp;
    }

  /* Fill in the appropriate buffers and return success
   */
  *puLen = pBlock->wValLen;

  *lplpBuffer = (LPSTR)pBlock + 4 + DWORDUP(lstrlenA(pBlock->szKey) + 1);

  //
  // Shouldn't need zero-length value check since win31 compatible.
  //

  *lpEndBlock = cEndBlock;

  /*
   * Must free string we allocated above
   */

  if (bUnicodeNeeded) {
     RtlFreeAnsiString(&AnsiString);
  } else {
     LocalFree(lpSubBlockOrg);
  }


  /*----------------------------------------------------------------------
   * thunk the results
   *
   * Must always thunk key, always ??? value
   *
   * We have no way of knowing if the resource info is binary or strings
   * Version stuff is usually string info, so thunk.
   *
   * The best we can do is assume that everything is a string UNLESS
   * we are looking at \VarFileInfo\Translation or at \.
   *
   * This is acceptable because the documenation of VerQueryValue
   * indicates that this is used only for strings (except these cases.)
   *----------------------------------------------------------------------*/

  if (bUnicodeNeeded) {

      //
      // Do thunk only if we aren't looking for \VarFileInfo\Translation or \
      //
      if (bThunkNeeded) {

         AnsiString.Length = AnsiString.MaximumLength = (SHORT)*puLen;
         AnsiString.Buffer = *lplpBuffer;

         //
         // Do the string conversion in the second half of the buffer
         // Assumes wTotLen is first filed in VERHEAD
         //
         UnicodeString.Buffer = (LPWSTR)((PBYTE)pb + DWORDUP(*((WORD*)pb)) +
             (DWORD)((PBYTE)*lplpBuffer - (PBYTE)pb)*2);

         UnicodeString.MaximumLength = (SHORT)((*puLen+1) * sizeof(WCHAR));
         RtlAnsiStringToUnicodeString(&UnicodeString, &AnsiString, FALSE);

         *lplpBuffer = UnicodeString.Buffer;
      }

      if (lplpKey) {

         //
         // Thunk the key
         //

         dwHeadLen = lstrlenA(*lplpKey);
         AnsiString.Length = AnsiString.MaximumLength = (SHORT)dwHeadLen;
         AnsiString.Buffer = *lplpKey;

         UnicodeString.Buffer = (LPWSTR) ((PBYTE)pb + DWORDUP(*((WORD*)pb)) +
            (DWORD)((PBYTE)*lplpKey - (PBYTE)pb)*2);

         UnicodeString.MaximumLength = (SHORT)((dwHeadLen+1) * sizeof(WCHAR));
         RtlAnsiStringToUnicodeString(&UnicodeString, &AnsiString, FALSE);

         *lplpKey = UnicodeString.Buffer;
     }
  }

  return(TRUE);



NotFound:

  /* Restore the char we NULLed above
   */
  *lpEndBlock = cEndBlock;

Fail:

  if (bUnicodeNeeded) {
     RtlFreeAnsiString(&AnsiString);
  } else {
     LocalFree(lpSubBlockOrg);
  }

  return(FALSE);
}