/* Reads the field info using SQLDescribeCol and creates
   a gsql_field with the descriptive information filled in. */
static gsql_field *
get_gsql_field_from_result (gsql_result *result, int colnum)
{
  gsql_field *gfield = (gsql_field *)xmalloc (sizeof (gsql_field));
  short colType;
  UDWORD colPrecision;
  short colScale;
  short colNullable;
  char colName[512];
  RETCODE status;

  colName[0] = '\000';

  initialize_gsql_field (gfield);

  /* Get column name */
  status = SQLDescribeCol
    (result->hstmt, colnum, (UCHAR *) colName,
     sizeof (colName), NULL, &colType, &colPrecision,
     &colScale, &colNullable);

  if (status != SQL_SUCCESS)
    {
      gsql_save_error_message (result->db, "SQLDescribeCol");
    }
  else
    {
#if defined (SQL_COLUMN_TABLE_NAME)
      char tablename[512];
      SWORD FAR tablename_len = 0;
      SDWORD FAR ignore_return = 0;

      status = SQLColAttributes
	(result->hstmt, colnum, SQL_COLUMN_TABLE_NAME,
	 (PTR)tablename, sizeof (tablename), &tablename_len, &ignore_return);

      if (status == SQL_SUCCESS)
	{
	  tablename[tablename_len] = '\0';
	  gfield->table = strdup (tablename);
	}
#endif /* SQL_COLUMN_TABLE_NAME */

      gfield->name = strdup (colName);
      gfield->type = colType;
      gfield->length = colPrecision;
      gfield->nullable = colNullable;
    }

  return (gfield);
}