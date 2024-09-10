int main()
{
  SQLHENV env;
  SQLHDBC dbc;
  SQLHSTMT stmt;
  SQLRETURN ret;
  SQLCHAR outstr[1024];
  SQLSMALLINT outstrlen;
  
  // Aloocate an environment handle
  ret=SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&env);
  checkrc(ret,__LINE__);
  
   //we need odbc3 support
   ret =SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(void*)SQL_OV_ODBC3,0);
   checkrc(ret,__LINE__);
  //ALLOCATE A Connection handle
  ret = SQLAllocHandle(SQL_HANDLE_DBC,env,&dbc);
  checkrc(ret,__LINE__);
    
  // connect to the DSN mydsn
   ret = SQLConnect (dbc,
                   (SQLCHAR *) "DSN=mycsql;MODE=csql;SERVER=127.0.0.1;PORT=5678;", (SQLSMALLINT) strlen ("DSN=mycsql;MODE=csql;SERVER=127.0.0.1;PORT=5678;"),
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));

  if(SQL_SUCCEEDED(ret))
  {
     printf("\nConnected to the Data Source..\n");
       
     
  }
   else
   {
        printf("error in connection\n");
        ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
        checkrc(ret,__LINE__);

        ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
        checkrc(ret,__LINE__); 
        return 1;
   }

   ret = SQLSetConnectAttr(dbc,SQL_ATTR_AUTOCOMMIT,(void*)SQL_AUTOCOMMIT_OFF,SQL_IS_UINTEGER);
   checkrc(ret,__LINE__);
   //******************************************************************
   // TABLE CREATED
   ret = SQLAllocHandle(SQL_HANDLE_STMT,dbc,&stmt);
   checkrc(ret,__LINE__);
   
   SQLCHAR table[200]=
     "CREATE TABLE T1(F1 INT,F2 INT);";
   ret = SQLPrepare(stmt,table,SQL_NTS);
   checkrc(ret,__LINE__);
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
   SQLFreeStmt(stmt, SQL_CLOSE);
   
   printf("\nTABLE CREATED\n"); 
   //****************************************************************
    ret = SQLPrepare(stmt,(unsigned char*)"INSERT INTO T1 VALUES(1,1);",SQL_NTS);
    checkrc(ret,__LINE__);
    ret = SQLExecute(stmt);
    checkrc(ret,__LINE__);
    
    SQLFreeStmt(stmt, SQL_CLOSE);
    ret = SQLEndTran(SQL_HANDLE_DBC,dbc,SQL_COMMIT);
    if(ret!=SQL_SUCCESS && ret !=SQL_SUCCESS_WITH_INFO)
    printf("error in commit\n");
   //InsertTest(env,dbc,stmt);  
   //*****************************************************************
    
    //update
    ret = SQLPrepare(stmt,(unsigned char*)"UPDATE T1 SET F2=100;",SQL_NTS);
    checkrc(ret,__LINE__);
    ret = SQLExecute(stmt);
    checkrc(ret,__LINE__);
    SQLFreeStmt(stmt, SQL_CLOSE);
    ret = SQLEndTran(SQL_HANDLE_DBC,dbc,SQL_COMMIT);
    if(ret!=SQL_SUCCESS && ret !=SQL_SUCCESS_WITH_INFO)
    printf("error in commit\n");
    checkrc(ret,__LINE__);
   //***********************************************************
     //FETCH
    FetchTest(env,dbc,stmt);

   //****************************************************************      
   ret = SQLExecDirect(stmt,(unsigned char*)"DROP TABLE T1",SQL_NTS);
   checkrc(ret,__LINE__);
   SQLFreeStmt(stmt, SQL_CLOSE);
   printf("Table T1 dropped\n");

   ret = SQLFreeHandle(SQL_HANDLE_STMT,stmt);
   checkrc(ret,__LINE__);

   ret = SQLDisconnect(dbc);
   checkrc(ret,__LINE__);
   
   ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
   checkrc(ret,__LINE__);
   
   ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
   checkrc(ret,__LINE__);
   return 0;
}         