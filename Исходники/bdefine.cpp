/* ****** Updated by CHENYH at 2004-4-9 10:06:44 ******
   增加pArrays： 为了能够接收处理多请求记录的情况
*/
int CallBDFunc(int fno,TRUSERID *handle,ST_CPACK *rpack,ST_PACK *pArrays,int *iRetCode, char *szMsg)
{
   int r=0;
   int rtn=0;
   int sendtype=0;
   char param[101]="";
#ifdef _DEBUG1
CMemoryState cm1, cm2, cm3;
#endif
   APPFUNC pFunc = g_BDefines[fno].pFunc;

#ifdef _DEBUG1
	cm1.Checkpoint();
#endif
	*iRetCode=0;
	*szMsg=0;
	//判断是否是结帐时刻,如果是则等待处理
	sendtype=rpack->head.RequestType/10000;
	switch(sendtype)
       {
		case 93:
		case 95:
			rtn = (*pFunc)(handle,rpack->head.RequestType,&rpack->pack,iRetCode,szMsg);
			break;
		default:
		 	rtn=GetSysParaVal(GLOBE_FLAG_BALANCE,param);
			if(rtn)
			{
				*iRetCode=rtn;
				break;
			}
			else if(strncmp(param,"0",1)!=0)
			{
				rtn=E_DAYEND_STATUS;
				*iRetCode=rtn;
				break;
			}
			rtn = (*pFunc)(handle,rpack->head.RequestType,&rpack->pack,iRetCode,szMsg);
	              break;
       }
	if(rtn)
	{
	   	char sErrMsg[101]="";
		char sRetMsg[256]="";
		if(*szMsg)
			snprintf(sRetMsg,256," %s",szMsg);
		r=get_errcode_msg(*iRetCode, sErrMsg);
		db_rollback();
		snprintf(szMsg,256,"%s%s",sErrMsg,sRetMsg);
		writelog(LOG_ERR,"Func[%d]ecode[%d]msg[%s]",rpack->head.RequestType,*iRetCode,szMsg);
		ERR_DEAL(szMsg,*iRetCode);
		if(r)
		{
			AnswerData(handle,*iRetCode,szMsg);
			db_disconnect();
			writelog(LOG_ERR,"数据库错误,系统退出");
			exit(1);
		}
	}
	else
	{
		r=db_commit();
		if(r)
		{
			*iRetCode=E_DB_COMMIT;
			strcpy(szMsg,"数据库事务提交失败");
			writelog(LOG_ERR,"Func[%d]Msg[%s]",rpack->head.RequestType,szMsg);
			db_rollback();
			ERR_DEAL( szMsg,*iRetCode);
		}
	}
#ifdef _DEBUG1
	cm2.Checkpoint();
	if (cm3.Difference(cm1, cm2))
   {
      BCCMsgLogOut(14444,"在执行功能号:%u时候，经检查，内存出现错误!",rpack->head.RequestType);
      g_LogFile.WriteLogEx(14444,"在执行功能号:%u时候，经检查，内存出现错误!",rpack->head.RequestType);
		cm3.DumpStatistics();
   }
#endif

   if (g_BUnit.m_SqlDB.lErrorCode<=-10000)  // 出现SQL比较严重的错误
   {
      if (SQLIsConnectOK()==0)
      {
         SQLDisconnect();
      }
      g_BUnit.m_SqlDB.lErrorCode = 0;
   }
   return(rtn);
}