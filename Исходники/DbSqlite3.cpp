BOOL CSqlite3Recordset::GetColumnName(short iIndex, LPTSTR pstrName, UINT cchMax)
{
   _ASSERTE(IsOpen());
   _ASSERTE(iIndex>=0 && iIndex<m_nCols);
   if( iIndex < 0 || iIndex >= m_nCols ) return FALSE;
   USES_CONVERSION;
   LPCSTR pstrSrc = m_lType == DB_OPEN_TYPE_FORWARD_ONLY ? ::sqlite3_column_name(m_pVm, iIndex) : m_ppSnapshot[iIndex];
   _tcsncpy(pstrName, A2CT(pstrSrc), cchMax);
   return TRUE;
}