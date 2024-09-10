int FetchTest(SQLHANDLE env, SQLHANDLE dbc, SQLHANDLE stmt)
{
    int ret;
    char f1[50]= "praba";
    char f2[50]= "praba";
    char f3[50]= "praba";
    char f4[50]= "praba";
    char f5[50]= "praba";

    ret = SQLTables(stmt, (SQLCHAR*)"csql", SQL_NTS, (SQLCHAR*)"csql", SQL_NTS, (SQLCHAR*)"", SQL_NTS, (SQLCHAR*)"Table", SQL_NTS );
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
    ret = SQLBindCol(stmt,5,SQL_C_CHAR,f5,sizeof(f5),NULL);
    checkrc(ret,__LINE__);
    while(SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("\tF1=%s \t F2=%s \t F3=%s \t F4= %s \t F5=%s \n ",f1,f2,f3,f4,f5);
    }
    ret = SQLCloseCursor(stmt);
    checkrc(ret,__LINE__);

    ret = SQLTransact(env,dbc,SQL_COMMIT);
    checkrc(ret,__LINE__);
    return 0;

}