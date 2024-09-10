//*************************************************************************
int  InsertTest(SQLHANDLE env,SQLHANDLE dbc,SQLHANDLE stmt)
{
         
      int ret;
      int f1=90; // f1 field
      int f2=20;//f2 field
 
      
      ret = SQLPrepare(stmt,(unsigned char*)"INSERT INTO T1 VALUES(?,?)",SQL_NTS);
      checkrc(ret,__LINE__);

      // BIND PARAMETER

      ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,0,0,&f1,0,NULL);
      checkrc(ret,__LINE__);

      ret = SQLBindParameter(stmt,2,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,0,0,&f2,0,NULL);
      checkrc(ret,__LINE__);

    

      int i,count=0;
      for(i=0;i<10;i++)
      {
         f1++;
         f2++;
         
         ret = SQLExecute(stmt);
         checkrc(ret,__LINE__);
        
         ret = SQLTransact(env,dbc,SQL_COMMIT);
         checkrc(ret,__LINE__);
         count++;
      } 
      printf("Total row inserted=%d\n",count);
      return 0;
  }