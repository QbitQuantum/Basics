RETCODE SQL_API SQLParamData(
									 HSTMT hstmt,
									 PTR*  prgbValue)
{
	stmt_t*  pstmt = hstmt;
	int      ipar;
	param_t* ppar;
	fptr_t      cvt;
	char*    data;
	date_t      dt;

	UNSET_ERROR( pstmt->herr );

	ipar = pstmt->putipar;
	ppar = pstmt->ppar + ipar - 1;

	if ( ipar )
	{
		ppar->need = 0;
		pstmt->ndelay --;

		if ( ppar->ctype == SQL_C_CHAR )
		{
			if ( ! ppar->putdtbuf && ! ppar->putdtlen )
				data = 0;
			else
			{
				cvt = ppar->cvt;
				data= cvt(ppar->putdtbuf, ppar->putdtlen, &dt);
			}

			MEM_FREE( ppar->putdtbuf );
			ppar->putdtbuf = 0;
			ppar->putdtlen = 0;

			if ( data == (char*)(-1) )
			{
				PUSHSQLERR( pstmt->herr, en_S1000 );

				return SQL_ERROR;
			}

			sqlputdata( pstmt, ipar, data );
		}
	}

	if ( pstmt->ndelay )
	{
		for (ipar++, ppar++;;)
		{
			if ( ppar->need )
			{
				*prgbValue = (PTR)(ppar->userbuf);
				pstmt->putipar = ipar;

				return SQL_NEED_DATA;
			}
		}
	}

	if ( nnsql_execute(pstmt->yystmt) )
	{
		int   code;

		code = nnsql_errcode( pstmt->yystmt );

		if ( code == -1 )
			code = errno;

		PUSHSYSERR( pstmt->herr, code, nnsql_errmsg(pstmt->yystmt));

		return SQL_ERROR;
	}

	if ( ! nnsql_getcolnum(pstmt->yystmt)
		  && nnsql_getrowcount(pstmt->yystmt) > 1 )
	{
		PUSHSQLERR( pstmt->herr, en_01S04);

		return SQL_SUCCESS_WITH_INFO;
	}

	return SQL_SUCCESS;
}