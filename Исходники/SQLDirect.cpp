int CSQLDirect::GetColumnID( CString svField,CString svTable )
{
	UCHAR svColName[256];
	UCHAR ucOwner[256];
	SWORD swCol,swType,swScale,swNull;
	UDWORD pcbColDef;
	SDWORD wColLen;

	int nCol=1;

	// Get the total # of columns in this query.
	SQLColAttributes( m_hStmt,0,SQL_COLUMN_COUNT,ucOwner,256,&swScale,&wColLen );
	int nMaxCols=(int)wColLen;

	while( nCol<=nMaxCols ) {
		int nRet=SQLDescribeCol( m_hStmt,nCol,svColName,256,&swCol,&swType,&pcbColDef,&swScale,&swNull );
		SQLColAttributes( m_hStmt,nCol,SQL_COLUMN_TABLE_NAME,ucOwner,256,&swScale,&wColLen );

		// If we hit this condition, then our field is not in the dataset.
		if( nRet!=SQL_SUCCESS ) {
			nCol=0;
			break;
		}

		CString svName=svColName;
		CString svOwner=ucOwner;

		svName.TrimRight();
		svOwner.TrimRight();

		if( ( svName==svField ) ) {
			if(  !svTable.IsEmpty() ) {
				if( svOwner==svTable )
					break;
				else
					nCol++;
			}
			else
				break;
		}
		else
			nCol++;
	}

	return nCol;
}