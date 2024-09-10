BOOL PopFileRead (HWND hwndEdit, PTSTR pstrFileName)
{
     BYTE   bySwap ;
     DWORD  dwBytesRead ;
     HANDLE hFile ;
     int    i, iFileLength, iUniTest ;
     PBYTE  pBuffer, pText, pConv ;

          // Open the file.

     if (INVALID_HANDLE_VALUE == 
               (hFile = CreateFile (pstrFileName, GENERIC_READ, FILE_SHARE_READ,
                                    NULL, OPEN_EXISTING, 0, NULL)))
          return FALSE ;

          // Get file size in bytes and allocate memory for read.
          // Add an extra two bytes for zero termination.
                    
     iFileLength = GetFileSize (hFile, NULL) ; 
     pBuffer = malloc (iFileLength + 2) ;

          // Read file and put terminating zeros at end.
     
     ReadFile (hFile, pBuffer, iFileLength, &dwBytesRead, NULL) ;
     CloseHandle (hFile) ;
     pBuffer[iFileLength] = '\0' ;
     pBuffer[iFileLength + 1] = '\0' ;

          // Test to see if the text is Unicode

     iUniTest = IS_TEXT_UNICODE_SIGNATURE | IS_TEXT_UNICODE_REVERSE_SIGNATURE ;
     
     if (IsTextUnicode (pBuffer, iFileLength, &iUniTest))
     {
          pText = pBuffer + 2 ;
          iFileLength -= 2 ;

          if (iUniTest & IS_TEXT_UNICODE_REVERSE_SIGNATURE)
          {
               for (i = 0 ; i < iFileLength / 2 ; i++)
               {
                    bySwap = ((BYTE *) pText) [2 * i] ;
                    ((BYTE *) pText) [2 * i] = ((BYTE *) pText) [2 * i + 1] ;
                    ((BYTE *) pText) [2 * i + 1] = bySwap ;
               }
          }

               // Allocate memory for possibly converted string

          pConv = malloc (iFileLength + 2) ;

               // If the edit control is not Unicode, convert Unicode text to 
               // non-Unicode (ie, in general, wide character).

#ifndef UNICODE
          WideCharToMultiByte (CP_ACP, 0, (PWSTR) pText, -1, pConv, 
                               iFileLength + 2, NULL, NULL) ;

               // If the edit control is Unicode, just copy the string
#else
          lstrcpy ((PTSTR) pConv, (PTSTR) pText) ;
#endif

     }
     else      // the file is not Unicode
     {
          pText = pBuffer ;

               // Allocate memory for possibly converted string.

          pConv = malloc (2 * iFileLength + 2) ;

               // If the edit control is Unicode, convert ASCII text.

#ifdef UNICODE
          MultiByteToWideChar (CP_ACP, 0, pText, -1, (PTSTR) pConv, 
                               iFileLength + 1) ;

               // If not, just copy buffer
#else
          lstrcpy ((PTSTR) pConv, (PTSTR) pText) ;
#endif
     }
     
     SetWindowText (hwndEdit, (PTSTR) pConv) ;
     free (pBuffer) ;
     free (pConv) ;
   
     return TRUE ;
}