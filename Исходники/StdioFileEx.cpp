void CStdioFileEx::WriteWideString(LPCWSTR lpsz)
{
   ASSERT(lpsz != NULL);
   
   if (lpsz == NULL)
   {
      AfxThrowInvalidArgException();
   }
   if(m_bIsUnicodeText)
   {
      ASSERT(m_pStream != NULL);
      // If writing Unicode and at the start of the file, need to write byte mark
      if(GetPosition() == 0)
      {
         wchar_t cBOM = (wchar_t)UNICODE_BOM;
         CFile::Write(&cBOM, sizeof(wchar_t));
      }
      if (fputws(lpsz, m_pStream) == _TEOF)
         AfxThrowFileException(CFileException::diskFull, _doserrno, m_strFileName);
   }
   else
   {
      USES_CONVERSION;
      WriteAnsiString(CW2A(lpsz));
   }
}