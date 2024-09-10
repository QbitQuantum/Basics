void MakeRtnData(void * pConn,long reqno, unsigned long funcid, long errcode,const char * errInfo , const char * retbuf, long len,bool islast)
{
	tagTradeErrorInfo *pErrInfo = new tagTradeErrorInfo();
	pErrInfo->ErrorID = 0;
	void * datahandle = NULL;
	int iRowCount = 0;
	if (errcode >= 0)
	{
		datahandle = YTData_NewData();
		YTData_ConvertData(datahandle, retbuf, len);
		iRowCount = YTData_GetRowCount(datahandle);
		if (iRowCount > 0)
		{
			YTData_GotoBeginRow(datahandle);
			pErrInfo->ErrorID = YTData_GetFieldInt(datahandle,"retcode");
			if (pErrInfo->ErrorID < 0)
			{
				YTData_GetFieldString(datahandle,"comment",pErrInfo->ErrorMsg,sizeof(pErrInfo->ErrorMsg));
			}
		}
	}
	else
	{
		pErrInfo->ErrorID = errcode;
		strcpy_s(pErrInfo->ErrorMsg, sizeof(pErrInfo->ErrorMsg), errInfo);
	}

	int i = 0;
	switch(funcid)
	{
	case LOGIN:
		if (errcode < 0 || pErrInfo->ErrorID < 0)  
		{
			pFuncList->Func_TradeAnsLogin(NULL,pErrInfo);
			
		}
		else  //正常返回
		{
			tagTradeAnsLogin* pPara = new tagTradeAnsLogin();
			pPara->UserID = YTData_GetFieldInt(datahandle,"userid");
			pPara->UserType = YTData_GetFieldInt(datahandle,"usertype");
			iUserID = pPara->UserID;

			//登陆成功之后，初始化连接池。连接池开始有maxconn/2 个连接
      void* conn = pConn;  
      EnterCriticalSection(&secLock); 
      //for(int k=0;k<imaxConnects/2;k++)  
      //{ 
      //  conn = YTConn_NewConn(ptrConfig);
      //  if (YTConn_Connect(conn) >=0)
      //  {
      //    connLists.push_back(conn);
      //    iCurConnects++;
      //  }
      //}  
      connLists.push_back(conn);
      iCurConnects++;
      LeaveCriticalSection(&secLock);  
      if(iCurConnects >= imaxConnects/2){ 
			  pFuncList->Func_TradeAnsLogin(pPara,pErrInfo);
      }
			delete pPara;			
		}
		break;
	case QURELATED:
		if (errcode < 0 || pErrInfo->ErrorID < 0)  
		{
			pFuncList->Func_TradeAnsQuRelated(NULL,0,pErrInfo,reqno,islast);

		}
		else  //正常返回
		{
			iRowCount = YTData_GetRowCount(datahandle); 
			tagTradeAnsQuRelated* pPara = new tagTradeAnsQuRelated[iRowCount];
			for (i=0;i<iRowCount;i++)
			{
				pPara[i].UserID = YTData_GetFieldInt(datahandle,"userid");
				YTData_GetFieldString(datahandle,"user",pPara[i].User,sizeof(pPara[i].User));
				pPara[i].AccID = YTData_GetFieldInt(datahandle,"accountid");
				YTData_GetFieldString(datahandle,"accountalias",pPara[i].AccountName,sizeof(pPara[i].AccountName));
				pPara[i].CounterID = YTData_GetFieldInt(datahandle,"counterid");
				pPara[i].UsableMoney = YTData_GetFieldDouble(datahandle,"usablemoney");
			}
			pFuncList->Func_TradeAnsQuRelated(pPara,iRowCount,pErrInfo,reqno,islast);
			delete []pPara;
		}
		break;
	case QUMONEY:
		if (errcode < 0 || pErrInfo->ErrorID < 0)  
		{
			pFuncList->Func_TradeAnsQuMoney(NULL,0,pErrInfo,reqno,islast);

		}
		else  //正常返回
		{
			iRowCount = YTData_GetRowCount(datahandle); 
			tagTradeAnsQuMoney* pPara = new tagTradeAnsQuMoney[iRowCount];
			for (i=0;i<iRowCount;i++)
			{
				pPara[i].UsableMoney = YTData_GetFieldDouble(datahandle,"usablemoney");
			}
			pFuncList->Func_TradeAnsQuMoney(pPara,iRowCount,pErrInfo,reqno,islast);
			delete []pPara;
		}
		break;
	case QUAMOUNT:
		if (errcode < 0 || pErrInfo->ErrorID < 0)  
		{
			pFuncList->Func_TradeAnsQuAmount(NULL,0,pErrInfo,reqno,islast);

		}
		else  //正常返回
		{
			iRowCount = YTData_GetRowCount(datahandle); 
			tagTradeAnsQuAmount* pPara = new tagTradeAnsQuAmount[iRowCount];
			for (i=0;i<iRowCount;i++)
			{

				pPara[i].AccID = YTData_GetFieldInt(datahandle,"accountid");
				YTData_GetFieldString(datahandle,"accountalias",pPara[i].AccountName,sizeof(pPara[i].AccountName));
				pPara[i].Amount = YTData_GetFieldInt(datahandle,"stockamount");
				YTData_GetFieldString(datahandle,"symbol",pPara[i].InstrumentID,sizeof(pPara[i].InstrumentID));
				YTData_GetFieldString(datahandle,"exchange",pPara[i].ExchangeID,sizeof(pPara[i].ExchangeID));
				YTData_GetFieldString(datahandle,"cname",pPara[i].InstrumentName,sizeof(pPara[i].InstrumentName));
			}
			pFuncList->Func_TradeAnsQuAmount(pPara,iRowCount,pErrInfo,reqno,islast);
			delete []pPara;
		}
		break;
	case QUUNFINISHENTRUST:
		if (errcode < 0 || pErrInfo->ErrorID < 0)  
		{
			pFuncList->Func_TradeAnsQuUnFinishEntrust(NULL,0,pErrInfo,reqno,islast);

		}
		else  //正常返回
		{
			iRowCount = YTData_GetRowCount(datahandle); 
			tagTradeAnsQuUnFinishEntrust* pPara = new tagTradeAnsQuUnFinishEntrust[iRowCount];
			for (i=0;i<iRowCount;i++)
			{
				pPara[i].UserID = YTData_GetFieldInt(datahandle,"userid");
				YTData_GetFieldString(datahandle,"user",pPara[i].User,sizeof(pPara[i].User));
				pPara[i].AccID = YTData_GetFieldInt(datahandle,"accountid");
				YTData_GetFieldString(datahandle,"accountalias",pPara[i].AccountName,sizeof(pPara[i].AccountName));
				pPara[i].CounterID = YTData_GetFieldInt(datahandle,"counterid");
				YTData_GetFieldString(datahandle,"symbol",pPara[i].InstrumentID,sizeof(pPara[i].InstrumentID));
				YTData_GetFieldString(datahandle,"exchange",pPara[i].ExchangeID,sizeof(pPara[i].ExchangeID));
				YTData_GetFieldString(datahandle,"cname",pPara[i].InstrumentName,sizeof(pPara[i].InstrumentName));
				pPara[i].EntrustDate = YTData_GetFieldInt(datahandle,"entrustdate");
				pPara[i].EntrustTime = YTData_GetFieldInt(datahandle,"entrusttime");
				pPara[i].EntrustType = YTData_GetFieldChar(datahandle,"entrusttype");
				pPara[i].EntrustStatus = YTData_GetFieldChar(datahandle,"entruststatus");
				YTData_GetFieldString(datahandle,"entrustno",pPara[i].EntrustNo,sizeof(pPara[i].EntrustNo));
				pPara[i].EntrustPrice = YTData_GetFieldDouble(datahandle,"entrustprice");
				pPara[i].EntrustAmount = YTData_GetFieldInt(datahandle,"entrustamount");
				pPara[i].BargAmount = YTData_GetFieldInt(datahandle,"stockturnover");
				pPara[i].LastUpdateTime = YTData_GetFieldInt(datahandle,"lasttime");
			}
			pFuncList->Func_TradeAnsQuUnFinishEntrust(pPara,iRowCount,pErrInfo,reqno,islast);
			delete []pPara;
		}
		break;
	case QULOG:
		if (errcode < 0 || pErrInfo->ErrorID < 0)  
		{
			pFuncList->Func_TradeAnsQuLog(NULL,0,pErrInfo,reqno,islast);

		}
		else  //正常返回
		{
			iRowCount = YTData_GetRowCount(datahandle); 
			tagTradeAnsQuLog* pPara = new tagTradeAnsQuLog[iRowCount];
			for (i=0;i<iRowCount;i++)
			{
				pPara[i].UserID = YTData_GetFieldInt(datahandle,"userid");
				YTData_GetFieldString(datahandle,"user",pPara[i].User,sizeof(pPara[i].User));
				pPara[i].AccID = YTData_GetFieldInt(datahandle,"accountid");
				YTData_GetFieldString(datahandle,"accountalias",pPara[i].AccountName,sizeof(pPara[i].AccountName));
				YTData_GetFieldString(datahandle,"symbol",pPara[i].InstrumentID,sizeof(pPara[i].InstrumentID));
				YTData_GetFieldString(datahandle,"cname",pPara[i].InstrumentName,sizeof(pPara[i].InstrumentName));
				pPara[i].EntrustDate = YTData_GetFieldInt(datahandle,"entrustdate");
				pPara[i].EntrustTime = YTData_GetFieldInt(datahandle,"entrusttime");
				pPara[i].EntrustStatus = YTData_GetFieldChar(datahandle,"entruststatus");
				YTData_GetFieldString(datahandle,"entrustno",pPara[i].EntrustNo,sizeof(pPara[i].EntrustNo));
				YTData_GetFieldString(datahandle,"event",pPara[i].LogDetail,sizeof(pPara[i].LogDetail));
				pPara[i].Index = YTData_GetFieldInt(datahandle,"qryindex");
			}
			pFuncList->Func_TradeAnsQuLog(pPara,iRowCount,pErrInfo,reqno,islast);
			delete []pPara;
		}
		break;
	case QUPOSITION:
		if (errcode < 0 || pErrInfo->ErrorID < 0)  
		{
			pFuncList->Func_TradeAnsQuPosition(NULL,0,pErrInfo,reqno,islast);

		}
		else  //正常返回
		{
			iRowCount = YTData_GetRowCount(datahandle); 
			tagTradeAnsQuPosition* pPara = new tagTradeAnsQuPosition[iRowCount];
			for (i=0;i<iRowCount;i++)
			{
				if (i==0)
				{
					pPara[i].TotalMarketValue = YTData_GetFieldDouble(datahandle,"totalmarketvalue");
					pPara[i].FloatProfitorLoss = YTData_GetFieldDouble(datahandle,"floatprofitorloss");
					pPara[i].AchieveFpl = YTData_GetFieldDouble(datahandle,"achievefpl");
				}
				YTData_GetFieldString(datahandle,"user",pPara[i].User,sizeof(pPara[i].User));
				YTData_GetFieldString(datahandle,"accountalias",pPara[i].AccountName,sizeof(pPara[i].AccountName));
				YTData_GetFieldString(datahandle,"symbol",pPara[i].InstrumentID,sizeof(pPara[i].InstrumentID));
				YTData_GetFieldString(datahandle,"cname",pPara[i].InstrumentName,sizeof(pPara[i].InstrumentName));
				YTData_GetFieldString(datahandle,"exchange",pPara[i].ExchangeID,sizeof(pPara[i].ExchangeID));
				pPara[i].Amount = YTData_GetFieldInt(datahandle,"stockamount");
				pPara[i].Side = YTData_GetFieldInt(datahandle,"side");
				pPara[i].CurrentFloatProfit = YTData_GetFieldDouble(datahandle,"currentfloatprofit");
				pPara[i].AveragePrice = YTData_GetFieldDouble(datahandle,"averageprice");
			}
			pFuncList->Func_TradeAnsQuPosition(pPara,iRowCount,pErrInfo,reqno,islast);
			delete []pPara;
		}
		break;
	case QUBARGAIN:
		if (errcode < 0 || pErrInfo->ErrorID < 0)  
		{
			pFuncList->Func_TradeAnsQuBargain(NULL,0,pErrInfo,reqno,islast);

		}
		else  //正常返回
		{
			iRowCount = YTData_GetRowCount(datahandle); 
			tagTradeAnsQuBargain* pPara = new tagTradeAnsQuBargain[iRowCount];
			for (i=0;i<iRowCount;i++)
			{
				pPara[i].UserID = YTData_GetFieldInt(datahandle,"userid");
				YTData_GetFieldString(datahandle,"user",pPara[i].User,sizeof(pPara[i].User));
				pPara[i].AccID = YTData_GetFieldInt(datahandle,"accountid");
				YTData_GetFieldString(datahandle,"accountalias",pPara[i].AccountName,sizeof(pPara[i].AccountName));
				YTData_GetFieldString(datahandle,"symbol",pPara[i].InstrumentID,sizeof(pPara[i].InstrumentID));
				YTData_GetFieldString(datahandle,"cname",pPara[i].InstrumentName,sizeof(pPara[i].InstrumentName));
				pPara[i].EntrustType = YTData_GetFieldChar(datahandle,"entrusttype");
				pPara[i].EntrustTime = YTData_GetFieldInt(datahandle,"entrusttime");
				YTData_GetFieldString(datahandle,"entrustno",pPara[i].EntrustNo,sizeof(pPara[i].EntrustNo));
				pPara[i].BargAmount = YTData_GetFieldInt(datahandle,"stockturnover");
				pPara[i].BargPrice = YTData_GetFieldDouble(datahandle,"bargainprice");
				pPara[i].EntrustFee = YTData_GetFieldChar(datahandle,"entrustfee");
			}
			pFuncList->Func_TradeAnsQuBargain(pPara,iRowCount,pErrInfo,reqno,islast);
			delete []pPara;
		}
		break;
	case QUCOLLECTBARGAIN:
		if (errcode < 0 || pErrInfo->ErrorID < 0)  
		{
			pFuncList->Func_TradeAnsQuCollectBargain(NULL,0,pErrInfo,reqno,islast);

		}
		else  //正常返回
		{
			iRowCount = YTData_GetRowCount(datahandle); 
			tagTradeAnsQuCollectBargain* pPara = new tagTradeAnsQuCollectBargain[iRowCount];
			for (i=0;i<iRowCount;i++)
			{
				if (i == 0)
				{
					pPara[i].AchieveFpl = YTData_GetFieldDouble(datahandle,"achievefpl");
					pPara[i].TotalTradeMoney = YTData_GetFieldDouble(datahandle,"totaltrademoney");
				}
				pPara[i].UserID = YTData_GetFieldInt(datahandle,"userid");
				YTData_GetFieldString(datahandle,"accountalias",pPara[i].AccountName,sizeof(pPara[i].AccountName));
				YTData_GetFieldString(datahandle,"symbol",pPara[i].InstrumentID,sizeof(pPara[i].InstrumentID));
				YTData_GetFieldString(datahandle,"cname",pPara[i].InstrumentName,sizeof(pPara[i].InstrumentName));
				pPara[i].BargAmount = YTData_GetFieldInt(datahandle,"stockturnover");
				pPara[i].EntrustCount = YTData_GetFieldInt(datahandle,"entrustcount");
				pPara[i].BargMoney = YTData_GetFieldDouble(datahandle,"priceturnover");
				pPara[i].Profits = YTData_GetFieldDouble(datahandle,"profits");
				pPara[i].EntrustFee = YTData_GetFieldChar(datahandle,"entrustfee");
			}
			pFuncList->Func_TradeAnsQuCollectBargain(pPara,iRowCount,pErrInfo,reqno,islast);
			delete []pPara;
		}
		break;
	case ENTRUST:
		pFuncList->Func_TradeAnsEntrust(pErrInfo,reqno);
		break;
	case DISENTRUST:
		pFuncList->Func_TradeAnsDisEntrust(pErrInfo,reqno);
		break;
	case  DISLASTENTRUST:
		pFuncList->Func_TradeAnsDisLastEntrust(pErrInfo,reqno);
		break;
	case DISALLENTRUST:
		pFuncList->Func_TradeAnsDisAllEntrust(pErrInfo,reqno);
		break;
	default:
		break;
	}

	YTData_DeleteData(datahandle);
	delete pErrInfo;
}