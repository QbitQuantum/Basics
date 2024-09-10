void
StatementObject::GetProcedures(const NPVariant *arg0, const NPVariant *arg1, 
	const NPVariant *arg2)
{
  NPString *cat = NULL;
  NPString *sch = NULL; 
  NPString *prc = NULL;

  if (NPVARIANT_IS_STRING(*arg0))
    cat = (NPString*)&NPVARIANT_TO_STRING(*arg0);
  if (NPVARIANT_IS_STRING(*arg1))
    sch = (NPString*)&NPVARIANT_TO_STRING(*arg1);
  if (NPVARIANT_IS_STRING(*arg2))
    prc = (NPString*)&NPVARIANT_TO_STRING(*arg2);

  if (!m_hstmt) {
    NPN_SetException(this, "Statement isn't initialized");
    return;
  }

  NPError rc = Close();
  if (rc != NPERR_NO_ERROR)
    return;

  SQLRETURN code = SQLProceduresW(m_hstmt, 
  	(cat?nsWString(cat).Data():NULL), (cat?SQL_NTS:0),
  	(sch?nsWString(sch).Data():NULL), (sch?SQL_NTS:0),
  	(prc?nsWString(prc).Data():NULL), (prc?SQL_NTS:0));
  if (!SQL_SUCCEEDED(code) && code != SQL_NO_DATA) {
    StoreError(SQL_HANDLE_STMT, m_hstmt);  
    return;
  } 
    
  SQLSMALLINT cols;
  if (SQL_SUCCEEDED(SQLNumResultCols(m_hstmt, &cols)))
    m_columnCount = cols;

  SQLLEN rcnt;
  if (SQL_SUCCEEDED(SQLRowCount(m_hstmt, &rcnt)))
    m_rowCount = rcnt;
}