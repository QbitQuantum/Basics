UINT Enconn::ConnectThread(LPVOID pParam)//接收线程
{		
	int rcvLen = 0;
	int nDataLen = 0;
	int recvedlen =0;
	char pData[256] = {0};	 
	unsigned char msgcmd=0;
		IPicture   *pPic;     
	IStream   *pStm;
				
	HGLOBAL hMem;
	LPVOID lpBuf;
	HDC			hdc;
	HWND		hwnd;
	MSGHEAD head;

	CString finename;
	int pptindex=0;
	Enconn* pEnconn = (Enconn*) pParam;


	pEnconn->m_hSocket = socket(AF_INET,SOCK_STREAM,0);	
	struct sockaddr_in        client_addr;
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr(pEnconn->m_pAddr);
	client_addr.sin_port = htons(PORT);
	int nSize = 4000;
	pEnconn->PostMessage(RM_ST_CONNING,0);//给窗体发送消息
	setsockopt(pEnconn->m_hSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&nSize ,sizeof(nSize));	//设置socket接收超时,4秒钟
	if(connect(pEnconn->m_hSocket, (LPSOCKADDR)&client_addr, sizeof(client_addr)) != 0)
	{	
		pEnconn->PostMessage(RM_ST_FAIL,NULL);	
		closesocket(pEnconn->m_hSocket);
		pEnconn->m_hSocket=0;		
		return 0;
	}
	pEnconn->Connflag=1;
	pEnconn->PostMessage(RM_ST_SUCCESS,0);
	if(pEnconn->Enctype==1)//ENC1200
	{
		pEnconn->PackHeaderMSG((BYTE *)pData, MSG_PASSWORD, (HEAD_LEN+1+_tcslen(pEnconn->m_pPassword)));
		pData[HEAD_LEN]='A';//表示管理员	
		WideCharToMultiByte(CP_ACP,NULL,pEnconn->m_pPassword,_tcslen(pEnconn->m_pPassword),&pData[HEAD_LEN+1],8,NULL,FALSE);
		rcvLen=pEnconn->Send((char*)pData,HEAD_LEN+1+_tcslen(pEnconn->m_pPassword));//发送密码
	}
	else//ENC110
	{
		*(short*)(&pData)=htons(4+_tcslen(pEnconn->m_pPassword));
		pData[2]=MSG_PASSWORD;
		pData[3]='A';//表示管理员	
		WideCharToMultiByte(CP_ACP,NULL,pEnconn->m_pPassword,_tcslen(pEnconn->m_pPassword),&pData[4],8,NULL,FALSE);
		rcvLen=pEnconn->Send((char*)pData,4+_tcslen(pEnconn->m_pPassword));//发送密码
	}
	if(rcvLen==-1)goto Exit;
	while(pEnconn->m_hSocket>0)
	{
		int nn = GetTickCount();
		if(pEnconn->Enctype==1)//ENC1200
		{
			rcvLen=pEnconn->Recv((char*)pEnconn->m_cVideoBuffer, HEAD_LEN);//接收编码器的数据
		}
		else//ENC110
		{
			rcvLen=pEnconn->Recv((char*)pEnconn->m_cVideoBuffer, 2);//接收编码器的数据
		}
		
		if(rcvLen == -1)
		{
			goto Exit;
		}		
		if(pEnconn->Enctype==1)//ENC1200
		{
			memcpy(&head,(pEnconn->m_cVideoBuffer),HEAD_LEN);	
			nDataLen=ntohs(head.nLen)-HEAD_LEN;
			if(nDataLen < 0)goto Exit;
			rcvLen=pEnconn->Recv((char*)pEnconn->m_cVideoBuffer, nDataLen);		
			msgcmd=head.nMsg;

		}
		else//ENC110
		{
			nDataLen=htons(*((unsigned short*)(pEnconn->m_cVideoBuffer)))-2;	
			if(nDataLen < 1)goto Exit;
			rcvLen=pEnconn->Recv((char*)pEnconn->m_cVideoBuffer, nDataLen);		
			msgcmd=pEnconn->m_cVideoBuffer[0];

		}
			
		if(rcvLen == -1)
		{
			goto Exit;
		}			
		switch(msgcmd) 
		{
		case MSG_CONNECTSUCC:				
			(pEnconn->m_RichEdit)->SetWindowTextW(_T("链接成功"));
			break;
		case MSG_PASSWORD_ERR:	
			pEnconn->PostMessage(RM_PASSWD_ERR,NULL);	
			(pEnconn->m_RichEdit)->SetWindowTextW(_T("密码错误"));
			break;
		case MSG_MAXCLIENT_ERR:				
			(pEnconn->m_RichEdit)->SetSel(-1,-1);
			(pEnconn->m_RichEdit)->ReplaceSel(_T("最大客户数\n"),0);
			break;
		case MSG_SCREENDATA:	
			//(pEnconn->m_RichEdit)->SetSel(-1,-1);
			//(pEnconn->m_RichEdit)->ReplaceSel(_T("h264 Data\n"),0);		
			//(pEnconn->m_RichEdit)->SetWindowTextW(_T("h264"));
			//printf("Recv h264 Data\n");
			
			if(pEnconn->saveStream==1)
			{
				if(pEnconn->Enctype==1)//ENC1200
					pEnconn->H264File.Write((char*)pEnconn->m_cVideoBuffer+sizeof(FRAMEHEAD),nDataLen-sizeof(FRAMEHEAD));
				else
					pEnconn->H264File.Write((char*)pEnconn->m_cVideoBuffer+1+sizeof(DataHeader),nDataLen-1-sizeof(DataHeader));
					
			}
			break;
		case MSG_AUDIODATA:							
			//(pEnconn->m_RichEdit)->SetSel(-1,-1);
			//(pEnconn->m_RichEdit)->ReplaceSel(_T("AAC Data\n"),0);
			//printf("Recv AAC Data\n");
			if(pEnconn->saveStream==1)
			{
				if(pEnconn->Enctype==1)//ENC1200
				pEnconn->AacFile.Write((char*)pEnconn->m_cVideoBuffer+sizeof(FRAMEHEAD),nDataLen-sizeof(FRAMEHEAD));
				else
				pEnconn->AacFile.Write((char*)pEnconn->m_cVideoBuffer+1+sizeof(DataHeader),nDataLen-1-sizeof(DataHeader));
			}
			break;
		case MSG_SYSPARAMS:
			
			printf("Recv MSG_SYSPARAMS \n");
			break;
		case MSG_TRACKAUTO:
			
			printf("Recv MSG_TRACKAUTO \n");
			break;
		case MSG_DATAINFO:
			
			printf("Recv MSG_DATAINFO \n");
			break;	
		case MSG_LOW_BITRATE:
			
			printf("Recv LowStream ok \n");
			break;
		case  MSG_LOW_SCREENDATA:			
			printf("Recv LowStream Data\n");
			break;
		case MSG_PIC_DATA:					
			//memcpy(&nDataLen, &pEnconn->m_cVideoBuffer[1],sizeof(nDataLen));
			memcpy(&nDataLen, (char*)pEnconn->m_cVideoBuffer+1,sizeof(nDataLen));
			printf("PPT索引图片=%d 字节\n", nDataLen);
			//hMem = ::GlobalAlloc(GMEM_MOVEABLE,nDataLen);
			//lpBuf = ::GlobalLock(hMem);
			rcvLen = pEnconn->Recv((char*)pEnconn->m_cVideoBuffer+4, nDataLen);
			finename.Format(_T("%d.jpg"),pptindex);
			if (!(pEnconn->JpgFile.Open(finename,CFile::modeCreate | CFile::modeWrite)))
			{
				printf("open jpegFile fail! \n");
				pptindex++;
				break;
			}
			pEnconn->JpgFile.Write((char*)pEnconn->m_cVideoBuffer+4,nDataLen);
			pEnconn->JpgFile.Close();
			pptindex++;
			hMem = ::GlobalAlloc(GMEM_MOVEABLE,nDataLen);
			lpBuf = ::GlobalLock(hMem);
			memcpy(lpBuf,(char*)pEnconn->m_cVideoBuffer+4,nDataLen);
			::GlobalUnlock(hMem);
			::CreateStreamOnHGlobal(hMem, TRUE, &pStm); //装入图形文件	
			if(SUCCEEDED(OleLoadPicture(pStm,nDataLen,TRUE,IID_IPicture,(LPVOID*)&pPic)))
			{
					
				OLE_XSIZE_HIMETRIC hmWidth;
				OLE_YSIZE_HIMETRIC hmHeight;
				pPic->get_Width(&hmWidth); //用接口方法获得图片的宽和高
				pPic->get_Height(&hmHeight);				
				printf("PPTJPEG=%d=%d\n",hmWidth,hmHeight);
				//获取桌面窗口句柄
				hwnd = ::GetDesktopWindow();
				//获取桌面窗口DC
				hdc = ::GetWindowDC(hwnd);				
				CRect rect;
				CDC *pDC=CDC::FromHandle(hdc);
				//////显示原图大小/////////////////////////////////////////////////////////////
				CSize sz(hmWidth,hmHeight);
				pDC->HIMETRICtoDP(&sz); //转换MM_HIMETRIC模式单位为MM_TEXT像素单位			
				pPic->Render(hdc,80,80,sz.cx,sz.cy,0,hmHeight,hmWidth,-hmHeight,NULL);
				//按窗口尺寸显示///////////////////						  
				GetClientRect(hwnd,&rect);
				if(pPic) pPic->Release();					
				::ReleaseDC(hwnd, hdc);
				
			}				
			pStm->Release();  

			printf("Recv PPT Data\n");
			break;
		case MSG_GET_LOGOINFO:	
			printf("Recv MSG_GET_LOGOINFO \n");
			break;
		case MSG_PIC_DATAEX:	
			printf("Recv MSG_PIC_DATAEX \n");
			recvedlen=0;			
			break;
		default:
	
			break;
		}
		
	}

Exit:	
	pEnconn->Connflag=0;
	pEnconn->PostMessage(RM_DISCONN,NULL);
	return 1;

}