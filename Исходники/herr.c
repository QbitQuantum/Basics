RETCODE SQL_API
SQLGetDiagField_Internal (
  SQLSMALLINT		  nHandleType,
  SQLHANDLE		  Handle,
  SQLSMALLINT		  nRecNumber,
  SQLSMALLINT		  nDiagIdentifier,
  SQLPOINTER		  pDiagInfoPtr,
  SQLSMALLINT		  nBufferLength,
  SQLSMALLINT		* pnStringLengthPtr,
  SQLCHAR		  waMode)
{
  GENV (genv, Handle);
  CONN (con, Handle);
  STMT (stmt, Handle);
  DESC (desc, Handle);
  HERR err;
  HPROC hproc = SQL_NULL_HPROC;
  RETCODE retcode = SQL_SUCCESS;
  SQLHANDLE dhandle = SQL_NULL_HANDLE;
  SWORD unicode_driver = 0;
  void *_DiagInfoPtr = NULL;
  void *diagInfoPtr = pDiagInfoPtr;


  switch (nHandleType)
    {
    case SQL_HANDLE_ENV:
      if (!IS_VALID_HENV (Handle))
	{
	  return SQL_INVALID_HANDLE;
	}
      err = genv->herr;
      con = NULL;
      stmt = NULL;
      desc = NULL;
      break;

    case SQL_HANDLE_DBC:
      if (!IS_VALID_HDBC (Handle))
	{
	  return SQL_INVALID_HANDLE;
	}
      err = con->herr;
      genv = (GENV_t *) con->genv;
      stmt = NULL;
      desc = NULL;
      dhandle = con->dhdbc;
      break;

    case SQL_HANDLE_STMT:
      if (!IS_VALID_HSTMT (Handle))
	{
	  return SQL_INVALID_HANDLE;
	}
      err = stmt->herr;
      con = (DBC_t *) stmt->hdbc;
      genv = (GENV_t *) con->genv;
      desc = NULL;
      dhandle = stmt->dhstmt;
      break;

    case SQL_HANDLE_DESC:
      if (!IS_VALID_HDESC (Handle))
	{
	  return SQL_INVALID_HANDLE;
	}
      err = desc->herr;
      stmt = (STMT_t *) desc->hstmt;
      con = (DBC_t *) desc->hdbc;
      genv = (GENV_t *) con->genv;
      dhandle = desc->dhdesc;
      break;

    default:
      return SQL_INVALID_HANDLE;
    }

  if (con != NULL && con->henv != SQL_NULL_HENV)
    unicode_driver = ((ENV_t *) con->henv)->unicode_driver;

  switch (nRecNumber)
    {

    case 0:			/* Header record */
      switch (nDiagIdentifier)
	{
	case SQL_DIAG_ROW_COUNT:
	  {
	    if (nHandleType != SQL_HANDLE_STMT || !stmt)
	      {
		return SQL_ERROR;
	      }

	    if (stmt->state != en_stmt_executed_with_info &&
	    	stmt->state != en_stmt_executed &&
		stmt->state != en_stmt_cursoropen)
	      {
		return SQL_ERROR;
	      }
	    if (!con)
	      {
		return SQL_INVALID_HANDLE;
	      }

            CALL_UDRIVER(con, stmt, retcode, hproc, unicode_driver, en_GetDiagField,
              (SQL_HANDLE_DBC, stmt->dhstmt, nRecNumber, nDiagIdentifier, 
               pDiagInfoPtr, nBufferLength, pnStringLengthPtr ));
            if (hproc == SQL_NULL_HPROC)
              {
		if (!con)
		  {
		    return SQL_INVALID_HANDLE;
		  }
		hproc = _iodbcdm_getproc (con, en_RowCount);
		if (!hproc)
		  {
		    return SQL_ERROR;
		  }
		CALL_DRIVER (stmt->hdbc, stmt, retcode, hproc,
		    (stmt->dhstmt, pDiagInfoPtr));
              }
	    return retcode;
	  }

	case SQL_DIAG_CURSOR_ROW_COUNT:
	case SQL_DIAG_DYNAMIC_FUNCTION:
	case SQL_DIAG_DYNAMIC_FUNCTION_CODE:

	  {
	    if (nHandleType != SQL_HANDLE_STMT || !stmt)
	      {
		return SQL_ERROR;
	      }

	    if (stmt->state != en_stmt_executed_with_info &&
	    	stmt->state != en_stmt_executed &&
		stmt->state != en_stmt_cursoropen)
	      {
		return SQL_ERROR;
	      }
	    if (!con)
	      {
		return SQL_INVALID_HANDLE;
	      }

            CALL_UDRIVER(con, stmt, retcode, hproc, unicode_driver, en_GetDiagField,
              (SQL_HANDLE_DBC, stmt->dhstmt, nRecNumber, nDiagIdentifier, 
               pDiagInfoPtr, nBufferLength, pnStringLengthPtr ));
            if (hproc == SQL_NULL_HPROC)
              return SQL_ERROR;
            else
	      return retcode;
	  }

	case SQL_DIAG_RETURNCODE:

	  if (pDiagInfoPtr)
	    *((SQLRETURN *) pDiagInfoPtr) = ((GENV_t *) Handle)->rc;
	  {
	    return SQL_SUCCESS;
	  }

	case SQL_DIAG_NUMBER:

	  if (pDiagInfoPtr)
	    {
	      (*(SQLINTEGER *) pDiagInfoPtr) = 0;
	      /* get the number from the driver */
	      if (con)
		{
                  CALL_UDRIVER(con, Handle, retcode, hproc, unicode_driver, en_GetDiagField,
                    (nHandleType, dhandle, 0, nDiagIdentifier, 
                     pDiagInfoPtr, nBufferLength, pnStringLengthPtr ));
                  if (hproc != SQL_NULL_HPROC)
                    {
		      if (retcode != SQL_SUCCESS)
			{
			  return retcode;
			}

		      /* and add the DM's value */
		      (*(SQLINTEGER *) pDiagInfoPtr) += error_rec_count (err);
                    }
		  else if (((ENV_t *) con->henv)->dodbc_ver == SQL_OV_ODBC2 &&
		      ((GENV_t *) Handle)->rc)
		    {		/* ODBC2 drivers can only have one error */
		      (*(SQLINTEGER *) pDiagInfoPtr) = 1;
		    }
		}
	      else if (genv)
		{
		  (*(SQLINTEGER *) pDiagInfoPtr) = error_rec_count (err);
		}

	    }
	  break;

	default:
	  return SQL_ERROR;
	}
      break;

    default:			/* status records */
      {
	int nRecs = 0;

	if (nRecNumber < 1)
	  {
	    return SQL_ERROR;
	  }
	nRecs = error_rec_count (err);
	if (nRecNumber <= nRecs)
	  {			/* DM Errors */
	    char *szval = "";
	    int ival = 0;
	    int isInt = 0;
	    sqlerr_t *rec = NULL;

	    rec = get_nth_error (err, nRecNumber - 1);

	    if (!rec)
	      {
		return (SQL_NO_DATA_FOUND);
	      }

	    switch (nDiagIdentifier)
	      {

	      case SQL_DIAG_SUBCLASS_ORIGIN:
	      case SQL_DIAG_CLASS_ORIGIN:
		isInt = 0;

		szval = (rec->code >= en_HY001
		    && rec->code <= en_IM014) ? (char *) "ODBC 3.0" : (char *) "ISO 9075";
		break;

	      case SQL_DIAG_COLUMN_NUMBER:

		if (nHandleType != SQL_HANDLE_STMT || !stmt)
		  {
		    return SQL_ERROR;
		  }
		if (!con)
		  {
		    return SQL_INVALID_HANDLE;
		  }

		if (pDiagInfoPtr)
		  *((SQLINTEGER *) pDiagInfoPtr) = SQL_COLUMN_NUMBER_UNKNOWN;

		return SQL_SUCCESS;

	      case SQL_DIAG_CONNECTION_NAME:
	      case SQL_DIAG_SERVER_NAME:

		isInt = 0;
		if (con)
		  {
		    if (waMode != 'W')
		       retcode = SQLGetInfo (con, SQL_DATA_SOURCE_NAME, 
		          pDiagInfoPtr,	nBufferLength, pnStringLengthPtr);
		    else
		       retcode = SQLGetInfoW (con, SQL_DATA_SOURCE_NAME, 
		          pDiagInfoPtr,	nBufferLength, pnStringLengthPtr);

		    return retcode;
		  }
		else
		  break;

	      case SQL_DIAG_MESSAGE_TEXT:

		isInt = 0;
		szval =
		    _iodbcdm_getsqlerrmsg (rec, (void *) sqlerrmsg_tab);
		break;

	      case SQL_DIAG_NATIVE:

		isInt = 1;
		ival = 0;
		break;

	      case SQL_DIAG_ROW_NUMBER:

		isInt = 1;
		if (nHandleType != SQL_HANDLE_STMT || !stmt)
		  {
		    return SQL_ERROR;
		  }
		if (!con)
		  {
		    return SQL_INVALID_HANDLE;
		  }
                CALL_UDRIVER(con, Handle, retcode, hproc, unicode_driver, en_GetDiagField,
                  (nHandleType, dhandle, nRecNumber, nDiagIdentifier, 
                   pDiagInfoPtr, nBufferLength, pnStringLengthPtr ));
               if (hproc != SQL_NULL_HPROC)
                 {
		    return retcode;
                 }
               else
                 {
		    ival = SQL_ROW_NUMBER_UNKNOWN;
		    break;
                 }

	      case SQL_DIAG_SQLSTATE:

		isInt = 0;
		szval = _iodbcdm_getsqlstate (rec, (void *) sqlerrmsg_tab);
		break;

	      default:
		return SQL_ERROR;
	      }
	    if (isInt)
	      {
		if (pDiagInfoPtr)
		  *((SQLINTEGER *) pDiagInfoPtr) = ival;
	      }
	    else
	      {
	        if (waMode != 'W')
	          {
		    int len = strlen (szval), len1;
		    len1 = len > nBufferLength ? nBufferLength : len;
		    if (pnStringLengthPtr)
		      *pnStringLengthPtr = len;
		    if (pDiagInfoPtr)
		      {
		        STRNCPY (pDiagInfoPtr, szval, len1);
		        *(((SQLCHAR *) pDiagInfoPtr) + len1) = 0;
		      }
		  }
		else
		  {
		    dm_StrCopyOut2_A2W((SQLCHAR *) szval, 
		    	(SQLWCHAR *) pDiagInfoPtr, nBufferLength, pnStringLengthPtr);
		  }
	      
	      }
	    break;
	  }
	else
	  {			/* Driver's errors */
	    nRecNumber -= nRecs;

	    if (!con)
	      {
		return SQL_NO_DATA_FOUND;
	      }

            if ((unicode_driver && waMode != 'W') 
                || (!unicode_driver && waMode == 'W'))
              {
                switch(nDiagIdentifier)
                  {
                  case SQL_DIAG_DYNAMIC_FUNCTION:
                  case SQL_DIAG_CLASS_ORIGIN:
                  case SQL_DIAG_CONNECTION_NAME:
                  case SQL_DIAG_MESSAGE_TEXT:
                  case SQL_DIAG_SERVER_NAME:
                  case SQL_DIAG_SQLSTATE:
                  case SQL_DIAG_SUBCLASS_ORIGIN:
                    if (waMode != 'W')
                      {
                      /* ansi=>unicode*/
                        if ((_DiagInfoPtr = malloc((nBufferLength + 1) * 
                               sizeof(wchar_t))) == NULL)
                          {
                            return SQL_ERROR;
                          }
                      }
                    else
                      {
                      /* unicode=>ansi*/
                        if ((_DiagInfoPtr = malloc(nBufferLength + 1)) == NULL)
                          {
                            return SQL_ERROR;
                          }
                      }
                    diagInfoPtr = _DiagInfoPtr;
                    break;
                  }
              }

            CALL_UDRIVER(con, Handle, retcode, hproc, unicode_driver, en_GetDiagField,
              (nHandleType, dhandle, nRecNumber, nDiagIdentifier, 
               diagInfoPtr, nBufferLength, pnStringLengthPtr ));
            if (hproc != SQL_NULL_HPROC)
              {
                if (pDiagInfoPtr
                    && SQL_SUCCEEDED (retcode)
                    && ((unicode_driver && waMode != 'W')
                        || (!unicode_driver && waMode == 'W')))
                  {
                    switch(nDiagIdentifier)
                      {
                      case SQL_DIAG_DYNAMIC_FUNCTION:
                      case SQL_DIAG_CLASS_ORIGIN:
                      case SQL_DIAG_CONNECTION_NAME:
                      case SQL_DIAG_MESSAGE_TEXT:
                      case SQL_DIAG_SERVER_NAME:
                      case SQL_DIAG_SQLSTATE:
                      case SQL_DIAG_SUBCLASS_ORIGIN:
                        if (waMode != 'W')
                          {
                          /* ansi<=unicode*/
                            dm_StrCopyOut2_W2A ((SQLWCHAR *) diagInfoPtr, 
				(SQLCHAR *) pDiagInfoPtr, 
				nBufferLength, pnStringLengthPtr);
                          }
                        else
                          {
                          /* unicode<=ansi*/
                            dm_StrCopyOut2_A2W ((SQLCHAR *)diagInfoPtr, 
			    	(SQLWCHAR *) pDiagInfoPtr, 
				nBufferLength, pnStringLengthPtr);
                          }
                      }
                  }

                MEM_FREE(_DiagInfoPtr);
		return retcode;
              }
            else
	      {			/* an ODBC2->ODBC3 translation */
		char *szval = "";
		wchar_t szState[6];
		SQLINTEGER nNative;

		if (nRecNumber > 1)
		  {
                    MEM_FREE(_DiagInfoPtr);
		    return SQL_NO_DATA_FOUND;
		  }

		if (nHandleType == SQL_HANDLE_DESC)
		  {
                    MEM_FREE(_DiagInfoPtr);
		    return SQL_INVALID_HANDLE;
		  }

		if (nDiagIdentifier != SQL_DIAG_MESSAGE_TEXT)
                   MEM_FREE(_DiagInfoPtr);

		switch (nDiagIdentifier)
		  {
		  case SQL_DIAG_SUBCLASS_ORIGIN:
		  case SQL_DIAG_CLASS_ORIGIN:
		    
		    CALL_UDRIVER (con, Handle, retcode, hproc, unicode_driver,
		      en_Error, (SQL_NULL_HENV,
		       nHandleType == SQL_HANDLE_DBC ? dhandle : SQL_NULL_HDBC,
		       nHandleType == SQL_HANDLE_STMT ? dhandle : SQL_NULL_HSTMT,
 		       szState, &nNative, NULL, 0, NULL));
                    if (hproc == SQL_NULL_HPROC)
                      {
		        return SQL_INVALID_HANDLE;
                      }
		    if (retcode != SQL_SUCCESS)
		      {
			return SQL_NO_DATA_FOUND;
		      }
		    if (waMode != 'W')
                      {
		        szval = !STRNEQ (szState, "IM", 2) ? (char *) "ODBC 3.0" : (char *) "ISO 9075";
                      }
		    else
                      {
                        if (szState[0] != L'I' && szState[1] != L'M')
		          szval = (char *) "ODBC 3.0";
                        else
		          szval = (char *) "ISO 9075";
                      }
		    break;

		  case SQL_DIAG_ROW_NUMBER:
		  case SQL_DIAG_COLUMN_NUMBER:
		    if (nHandleType != SQL_HANDLE_STMT || !stmt)
		      {
			return SQL_ERROR;
		      }
		    if (!con)
		      {
			return SQL_INVALID_HANDLE;
		      }
		    if (pDiagInfoPtr)
		      *((SQLINTEGER *) pDiagInfoPtr) =
			  SQL_COLUMN_NUMBER_UNKNOWN;
		    {
		      return SQL_SUCCESS;
		    }

		  case SQL_DIAG_SERVER_NAME:
		  case SQL_DIAG_CONNECTION_NAME:
		    break;

		  case SQL_DIAG_MESSAGE_TEXT:
		    CALL_UDRIVER (con, Handle, retcode, hproc, unicode_driver,
		      en_Error, (SQL_NULL_HENV,
		      nHandleType == SQL_HANDLE_DBC ? dhandle : SQL_NULL_HDBC,
		      nHandleType == SQL_HANDLE_STMT ? dhandle : SQL_NULL_HSTMT,
 		      szState, &nNative, diagInfoPtr, nBufferLength, 
 		      pnStringLengthPtr));
                    if (hproc == SQL_NULL_HPROC)
                      {
                        MEM_FREE(_DiagInfoPtr);
		        return SQL_INVALID_HANDLE;
                      }
                    if (pDiagInfoPtr
                        && SQL_SUCCEEDED (retcode)
                        && ((unicode_driver && waMode != 'W')
                            || (!unicode_driver && waMode == 'W')))
                      {
                        if (waMode != 'W')
                          {
                          /* ansi<=unicode*/
                            dm_StrCopyOut2_W2A ((SQLWCHAR *) diagInfoPtr, 
				(SQLCHAR *) pDiagInfoPtr, 
		      		nBufferLength, pnStringLengthPtr);
                          }
                        else
                          {
                          /* unicode<=ansi*/
                            dm_StrCopyOut2_A2W ((SQLCHAR *)diagInfoPtr, 
			    	(SQLWCHAR *) pDiagInfoPtr, 
				nBufferLength, pnStringLengthPtr);
                          }
                      }

                    MEM_FREE(_DiagInfoPtr);
		    return retcode;

		  case SQL_DIAG_NATIVE:
		    CALL_UDRIVER (con, Handle, retcode, hproc, unicode_driver,
		      en_Error, (SQL_NULL_HENV,
		      nHandleType == SQL_HANDLE_DBC ? dhandle : SQL_NULL_HDBC,
		      nHandleType == SQL_HANDLE_STMT ? dhandle : SQL_NULL_HSTMT,
 		      szState, &nNative, NULL, 0, NULL));
                    if (hproc == SQL_NULL_HPROC)
                      {
		        return SQL_INVALID_HANDLE;
                      }
		    if (pDiagInfoPtr)
		      *((SQLINTEGER *) pDiagInfoPtr) = nNative;
		    return retcode;

		  case SQL_DIAG_SQLSTATE:
		    CALL_UDRIVER (con, Handle, retcode, hproc, unicode_driver,
		      en_Error, (SQL_NULL_HENV,
		      nHandleType == SQL_HANDLE_DBC ? dhandle : SQL_NULL_HDBC,
		      nHandleType == SQL_HANDLE_STMT ? dhandle : SQL_NULL_HSTMT,
 		      szState, &nNative, NULL, 0, NULL));
                    if (hproc == SQL_NULL_HPROC)
                      {
		        return SQL_INVALID_HANDLE;
                      }
                    if (pDiagInfoPtr
                        && SQL_SUCCEEDED (retcode)
                        && ((unicode_driver && waMode != 'W')
                            || (!unicode_driver && waMode == 'W')))
                      {
                        if (waMode != 'W')
                          {
                          /* ansi<=unicode*/
                            dm_StrCopyOut2_W2A ((SQLWCHAR *) szState, 
				(SQLCHAR *) pDiagInfoPtr, 
		      		nBufferLength, pnStringLengthPtr);
                          }
                        else
                          {
                          /* unicode<=ansi*/
                            dm_StrCopyOut2_A2W ((SQLCHAR *)szState, 
			    	(SQLWCHAR *) pDiagInfoPtr, 
				nBufferLength, pnStringLengthPtr);
                          }
                      }

		    return retcode;

		  default:
		    return SQL_ERROR;
		  }

	        if (waMode != 'W')
	          {
		    if (pDiagInfoPtr)
		      {
		        int len = strlen (szval);
		        if (len > nBufferLength)
		          len = nBufferLength;
		        if (len)
		          _iodbcdm_strlcpy ((char *) pDiagInfoPtr, szval, len);
		      }
		    if (pnStringLengthPtr)
		      *pnStringLengthPtr = strlen (szval);
		  }
		else
		  {
		    dm_StrCopyOut2_A2W((SQLCHAR *) szval, 
		    	(SQLWCHAR *) pDiagInfoPtr, 
			nBufferLength, pnStringLengthPtr);
		  }
	      }			/* ODBC3->ODBC2 */
	  }			/* driver's errors */
      }				/* status records */
    }				/* switch (nRecNumber */
  return (SQL_SUCCESS);
}