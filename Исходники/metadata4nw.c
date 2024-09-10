int FetchTest(SQLHANDLE env, SQLHANDLE dbc, SQLHANDLE stmt)
{
    int ret;

    SQLCHAR szSchema[STR_LEN];
    SQLCHAR szCatalog[STR_LEN];
    SQLCHAR szColumnName[STR_LEN];
    SQLCHAR szTableName[STR_LEN];
    SQLCHAR szTypeName[STR_LEN];
    SQLCHAR szRemarks[REM_LEN];
    SQLCHAR szColumnDefault[STR_LEN];
    SQLCHAR szIsNullable[STR_LEN];

    SQLINTEGER ColumnSize;
    SQLINTEGER BufferLength;
    SQLINTEGER CharOctetLength;
    SQLINTEGER OrdinalPosition;

    SQLSMALLINT DataType;
    SQLSMALLINT DecimalDigits;
    SQLSMALLINT NumPrecRadix;
    SQLSMALLINT Nullable;
    SQLSMALLINT SQLDataType;
    SQLSMALLINT DatetimeSubtypeCode;

    ret = SQLColumns(stmt, (SQLCHAR*)"", SQL_NTS, (SQLCHAR*)"", SQL_NTS, (SQLCHAR*)"T1", SQL_NTS, NULL, 0);
    checkrc(ret,__LINE__);
    short totalFields = 0 ;
    ret = SQLNumResultCols (stmt, &totalFields);
    checkrc(ret,__LINE__);
    printf( "No of columns in resultset = %d\n",totalFields);


    SQLBindCol(stmt, 1, SQL_C_CHAR, szCatalog, STR_LEN,NULL);
    SQLBindCol(stmt, 2, SQL_C_CHAR, szSchema, STR_LEN, NULL);
    SQLBindCol(stmt, 3, SQL_C_CHAR, szTableName, STR_LEN,NULL);
    SQLBindCol(stmt, 4, SQL_C_CHAR, szColumnName, STR_LEN, NULL);
    SQLBindCol(stmt, 5, SQL_C_SSHORT, &DataType, 0, NULL);
    SQLBindCol(stmt, 6, SQL_C_CHAR, szTypeName, STR_LEN, NULL);
    SQLBindCol(stmt, 7, SQL_C_SLONG, &ColumnSize, 0, NULL);
    SQLBindCol(stmt, 8, SQL_C_SLONG, &BufferLength, 0, NULL);
    SQLBindCol(stmt, 9, SQL_C_SSHORT, &DecimalDigits, 0, NULL);
    SQLBindCol(stmt, 10, SQL_C_SSHORT, &NumPrecRadix, 0, NULL);
    SQLBindCol(stmt, 11, SQL_C_SSHORT, &Nullable, 0, NULL);
    SQLBindCol(stmt, 12, SQL_C_CHAR, szRemarks, REM_LEN, NULL);
    SQLBindCol(stmt, 13, SQL_C_CHAR, szColumnDefault, STR_LEN, NULL);
    SQLBindCol(stmt, 14, SQL_C_SSHORT, &SQLDataType, 0, NULL);
    SQLBindCol(stmt, 15, SQL_C_SSHORT, &DatetimeSubtypeCode, 0,NULL);
    SQLBindCol(stmt, 16, SQL_C_SLONG, &CharOctetLength, 0, NULL);
    SQLBindCol(stmt, 17, SQL_C_SLONG, &OrdinalPosition, 0, NULL);
    SQLBindCol(stmt, 18, SQL_C_CHAR, szIsNullable, STR_LEN, NULL);

    while(SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("szCatalog =%s \t szSchema=%s \t szTableName=%s \t szColumnName= %s \t DataType = %d ColumnSize = %d  Nullable =%d szRemarks = %s, OrdinalPosition =%d szIsNullable =%s\n ",szCatalog,szSchema,szTableName,szColumnName,DataType,ColumnSize,Nullable,szRemarks,OrdinalPosition,szIsNullable);
    }
    ret = SQLCloseCursor(stmt);
    checkrc(ret,__LINE__);

    ret = SQLTransact(env,dbc,SQL_COMMIT);
    checkrc(ret,__LINE__);
    return 0;
}