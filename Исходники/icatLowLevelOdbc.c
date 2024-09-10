/*
 Bind variables from the global array.
 */
int
bindTheVariables(HSTMT myHstmt, char *sql) {
   int myBindVarCount;
   RETCODE stat;
   int i;
   char tmpStr[TMP_STR_LEN+2];

   myBindVarCount = cllBindVarCount;
   cllBindVarCountPrev=cllBindVarCount; /* save in case we need to log error */
   cllBindVarCount = 0; /* reset for next call */

   if (myBindVarCount > 0) {
      rodsLogSql("SQLPrepare");
      stat = SQLPrepare(myHstmt,  (unsigned char *)sql, SQL_NTS);
      if (stat != SQL_SUCCESS) {
	 rodsLog(LOG_ERROR, "bindTheVariables: SQLPrepare failed: %d",
		 stat);
	 return(-1);
      }

      for (i=0;i<myBindVarCount;i++) {
	 stat = SQLBindParameter(myHstmt, i+1, SQL_PARAM_INPUT, SQL_C_CHAR,
				 SQL_C_CHAR, 0, 0, cllBindVars[i], 0, 0);
	 snprintf(tmpStr, TMP_STR_LEN, "bindVar[%d]=%s", i+1, cllBindVars[i]);
	 rodsLogSql(tmpStr);
	 if (stat != SQL_SUCCESS) {
	    rodsLog(LOG_ERROR, 
		    "bindTheVariables: SQLBindParameter failed: %d", stat);
	    return(-1);
	 }
      }

      if (stat != SQL_SUCCESS) {
	 rodsLog(LOG_ERROR, "bindTheVariables: SQLAllocStmt failed: %d",
		 stat);
	 return(-1);
      }
   }
   return(0);
}