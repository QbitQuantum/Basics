/* ------------------------------------------------------------- */
PJXSQL jx_sqlOpen(PUCHAR sqlstmt , PJXNODE pSqlParms)
{

   PNPMPARMLISTADDRP pParms = _NPMPARMLISTADDR();
   // LONG    format   =  (pParms->OpDescList->NbrOfParms >= 3) ? formatP : 0;  // Status & result object

   LONG   attrParm;
   LONG   i;
//   PJXSQL pSQL = jx_sqlNewStatement (pParms->OpDescList->NbrOfParms >= 2 ? pSqlParms  :NULL);
   PJXSQL pSQL = jx_sqlNewStatement (NULL);

   pSQL->rc = SQLAllocStmt(pConnection->hdbc, &pSQL->hstmt);
   if (pSQL->rc != SQL_SUCCESS ) {
     check_error (pSQL);
     return NULL; // we have an error
   }

   attrParm = SQL_TRUE;
   pSQL->rc = SQLSetStmtAttr  (pSQL->hstmt, SQL_ATTR_CURSOR_SCROLLABLE , &attrParm  , 0);
   if (pSQL->rc != SQL_SUCCESS ) {
     check_error (pSQL);
     return NULL; // we have an error
   }

   /*
   attrParm = SQL_TRUE;
   pSQL->rc = SQLSetStmtAttr  (pSQL->hstmt, SQL_ATTR_EXTENDED_COL_INFO , &attrParm  , 0);
   if (pSQL->rc != SQL_SUCCESS ) {
     check_error (pSQL);
     return NULL; // we have an error
   }
   */

   attrParm = SQL_CONCUR_READ_ONLY;
   pSQL->rc = SQLSetStmtAttr  (pSQL->hstmt, SQL_ATTR_CONCURRENCY , &attrParm  , 0);
   if (pSQL->rc != SQL_SUCCESS ) {
     check_error (pSQL);
     return NULL; // we have an error
   }

   // run  the  statement in "sqlstr"
   if (pParms->OpDescList->NbrOfParms >= 2 && pSqlParms ) {
      UCHAR sqlTempStmt[32766];
      strFormat(sqlTempStmt , sqlstmt , pSqlParms);
      pSQL->sqlstmt = strdup(sqlTempStmt);
   } else {
      pSQL->sqlstmt = strdup(sqlstmt);
   }

   pSQL->rc = SQLExecDirect (pSQL->hstmt, pSQL->sqlstmt, SQL_NTS);

   if (pSQL->rc != SQL_SUCCESS && pSQL->rc != SQL_NO_DATA_FOUND) {
     check_error (pSQL);
     return NULL; // we have an error
   }


   // Number of rows? .. No does not work :(
   /*
   SQLGetDiagField(SQL_HANDLE_STMT,pSQL->hstmt, 0 ,SQL_DIAG_ROW_COUNT,&pSQL->rowcount,0, NULL);
   */

   /*
   // Row count is only affected row in a "delete" or "update" ..TODO find a solution for select
   pSQL->rc = SQLRowCount (pSQL->hstmt, &pSQL->rowcount);
   if (pSQL->rc != SQL_SUCCESS ) {
     check_error (pSQL);
     return; // we have an error
   }
   */

   pSQL->rc = SQLNumResultCols (pSQL->hstmt, &pSQL->nresultcols);
   if (pSQL->rc != SQL_SUCCESS ) {
      check_error (pSQL);
      return NULL; // we have an error
   }

   for (i = 0; i < pSQL->nresultcols; i++) {
      PJXCOL pCol = &pSQL->cols[i];

      SQLDescribeCol (pSQL->hstmt, i+1, pCol->colname, sizeof (pCol->colname),
          &pCol->colnamelen, &pCol->coltype, &pCol->collen, &pCol->scale, &pCol->nullable);

      pCol->colname[pCol->colnamelen] = '\0';

      if (OFF == jx_IsTrue (pConnection->pOptions ,"uppercasecolname")) {
         str2lower  (pCol->colname , pCol->colname);
      }

      // get display label  for column
      /****************
      pSQL->rc = SQLColAttributes (hstmt, i+1, SQL_DESC_LABEL, Label , sizeof(Label)  , &len , NULL);
      if (pSQL->rc != SQL_SUCCESS ) {
        check_error (pSQL);
        return; // we have an error
      }
      ***********/


      // get display length for column
      SQLColAttributes (pSQL->hstmt, i+1, SQL_DESC_PRECISION, NULL, 0,NULL, &pCol->displaysize);

      // set column length to max of display length, and column name
      //   length.  Plus one byte for null terminator
      // collen[i] = max(displaysize, collen[i]);
      // collen[i] = max(collen[i], strlen((char *) colname) ) + 1;

      // printf ("%-*.*s", collen[i], collen[i], colname);

      // allocate memory to bind column

      // bind columns to program vars, converting all types to CHAR
      //*SQLBindCol (hstmt, i+1, SQL_C_CHAR, data[i], collen[i], &outlen[i]);
      switch( pCol->coltype) {
         case SQL_BLOB:
         case SQL_CLOB:
 //           pCol->collen = pCol->displaysize * 2;
 //           pCol->data = (SQLCHAR *) malloc (pCol->collen);
            pCol->collen = 1048576;  // 1MEGABYTES
            pCol->data = (SQLCHAR *) malloc (pCol->collen);  // 1MEGABYTES
            SQLBindCol (pSQL->hstmt, i+1, SQL_C_BINARY , pCol->data, pCol->collen, &pCol->outlen);
            break;

         case SQL_WCHAR:
         case SQL_WVARCHAR:
         case SQL_GRAPHIC:
         case SQL_VARGRAPHIC:
            pCol->collen = pCol->displaysize * 2;
            pCol->data = (SQLCHAR *) malloc (pCol->collen);
            SQLBindCol (pSQL->hstmt, i+1, pCol->coltype, pCol->data, pCol->collen, &pCol->outlen);
            break;

         default:
            pCol->collen = pCol->displaysize + 3; // + . and , and zero term
            pCol->data = (SQLCHAR *) malloc (pCol->collen);
            SQLBindCol (pSQL->hstmt, i+1, SQL_C_CHAR, pCol->data, pCol->collen, &pCol->outlen);
            break;
      }
      if (pCol->coltype >= SQL_NUMERIC && pCol->coltype <= SQL_DOUBLE) {
         pCol->nodeType = JX_LITERAL;
      } else {
         pCol->nodeType = JX_VALUE;
      }
   }


   return pSQL;

}