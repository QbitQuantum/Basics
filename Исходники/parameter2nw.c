//***********************************************************************
// FETCH ROWS FROM THE TABLE "T1"......select * from T1;
int FetchTest(SQLHANDLE env, SQLHANDLE dbc, SQLHANDLE stmt)
{
    
      int ret;
      int f1=10; // f1 field
      short int f2=20;//f2 field
      char f3[50]= "praba";
      float f4 = 2.5;
      float f5 = 10.50;
      int f9=5;
      long long f10=15000;
      SQLINTEGER slen = SQL_NTS;
      SQL_DATE_STRUCT  date,f6Date;
      SQL_TIME_STRUCT  time, f7Time;
      SQL_TIMESTAMP_STRUCT  timestamp, f8Timestamp;
      
      date.year=2008;
      date.month=03;
      date.day=18;

      time.hour=5;
      time.minute=22;
      time.second=10;

      timestamp.year=2008;
      timestamp.month=03;
      timestamp.day=18;
      timestamp.hour=5; 
      timestamp.minute = 22;
      timestamp.second = 10;
      timestamp.fraction = 764576;
      
       int f1temp,f2temp;
       char f3temp[20];
       float f4temp, f5temp;
       
       int f9temp;
       long long f10temp;
       
     ret = SQLPrepare(stmt,(unsigned char*)"SELECT *  FROM T1 WHERE F1=? AND F2=? AND F3=? AND F4=? AND F5=? AND F6=? AND F7=? AND F8=? AND F9=? AND F10=?",SQL_NTS);
     checkrc(ret,__LINE__);

    //ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SMALL,SQL_SMALL,0,0,)
    ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,0,0,&f1temp,0,NULL);
    checkrc(ret,__LINE__);
    
    ret = SQLBindParameter(stmt,2,SQL_PARAM_INPUT,SQL_C_SSHORT,SQL_INTEGER,0,0,&f2temp,0,NULL);
    checkrc(ret,__LINE__);
    
    ret =  SQLBindParameter(stmt,3,SQL_PARAM_INPUT,SQL_C_CHAR,SQL_CHAR,196,0,(void*)f3temp,0,&slen);
    checkrc(ret,__LINE__);
    
    ret = SQLBindParameter(stmt,4,SQL_PARAM_INPUT,SQL_C_FLOAT,SQL_FLOAT,0,0,&f4temp,0,NULL);
    checkrc(ret,__LINE__);
   
    ret = SQLBindParameter(stmt,5,SQL_PARAM_INPUT,SQL_C_FLOAT,SQL_REAL,0,0,&f5temp,0,NULL);
    checkrc(ret,__LINE__);
   
    ret = SQLBindParameter(stmt,6,SQL_PARAM_INPUT,SQL_C_TYPE_DATE,SQL_TYPE_DATE,196,0,&f6Date,sizeof(f6Date),&slen);
    checkrc(ret,__LINE__);

    ret = SQLBindParameter(stmt,7,SQL_PARAM_INPUT,SQL_C_TYPE_TIME,SQL_TYPE_TIME,196,0,&f7Time,sizeof(f7Time),&slen); 
    checkrc(ret,__LINE__);
   
    ret = SQLBindParameter(stmt,8,SQL_PARAM_INPUT,SQL_C_TYPE_TIMESTAMP,SQL_TYPE_TIMESTAMP,196,0,&f8Timestamp,sizeof(f8Timestamp),&slen);
    checkrc(ret,__LINE__);

    ret = SQLBindParameter(stmt,9,SQL_PARAM_INPUT,SQL_C_TINYINT,SQL_TINYINT,0,0,&f9temp,0,NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindParameter(stmt,10,SQL_PARAM_INPUT,SQL_C_SBIGINT,SQL_BIGINT,0,0,&f10temp,0,NULL);
    checkrc(ret,__LINE__);
    //*******************************************************************************************************

    ret = SQLBindCol(stmt,1,SQL_C_SLONG,&f1,0,NULL);
    checkrc(ret,__LINE__);
    
    ret = SQLBindCol(stmt,2,SQL_C_SSHORT,&f2,0,NULL);
    checkrc(ret,__LINE__);


    ret = SQLBindCol(stmt,3,SQL_C_CHAR,f3,sizeof(f3),NULL);
    checkrc(ret,__LINE__);
 
    ret = SQLBindCol(stmt,4,SQL_C_FLOAT,&f4,0,NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,5,SQL_C_FLOAT,&f5,0,NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,6,SQL_C_TYPE_DATE,&date,sizeof(date),NULL);
    checkrc(ret,__LINE__);
 
    ret = SQLBindCol(stmt,7,SQL_C_TYPE_TIME,&time,sizeof(time),NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,8,SQL_C_TYPE_TIMESTAMP,&timestamp,sizeof(timestamp),NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,9,SQL_C_TINYINT,&f9,0,NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,10,SQL_C_SBIGINT,&f10,0,NULL);
    checkrc(ret,__LINE__);

    int j, count=0;
   
    
    
    f6Date=date;
    f7Time=time;
    f8Timestamp=timestamp;
    for(j=0;j<10;j++)
    {
      f1temp=f1++;
      f2temp=f2++;
      strcpy(f3temp,"praba");
      f4temp=f4++;
      f5temp=f5;
      f9temp=f9;
      f10temp=f10;
      
      ret = SQLExecute(stmt);
      checkrc(ret,__LINE__);
      ret = SQLFetch(stmt);
      ret = SQLCloseCursor(stmt);
      checkrc(ret,__LINE__);
      count++;
      
       printf("F1=%d\tF2=%d\tF3=%s\tF4=%f\tF5=%f\tDATE=%d/%d/%d\tTIME=%d-%d-%d\tTIMESTAMP=%d/%d/%d %d-%d-%d\tF9=%d\tF10=%lld\n ",f1,f2,f3,f4,f5,date.year,date.month,date.day,time.hour,time.minute,time.second,timestamp.year,timestamp.month,timestamp.day,timestamp.hour,timestamp.minute,timestamp.second,f9,f10);

 
  }
        
    ret = SQLTransact(env,dbc,SQL_COMMIT);
    checkrc(ret,__LINE__);
    
    printf("Total row fetched=%d\n",count);
    return 0;
} 