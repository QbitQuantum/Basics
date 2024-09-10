//***********************************************************************
// FETCH ROWS FROM THE TABLE "T1"......select * from T1;
int FetchTest(SQLHANDLE env, SQLHANDLE dbc, SQLHANDLE stmt)
{
    
      int ret;
      int f1=10; // f1 field
      int f2=20;//f2 field

       int rettype ;

    ret = SQLPrepare(stmt,(unsigned char*)"SELECT F3,F2  FROM T1 ",SQL_NTS);
    rettype = ret;
    if(rettype!=0)return 1;

    //ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SMALL,SQL_SMALL,0,0,)
    ret = SQLBindCol(stmt,1,SQL_C_SLONG,&f1,0,NULL);
    
    
    
    ret = SQLBindCol(stmt,2,SQL_C_SLONG,&f2,0,NULL);
    



    int j, count=0; 
    
    ret = SQLExecute(stmt);
    
    SQLSMALLINT  noc;
    ret = SQLNumResultCols(stmt,&noc);
    rettype=ret;
    
    if(rettype != 0 )
    {
      printf("SQLNumResultCol() returns = %d\n",noc);
      return 1;
    }  
     
   while(SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        count++;
                
    }
    
    /*SQLSMALLINT noc;
    ret =SQLNumResultCols(stmt,&noc);
        
    printf("SQLNumResultCols() returns=%d\n",noc);*/
    
    ret = SQLCloseCursor(stmt);
    checkrc(ret,__LINE__);
    
    ret = SQLTransact(env,dbc,SQL_COMMIT);
    checkrc(ret,__LINE__);
    
    printf("Total row fetched=%d\n",count);
    return 0;
} 