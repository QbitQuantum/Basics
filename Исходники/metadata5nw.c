int FetchTest(SQLHANDLE env, SQLHANDLE dbc, SQLHANDLE stmt,char *tablename)
{
      int ret;
      char f1[50]= "praba";
      char f2[50]= "praba";
      char f3[50]= "praba";
      char f4[50]= "praba";
      short f5;
      char f6[50]= "praba";

     ret = SQLPrimaryKeys(stmt, (SQLCHAR*)"", SQL_NTS, (SQLCHAR*)"", SQL_NTS, (SQLCHAR*)tablename,SQL_NTS);
     checkrc(ret,__LINE__);
    short totalFields=0;
    ret = SQLNumResultCols (stmt, &totalFields); 
    checkrc(ret,__LINE__);
    printf( "No of columns in resultset = %d\n",totalFields);

    ret = SQLBindCol(stmt,1,SQL_C_CHAR,f1,sizeof(f1),NULL);
    checkrc(ret,__LINE__);
    ret = SQLBindCol(stmt,2,SQL_C_CHAR,f2,sizeof(f2),NULL);
    checkrc(ret,__LINE__);
    ret = SQLBindCol(stmt,3,SQL_C_CHAR,f3,sizeof(f3),NULL);
    checkrc(ret,__LINE__);
    ret = SQLBindCol(stmt,4,SQL_C_CHAR,f4,sizeof(f4),NULL);
    checkrc(ret,__LINE__);
    SQLBindCol(stmt, 5, SQL_C_SHORT, &f5, 0, NULL);
    checkrc(ret,__LINE__);
    ret = SQLBindCol(stmt,6,SQL_C_CHAR,f6,sizeof(f6),NULL);
    checkrc(ret,__LINE__);
    while(SQL_SUCCEEDED(ret = SQLFetch(stmt))){
       printf("catalogName%s \t SchemaName=%s \t TableName=%s \t ColumnName = %s \t KEY_SEQ=%hd\t Primarykey = %s \n ",f1,f2,f3,f4,f5,f6);
  }
      ret = SQLCloseCursor(stmt);
      checkrc(ret,__LINE__);

    ret = SQLTransact(env,dbc,SQL_COMMIT);
       checkrc(ret,__LINE__);
    return 0;
}