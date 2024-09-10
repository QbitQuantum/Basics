int F250001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;

	char host[16]="";		//对方机器的ip
	short port=0;			
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	//char senddata[327]="";
	//char rcvdata[327]="";
	CTcpSocket tcpsocket ;
	ext_phone_trans_t  PhoneTrans;

	
	//memset(senddata,0x20,sizeof senddata);
	//memset(rcvdata,0x20,sizeof rcvdata);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SSECTYPES,0);

	des2src(host,rPack->scust_auth);
	port=rPack->lvol0;
	memset(&PhoneTrans,0,sizeof(PhoneTrans));
	memcpy(&PhoneTrans, rPack->ssectypes,127);
	memset(PhoneTrans.plugdata,0x20,sizeof(PhoneTrans.plugdata));
	memcpy(PhoneTrans.signcheck,gSignCheck,strlen(gSignCheck));
	
	//writelog(LOG_ERR,"package_send=[%s] ",rPack->ssectypes);
	writelog(LOG_INFO,"Connect to boss system ip_addr[%s],port[%d] ",host,port);	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to boss system error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		*pRetCode=E_MOBILE_TRANS_CONNECT;
		goto l_ret;
	}
	printf("send:[%s]\n",(char*)&PhoneTrans);
	ret = tcpsocket.Send((char*)&PhoneTrans,sizeof(PhoneTrans));
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
		writelog(LOG_ERR,"Send to boss system error,error code is [%d] ",ret);
		*pRetCode=E_MOBILE_TRANS_REQUEST;
		goto l_ret;
	}
	else if(0==ret){
		// 不应该出现这种情况
	      	writelog(LOG_ERR,"Send to boss system error，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		*pRetCode=E_MOBILE_TRANS_REQUEST;
	      	goto l_ret;
	}
	memset(&PhoneTrans,0,sizeof(PhoneTrans));
	if(rPack->lvol1==1)
	{
		ret = tcpsocket.Recv((char*)&PhoneTrans, sizeof(PhoneTrans), 15000);		
		tcpsocket.Close();
		if (ret!=327)
		{
			writelog(LOG_ERR,"Receive from boss system error,error code is [%d] ",ret);
			*pRetCode=E_MOBILE_TRANS_TIME_OUT;
			goto l_ret;  // 接收时候出错，或超时
		}
		printf("trans recv:[%s]\n",(char*)&PhoneTrans);
//		memcpy(out_pack->ssectypes,&PhoneTrans,127);
		if(strncmp(PhoneTrans.retnum,"00",2)!=0)
		{
			if(strncmp(PhoneTrans.retnum,"01",2)==0)
			{
				writelog(LOG_ERR,"trans error,mac error,ret[%s] ",PhoneTrans.retnum);
				*pRetCode=E_MOBILE_CHECK_MAC;
				goto l_ret;
			}
			if(strncmp(PhoneTrans.retnum,"02",2)==0)
			{
				writelog(LOG_ERR,"trans falied ret[%s] ",PhoneTrans.retnum);

				*pRetCode=E_MOBILE_TRANS_FAILURE;
				goto l_ret;
			}
		}
		else
		{
			writelog(LOG_INFO,"trans success ret[%s] ","00");
		}
	}else{
		ret=tcpsocket.Recv((char*)&PhoneTrans, sizeof(PhoneTrans), 15000);
		tcpsocket.Close();
		if (ret!=327)
		{
			writelog(LOG_ERR,"Receive from boss system error,error code is [%d] ",ret);
			*pRetCode=E_MOBILE_TRANS_TIME_OUT;
			goto l_ret;  // 接收时候出错，或超时
		}
		printf("query recv:[%s]\n",(char*)&PhoneTrans);	
//		memcpy(out_pack->ssectypes,&PhoneTrans,127);
		if(strncmp(PhoneTrans.retnum,"00",2)!=0)
		{
			if(strncmp(PhoneTrans.retnum,"01",2)==0)
			{
				writelog(LOG_ERR,"query error,mac error,ret[%s] ",PhoneTrans.retnum);
				*pRetCode=E_MOBILE_CHECK_MAC;
				goto l_ret;
			}
			if(strncmp(PhoneTrans.retnum,"02",2)==0)
			{
				writelog(LOG_ERR,"query falied ret[%s] ",PhoneTrans.retnum);
				*pRetCode=E_MOBILE_CHECK_FAIL;
				goto l_ret;
			}
		}
		else
		{
			writelog(LOG_INFO,"query success ret[%s] ","00");
		}
	}
	//writelog(LOG_ERR,"package_recv=[%s] ",out_pack->ssectypes);
			PutRow(handle,out_pack,pRetCode,szMsg);
			return 0;
l_ret:
	return -1;
}