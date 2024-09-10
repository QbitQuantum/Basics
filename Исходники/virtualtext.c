static int
vtxt_column (sqlite3_vtab_cursor * pCursor, sqlite3_context * pContext,
	     int column)
{
/* fetching value for the Nth column */
    int nCol = 1;
    int i;
    char buf[4096];
    int type;
    const char *value;
    VirtualTextCursorPtr cursor = (VirtualTextCursorPtr) pCursor;
    gaiaTextReaderPtr text = cursor->pVtab->reader;
    if (column == 0)
      {
	  /* the ROWNO column */
	  sqlite3_result_int (pContext, cursor->current_row);
	  return SQLITE_OK;
      }
    if (text->current_line_ready == 0)
	return SQLITE_ERROR;
    for (i = 0; i < text->max_fields; i++)
      {
	  if (nCol == column)
	    {
		if (!gaiaTextReaderFetchField (text, i, &type, &value))
		    sqlite3_result_null (pContext);
		else
		  {
		      if (type == VRTTXT_INTEGER)
			{
			    strcpy (buf, value);
			    text_clean_integer (buf);
#if defined(_WIN32) || defined(__MINGW32__)
/* CAVEAT - M$ runtime has non-standard functions for 64 bits */
			    sqlite3_result_int64 (pContext, _atoi64 (buf));
#else
			    sqlite3_result_int64 (pContext, atoll (buf));
#endif
			}
		      else if (type == VRTTXT_DOUBLE)
			{
			    strcpy (buf, value);
			    text_clean_double (buf);
			    sqlite3_result_double (pContext, atof (buf));
			}
		      else if (type == VRTTXT_TEXT)
			  sqlite3_result_text (pContext, value, strlen (value),
					       free);
		      else
			  sqlite3_result_null (pContext);
		  }
	    }
	  nCol++;
      }
    return SQLITE_OK;
}