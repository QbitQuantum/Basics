/* Get a new Tax ID given an old Tax ID from the merged node database */
Int4 DB_GetTaxMergedNodeRecNewTIDByOldTID(Int4 oldTaxId)
{
CharPtr search_mergeddb = "select new_taxid from seqhound.mergedtaxdb where old_taxid=?";
   SQLHANDLE hstmt;
   Int4 new_value = -1;
   Int2 sqlrc=SQL_SUCCESS;
   struct{
     Int4 len;
     Int4 val;
   }new_id;
 
   /* search merged db*/
   CreateHandle(&hstmt,search_mergeddb,&henv, &hdbc);

  SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG,SQL_INTEGER, 0, 0, &oldTaxId, 0, NULL);

  /* set auto commit on */
   SQLSetConnectAttr( hdbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, SQL_NTS);  

  /* execute statment */
  if (SQLExecute(hstmt) != SQL_SUCCESS){
	ErrPostEx(SEV_ERROR,0,0,"DB_GetTaxMergedNodeRecNewTIDByOldTID:unable to execute select statement.");
	print_err(hstmt);
	SQLFreeStmt(hstmt, SQL_DROP);
	return FALSE;
  }

  SQLBindCol(hstmt,1,SQL_C_LONG,&new_id.val,10,(long*)&new_id.len); 
 
  sqlrc = SQLFetch(hstmt);
  if(sqlrc == SQL_NO_DATA_FOUND){
    ErrPostEx(SEV_INFO, 0, 0, "Old Tax ID: %ld not found in Mergedtaxdb.", oldTaxId);
	return(-1);
  }
  else if(sqlrc == SQL_SUCCESS || sqlrc == SQL_SUCCESS_WITH_INFO){
    new_value = new_id.val; 
	}
  else{
    print_err(hstmt);
    return (-1);
  }

   /* Free statement handle. */
   if(SQLFreeStmt(hstmt, SQL_DROP) != SQL_SUCCESS){
     print_err(hstmt);
     return (-1);
   }
   return(new_value);

}