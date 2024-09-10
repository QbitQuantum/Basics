//*************************************************************************
int  InsertTest(SQLHANDLE env,SQLHANDLE dbc,SQLHANDLE stmt)
{
         
      SQLRETURN  ret;
      int f1=0; // f1 field
      char f2[15]="jitendra";//f2 field
      SQLINTEGER slen=SQL_NTS;
      
      ret = SQLPrepare(stmt,(unsigned char*)"INSERT INTO T1 VALUES(?,?)",SQL_NTS);
      checkrc(ret,__LINE__);

      // BIND PARAMETER

      ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_LONG,SQL_INTEGER,0,0,&f1,0,NULL);
      checkrc(ret,__LINE__);

      ret = SQLBindParameter(stmt,2,SQL_PARAM_INPUT,SQL_C_CHAR,SQL_CHAR,196,0,(void*)f2,0,&slen);
      checkrc(ret,__LINE__);

    

      int i,count=0;
      for(i=0;i<1000;i++)
      {
         f1++;
         
         
         ret = SQLExecute(stmt);
         checkrc(ret,__LINE__);
        
         ret = SQLTransact(env,dbc,SQL_COMMIT);
         checkrc(ret,__LINE__);
         count++;
      } 
      printf("Total row inserted=%d\n",count);
      return 0;
  }