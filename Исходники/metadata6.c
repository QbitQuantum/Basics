int FetchTest(SQLHANDLE env, SQLHANDLE dbc, SQLHANDLE stmt,char *tablename)
{
      int ret;
      char f2[50]= "praba";
      SWORD                   f1;
      char f4[50]= "praba";
      SWORD                   f3;
      int f5;
      char f6[50]= "praba";

     ret = SQLStatistics(stmt, NULL, 0, NULL, SQL_NTS,
                    (SQLCHAR*) tablename, SQL_NTS, SQL_INDEX_ALL, SQL_QUICK);
 
     checkrc(ret,__LINE__);
    short totalFields=0;
    ret = SQLNumResultCols (stmt, &totalFields); 
    checkrc(ret,__LINE__);
    printf( "No of columns in resultset = %d\n",totalFields);

    ret = SQLBindCol(stmt,4,SQL_C_SHORT,(void*)&f1,0,NULL);
    checkrc(ret,__LINE__);
    ret = SQLBindCol(stmt,6,SQL_C_CHAR,f2,sizeof(f2),NULL);
    checkrc(ret,__LINE__);
    ret = SQLBindCol(stmt,7,SQL_C_SHORT,(void *)&f3,0,NULL);
    checkrc(ret,__LINE__);
    ret = SQLBindCol(stmt,9,SQL_C_CHAR,f4,sizeof(f4),NULL);
    checkrc(ret,__LINE__);
    while(SQL_SUCCEEDED(ret = SQLFetch(stmt))){
       printf(" Unique =%hd \tIndexName = %s \t Type=%hd ColumnName = %s \n ",f1,f2,f3,f4);
  }
      ret = SQLCloseCursor(stmt);
      checkrc(ret,__LINE__);

    ret = SQLTransact(env,dbc,SQL_COMMIT);
       checkrc(ret,__LINE__);
    return 0;
}