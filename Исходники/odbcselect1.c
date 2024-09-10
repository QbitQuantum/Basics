//***********************************************************************
// FETCH ROWS FROM THE TABLE "T1"......select * from T1;
int FetchTest(SQLHANDLE env, SQLHANDLE dbc, SQLHANDLE stmt)
{
    
      int ret;
      int f1=10; // f1 field
      short int f2=20;//f2 field
      char f3[50]= "jitendra";
      float f4 = 2.5;
      float f5 = 10.50;
      int  f9 = 5;
      long long f10 = 15000;
      int result;


      SQL_DATE_STRUCT date;
      char strDate[30];

      date.year=2007;
      date.month=03;
      date.day=18;
     // strcpy(strDate,"{d '2008-03-18'}");
      //**********************************************
      SQL_TIME_STRUCT time;
      time.hour = 5;
      time.minute = 22;
      time.second = 10;
      //*********************************************
      SQL_TIMESTAMP_STRUCT timestamp;
      timestamp.year = 2007;
      timestamp.month = 03;
      timestamp.day = 18;
      timestamp.hour = 5;
      timestamp.minute = 22;
      timestamp.second = 10;
      

     ret = SQLPrepare(stmt,(unsigned char*)"SELECT * FROM T1",SQL_NTS);
     checkrc(ret,__LINE__);

    //ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SMALL,SQL_SMALL,0,0,)
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
    ret = SQLExecute(stmt);
    checkrc(ret,__LINE__);
    printf("Fetching starts on table  T1 :\n");
    
    while(SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        printf("F1=%d\tF2=%d\tF3=%s\tF4=%f\tF5=%f\tDATE=%d/%d/%d\tTIME=%d-%d-%d\tTIMESTAMP=%d/%d/%d %d-%d-%d\tF9=%d\tF10=%lld\n ",f1,f2,f3,f4,f5,date.year,date.month,date.day,time.hour,time.minute,time.second,timestamp.year,timestamp.month,timestamp.day,timestamp.hour,timestamp.minute,timestamp.second,f9,f10);


        count++;
           
    }
    
   
    
    ret = SQLCloseCursor(stmt);
    checkrc(ret,__LINE__);
    
    ret = SQLTransact(env,dbc,SQL_COMMIT);
    checkrc(ret,__LINE__);
    
    printf("Total row fetched=%d\n",count);
    return 0;
} 