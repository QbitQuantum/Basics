BOOL CCsvDatabase::_BindColumns()
{
   USES_CONVERSION;
   // Count number of columns
   LPCSTR p = m_pstrText;
   if( *p == ';' ) p++;  // Sometimes column-definition line starts with a ';'-char
   if( *p == '\r' || *p == '\n' || *p == ' ' ) return _Error(1, _T("Junk at start of file"));
   m_nCols = 1;
   m_cSep = ',';
   m_bFixedWidth = false;
   bool bInsideQuote = false;
   bool bWasSpace = false;
   while( *p != '\n' ) {
      // Look for a possible new separator
      if( *p == ';' && m_nCols == 1 ) m_cSep = *p;
      if( *p == '\0' ) return _Error(2, _T("EOF before columns were defined"));
      // So is this a column, then?
      if( !bInsideQuote && *p == m_cSep ) m_nCols++;
      // Skip skip skip
      if( *p == '\"' ) bInsideQuote = !bInsideQuote;
      p++;
      if( *p == '\n' && bInsideQuote ) return _Error(2, _T("Unclosed quotes in field definition"));
   }
   // Create columns array
   m_pColumns = new CCsvColumn[m_nCols];
   // Ready for new run where we populate the columns
   p = m_pstrText;
   if( *p == ';' ) p++;
   bInsideQuote = false;
   bWasSpace = false;
   int iField = 0;
   int iWidth = 0;
   LPCSTR pstrName = p;
   while( *p != '\n' ) {
      if( !bInsideQuote && *p == m_cSep ) {
         // Populate column information
         m_pColumns[iField].iSize = iWidth;
         m_pColumns[iField].lOffset = p - pstrName;
         // A space before the field-separator indicates fixed-width.
         // The "fixed width"-flag is global so we only need to see it once.
         if( bWasSpace ) {
            m_bFixedWidth = true;
            // Trim name as well
            while( iWidth > 0 && pstrName[iWidth - 1] == ' ' ) iWidth--;
         }
         _tcsncpy(m_pColumns[iField].szName, A2CT(pstrName), iWidth);
         // Prepare for next column
         pstrName = ++p;
         iWidth = 0;
         iField++;
      }
      if( *p == '\"' ) bInsideQuote = !bInsideQuote;
      if( bInsideQuote ) m_pColumns[iField].iType = VT_BSTR;
      bWasSpace = (*p == ' ');
      iWidth++;
      p++;
   }
   return TRUE;
}