bool CMyV8Handler::Execute( const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception )
{
	if (name==_T("configInfo"))
	{
		retval= CefV8Value::CreateString(CefString(configInfo()));
		return true;
	}
	if (name==_T("clearPassword"))
	{
		GetUserDb()->DeleteUserInfo();
		return true;
	}
	if (name==_T("changeHost"))
	{
		if (arguments.size()>0&&arguments[0]->IsString())
		{
			CString strContent;
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			if(strContent.GetLength()>2)
				strContent=strContent.Mid(1,strContent.GetLength()-2);
			CString strTemp;
			if (COssApi::m_strHost!=_T(""))
				strTemp.Format(_T("\"%s\""),COssApi::m_strHost.c_str());
			else
				strTemp.Format(_T("\"%s\""),GetStaroneControl()->ChangeHost(wstring(strContent)).c_str());
			retval= CefV8Value::CreateString(CefString(strTemp));
		}
		return true;
	}
	if (name==_T("loadFinish"))
	{
		GetStaroneControl()->m_bLoadFinish=TRUE;
		return true;
	}
	if (name==_T("showAuthorizationDlg"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
		}
		CefRefPtr<CefV8Value> func=NULL;
		if (arguments.size()>1)
			func=arguments[1];
		Handler_Msg *hmsg=new Handler_Msg;
		hmsg->strJson=strContent;
		hmsg->v8Ctx=CefV8Context::GetCurrentContext();
		hmsg->vObject=object;
		hmsg->vFunc=func;
		CWebBaseDlg::m_HanderMsg.push_back(hmsg);
		CefRefPtr<CefBrowser> browser=CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> msg=CefProcessMessage::Create(_T("msgshowAuthorizationDlg"));
		CefRefPtr<CefListValue>msglist=msg->GetArgumentList();
		msglist->SetInt(0,(int)hmsg);
		browser->SendProcessMessage(PID_RENDERER,msg);
		return true;
	}
	if (name==_T("showWnd"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			Handler_Msg *hmsg=new Handler_Msg;
			hmsg->strJson=strContent;
			hmsg->v8Ctx=CefV8Context::GetCurrentContext();
			hmsg->vObject=object;
			hmsg->vFunc=func;
			CWebBaseDlg::m_HanderMsg.push_back(hmsg);
			CefRefPtr<CefBrowser> browser=CefV8Context::GetCurrentContext()->GetBrowser();
			CefRefPtr<CefProcessMessage> msg=CefProcessMessage::Create(_T("msgMain"));
			CefRefPtr<CefListValue>msglist=msg->GetArgumentList();
			msglist->SetInt(0,(int)hmsg);
			browser->SendProcessMessage(PID_RENDERER,msg);
		}
		return true;
	}
	if (name==_T("closeWnd"))
	{
		CefRefPtr<CefBrowser> browser=CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> msg=CefProcessMessage::Create(_T("msgcloseWnd"));
		browser->SendProcessMessage(PID_RENDERER,msg);
		return true;
	}
	if (name==_T("setClipboardData"))
	{
		if (arguments.size()>0&&arguments[0]->IsString())
		{
			CString strContent;
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			if(strContent.GetLength()>2)
				strContent=strContent.Mid(1,strContent.GetLength()-2);
			if(OpenClipboard(NULL)) 
			{   
				HGLOBAL clipbuffer; 
				char   *buffer; 
				EmptyClipboard(); 
				clipbuffer=GlobalAlloc(GMEM_DDESHARE,strContent.GetLength()*2+2); 
				buffer=(char *)GlobalLock(clipbuffer);
				memset(buffer,0,strContent.GetLength()*2+2);
				memcpy(buffer,strContent.GetBuffer(0),strContent.GetLength()*2);
				GlobalUnlock(clipbuffer); 
				SetClipboardData(CF_UNICODETEXT,clipbuffer); 
				CloseClipboard();
			}
		}
		return true;
	}
	if (name==_T("showLaunchpad"))
	{
		GetStaroenHummerDlg()->ShowLauchpad();
		return true;
	}
	if (name==_T("getAccessID"))
	{
		CString strTemp;
		strTemp.Format(_T("\"%s\""),GetStaroneControl()->m_UserInfo.strAccessID);
		retval= CefV8Value::CreateString(CefString(strTemp));
		return true;
	}
	if (name==_T("getSignature"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CString strTemp;
			strTemp.Format(_T("\"%s\""),GetSignature(strContent));
			retval= CefV8Value::CreateString(CefString(strTemp));
		}
		return true;
	}
	if (name==_T("getRamSignature"))
	{
		CString strCmd;
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strCmd.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
		}
		if(arguments.size()>1&&arguments[1]->IsString())
		{
			strContent.Format(_T("%s"),arguments[1]->GetStringValue().c_str());
		}
		CString strTemp;
		strTemp.Format(_T("\"%s\""),getRamSignature(strCmd,strContent));
		retval= CefV8Value::CreateString(CefString(strTemp));
		return true;
	}
	if (name==_T("addFile"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			Handler_Msg *hmsg=new Handler_Msg;
			hmsg->strJson=strContent;
			hmsg->v8Ctx=CefV8Context::GetCurrentContext();
			hmsg->vObject=object;
			hmsg->vFunc=func;
			CWebBaseDlg::m_HanderMsg.push_back(hmsg);
			CefRefPtr<CefBrowser> browser=CefV8Context::GetCurrentContext()->GetBrowser();
			CefRefPtr<CefProcessMessage> msg=CefProcessMessage::Create(_T("msgaddFile"));
			CefRefPtr<CefListValue>msglist=msg->GetArgumentList();
			msglist->SetInt(0,(int)hmsg);
			browser->SendProcessMessage(PID_RENDERER,msg);
		}
		return true;
	}
	if (name==_T("saveFile"))
	{
		if (arguments.size()>=1&&arguments[0]->IsString())
		{
			CString strContent;
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			Handler_Msg *hmsg=new Handler_Msg;
			hmsg->strJson=strContent;
			hmsg->v8Ctx=CefV8Context::GetCurrentContext();
			hmsg->vObject=object;
			hmsg->vFunc=func;
			CWebBaseDlg::m_HanderMsg.push_back(hmsg);
			CefRefPtr<CefBrowser> browser=CefV8Context::GetCurrentContext()->GetBrowser();
			CefRefPtr<CefProcessMessage> msg=CefProcessMessage::Create(_T("msgsaveFile"));
			CefRefPtr<CefListValue>msglist=msg->GetArgumentList();
			msglist->SetInt(0,(int)hmsg);
			browser->SendProcessMessage(PID_RENDERER,msg);
		}
		return true;
	}
	if (name==_T("saveFileDlg"))
	{
		if (arguments.size()==1)
		{
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>0)
				func=arguments[0];
			Handler_Msg *hmsg=new Handler_Msg;
			hmsg->strJson=_T("");
			hmsg->v8Ctx=CefV8Context::GetCurrentContext();
			hmsg->vObject=object;
			hmsg->vFunc=func;
			CWebBaseDlg::m_HanderMsg.push_back(hmsg);
			CefRefPtr<CefBrowser> browser=CefV8Context::GetCurrentContext()->GetBrowser();
			CefRefPtr<CefProcessMessage> msg=CefProcessMessage::Create(_T("msgsaveFileDlg"));
			CefRefPtr<CefListValue>msglist=msg->GetArgumentList();
			msglist->SetInt(0,(int)hmsg);
			browser->SendProcessMessage(PID_RENDERER,msg);
		}
		return true;
	}
	if (name==_T("selectFileDlg"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			Handler_Msg *hmsg=new Handler_Msg;
			hmsg->strJson=strContent;
			hmsg->v8Ctx=CefV8Context::GetCurrentContext();
			hmsg->vObject=object;
			hmsg->vFunc=func;
			CWebBaseDlg::m_HanderMsg.push_back(hmsg);
			CefRefPtr<CefBrowser> browser=CefV8Context::GetCurrentContext()->GetBrowser();
			CefRefPtr<CefProcessMessage> msg=CefProcessMessage::Create(_T("msgselectFileDlg"));
			CefRefPtr<CefListValue>msglist=msg->GetArgumentList();
			msglist->SetInt(0,(int)hmsg);
			browser->SendProcessMessage(PID_RENDERER,msg);
		}
		return true;
	}
	if (name==_T("getUpload"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
		}
		retval = CefV8Value::CreateString(CefString(getUpload(strContent)));
		return true;
	}
	if (name==_T("getDownload"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
		}
		retval = CefV8Value::CreateString(CefString(getDownload(strContent)));
		return true;
	}
	if (name==_T("startUpload"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			CHandlerTask *pTask=new CHandlerTask;
			pTask->Init(CefV8Context::GetCurrentContext(),object,func,strContent,_T("startUpload"));
			GetStaroneControl()->m_ThreadPool.AddTask(pTask);
		}
		return true;
	}
	if (name==_T("startDownload"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			CHandlerTask *pTask=new CHandlerTask;
			pTask->Init(CefV8Context::GetCurrentContext(),object,func,strContent,_T("startDownload"));
			GetStaroneControl()->m_ThreadPool.AddTask(pTask);
		}
		return true;
	}
	if (name==_T("stopUpload"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			CHandlerTask *pTask=new CHandlerTask;
			pTask->Init(CefV8Context::GetCurrentContext(),object,func,strContent,_T("stopUpload"));
			GetStaroneControl()->m_ThreadPool.AddTask(pTask);
		}
		return true;
	}
	if (name==_T("stopDownload"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			CHandlerTask *pTask=new CHandlerTask;
			pTask->Init(CefV8Context::GetCurrentContext(),object,func,strContent,_T("stopDownload"));
			GetStaroneControl()->m_ThreadPool.AddTask(pTask);
		}
		return true;
	}
	if (name==_T("deleteUpload"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			CHandlerTask *pTask=new CHandlerTask;
			pTask->Init(CefV8Context::GetCurrentContext(),object,func,strContent,_T("deleteUpload"));
			GetStaroneControl()->m_ThreadPool.AddTask(pTask);
		}
		return true;
	}
	if (name==_T("deleteDownload"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			CHandlerTask *pTask=new CHandlerTask;
			pTask->Init(CefV8Context::GetCurrentContext(),object,func,strContent,_T("deleteDownload"));
			GetStaroneControl()->m_ThreadPool.AddTask(pTask);
		}
		return true;
	}
	if (name==_T("setMetaObject"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			CHandlerTask *pTask=new CHandlerTask;
			pTask->Init(CefV8Context::GetCurrentContext(),object,func,strContent,_T("setMetaObject"));
			GetStaroneControl()->m_ThreadPool.AddTask(pTask);
		}
		return true;
	}
	if (name==_T("getClipboardData"))
	{
		retval = CefV8Value::CreateString(CefString(getClipboardData()));
		return true;
	}
	if (name==_T("getDragFiles"))
	{
		CString strContent=_T("{\"list\":[");
		for (int i=0;i<GetStaroneControl()->m_strDragList.size();i++)
		{
			if (i!=0)
				strContent+=_T(",");
			CString str;
			str.Format(_T("{\"path\":\"%s\"}"),slnhelper::ReplaceToJson(GetStaroneControl()->m_strDragList[i]));
			strContent+=str;
		}
		strContent+=_T("]}");
		retval = CefV8Value::CreateString(CefString(strContent));
		return true;
	}
	if (name==_T("deleteObject"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			Handler_Msg *hmsg=new Handler_Msg;
			hmsg->strJson=strContent;
			hmsg->v8Ctx=CefV8Context::GetCurrentContext();
			hmsg->vObject=object;
			hmsg->vFunc=func;
			CWebBaseDlg::m_HanderMsg.push_back(hmsg);
			CefRefPtr<CefBrowser> browser=CefV8Context::GetCurrentContext()->GetBrowser();
			CefRefPtr<CefProcessMessage> msg=CefProcessMessage::Create(_T("msgdeleteObject"));
			CefRefPtr<CefListValue>msglist=msg->GetArgumentList();
			msglist->SetInt(0,(int)hmsg);
			browser->SendProcessMessage(PID_RENDERER,msg);
		}
		return true;
	}
	if (name==_T("copyObject"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			Handler_Msg *hmsg=new Handler_Msg;
			hmsg->strJson=strContent;
			hmsg->v8Ctx=CefV8Context::GetCurrentContext();
			hmsg->vObject=object;
			hmsg->vFunc=func;
			CWebBaseDlg::m_HanderMsg.push_back(hmsg);
			CefRefPtr<CefBrowser> browser=CefV8Context::GetCurrentContext()->GetBrowser();
			CefRefPtr<CefProcessMessage> msg=CefProcessMessage::Create(_T("msgcopyObject"));
			CefRefPtr<CefListValue>msglist=msg->GetArgumentList();
			msglist->SetInt(0,(int)hmsg);
			browser->SendProcessMessage(PID_RENDERER,msg);
		}
		return true;
	}
	if (name==_T("changeUpload"))
	{
		CString strContent;
		CefRefPtr<CefV8Value> func=NULL;
		if(arguments.size()>0&&arguments[0]->IsString())
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
		if (arguments.size()>1)
			func=arguments[1];
		GetCallbackUploadThread()->SetCallbackStatus(CefV8Context::GetCurrentContext(),object,func,strContent);
		return true;
	}
	if (name==_T("changeDownload"))
	{
		CString strContent;
		CefRefPtr<CefV8Value> func=NULL;
		if(arguments.size()>0&&arguments[0]->IsString())
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
		if (arguments.size()>1)
			func=arguments[1];
		GetCallbackDownloadThread()->SetCallbackStatus(CefV8Context::GetCurrentContext(),object,func,strContent);
		return true;
	}
	if (name==_T("getErrorLog"))
	{
		retval = CefV8Value::CreateString(CefString(getErrorLog()));
		return true;
	}
	if (name==_T("loginByKey"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			Handler_Msg *hmsg=new Handler_Msg;
			hmsg->strJson=strContent;
			hmsg->v8Ctx=CefV8Context::GetCurrentContext();
			hmsg->vObject=object;
			hmsg->vFunc=func;
			CWebBaseDlg::m_HanderMsg.push_back(hmsg);
			CefRefPtr<CefBrowser> browser=CefV8Context::GetCurrentContext()->GetBrowser();
			CefRefPtr<CefProcessMessage> msg=CefProcessMessage::Create(_T("msgloginByKey"));
			CefRefPtr<CefListValue>msglist=msg->GetArgumentList();
			msglist->SetInt(0,(int)hmsg);
			browser->SendProcessMessage(PID_RENDERER,msg);
		}
		return true;
	}
	if (name==_T("loginByFile"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			Handler_Msg *hmsg=new Handler_Msg;
			hmsg->strJson=strContent;
			hmsg->v8Ctx=CefV8Context::GetCurrentContext();
			hmsg->vObject=object;
			hmsg->vFunc=func;
			CWebBaseDlg::m_HanderMsg.push_back(hmsg);
			CefRefPtr<CefBrowser> browser=CefV8Context::GetCurrentContext()->GetBrowser();
			CefRefPtr<CefProcessMessage> msg=CefProcessMessage::Create(_T("msgloginByFile"));
			CefRefPtr<CefListValue>msglist=msg->GetArgumentList();
			msglist->SetInt(0,(int)hmsg);
			browser->SendProcessMessage(PID_RENDERER,msg);
		}
		return true;
	}
	if (name==_T("setPassword"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			Handler_Msg *hmsg=new Handler_Msg;
			hmsg->strJson=strContent;
			hmsg->v8Ctx=CefV8Context::GetCurrentContext();
			hmsg->vObject=object;
			hmsg->vFunc=func;
			CWebBaseDlg::m_HanderMsg.push_back(hmsg);
			CefRefPtr<CefBrowser> browser=CefV8Context::GetCurrentContext()->GetBrowser();
			CefRefPtr<CefProcessMessage> msg=CefProcessMessage::Create(_T("msgsetPassword"));
			CefRefPtr<CefListValue>msglist=msg->GetArgumentList();
			msglist->SetInt(0,(int)hmsg);
			browser->SendProcessMessage(PID_RENDERER,msg);
		}
		return true;
	}
	if (name==_T("loginPassword"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			Handler_Msg *hmsg=new Handler_Msg;
			hmsg->strJson=strContent;
			hmsg->v8Ctx=CefV8Context::GetCurrentContext();
			hmsg->vObject=object;
			hmsg->vFunc=func;
			CWebBaseDlg::m_HanderMsg.push_back(hmsg);
			CefRefPtr<CefBrowser> browser=CefV8Context::GetCurrentContext()->GetBrowser();
			CefRefPtr<CefProcessMessage> msg=CefProcessMessage::Create(_T("msgloginPassword"));
			CefRefPtr<CefListValue>msglist=msg->GetArgumentList();
			msglist->SetInt(0,(int)hmsg);
			browser->SendProcessMessage(PID_RENDERER,msg);
		}
		return true;
	}
	if (name==_T("setServerLocation"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			Handler_Msg *hmsg=new Handler_Msg;
			hmsg->strJson=strContent;
			hmsg->v8Ctx=CefV8Context::GetCurrentContext();
			hmsg->vObject=object;
			hmsg->vFunc=func;
			CWebBaseDlg::m_HanderMsg.push_back(hmsg);
			CefRefPtr<CefBrowser> browser=CefV8Context::GetCurrentContext()->GetBrowser();
			CefRefPtr<CefProcessMessage> msg=CefProcessMessage::Create(_T("msgsetServerLocation"));
			CefRefPtr<CefListValue>msglist=msg->GetArgumentList();
			msglist->SetInt(0,(int)hmsg);
			browser->SendProcessMessage(PID_RENDERER,msg);
		}
		return true;
	}
	if (name==_T("saveAuthorization"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			Handler_Msg *hmsg=new Handler_Msg;
			hmsg->strJson=strContent;
			hmsg->v8Ctx=CefV8Context::GetCurrentContext();
			hmsg->vObject=object;
			hmsg->vFunc=func;
			CWebBaseDlg::m_HanderMsg.push_back(hmsg);
			CefRefPtr<CefBrowser> browser=CefV8Context::GetCurrentContext()->GetBrowser();
			CefRefPtr<CefProcessMessage> msg=CefProcessMessage::Create(_T("msgsaveAuthorization"));
			CefRefPtr<CefListValue>msglist=msg->GetArgumentList();
			msglist->SetInt(0,(int)hmsg);
			browser->SendProcessMessage(PID_RENDERER,msg);
		}
		return true;
	}
	if (name==_T("getDeviceEncoding"))
	{
		CString strDevice=CRsa::GetDevice();
		wstring hash=L"";
		if (strDevice!=_T(""))
			hash=slnhelper::getstringhash(wstring(strDevice));
		CString strRet;
		strRet.Format(_T("\"%s\""),hash.c_str());
		retval = CefV8Value::CreateString(CefString(strRet));
		return true;
	}
	if (name==_T("getUIPath"))
	{
		CString strRet=_T("");
		if (GetUserDb()->GetUIPath()!=_T(""))
			strRet.Format(_T("\"%s\""),slnhelper::ReplaceToJson(GetUserDb()->GetUIPath()));
		else
			strRet.Format(_T("\"%s\""),slnhelper::ReplaceToJson(GetStaroneControl()->m_strUIPath));
		retval= CefV8Value::CreateString(CefString(strRet));
		return true;
	}
	if (name==_T("openLogFolder"))
	{
		ShellExecute(NULL,_T("open"),GetStaroneControl()->m_strUserConfig+_T("\\log"),NULL,NULL, SW_SHOW);
		return true;
	}
	if (name==_T("deleteBucket"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			CefRefPtr<CefV8Value> func=NULL;
			if (arguments.size()>1)
				func=arguments[1];
			Handler_Msg *hmsg=new Handler_Msg;
			hmsg->strJson=strContent;
			hmsg->v8Ctx=CefV8Context::GetCurrentContext();
			hmsg->vObject=object;
			hmsg->vFunc=func;
			CWebBaseDlg::m_HanderMsg.push_back(hmsg);
			CefRefPtr<CefBrowser> browser=CefV8Context::GetCurrentContext()->GetBrowser();
			CefRefPtr<CefProcessMessage> msg=CefProcessMessage::Create(_T("msgdeleteBucket"));
			CefRefPtr<CefListValue>msglist=msg->GetArgumentList();
			msglist->SetInt(0,(int)hmsg);
			browser->SendProcessMessage(PID_RENDERER,msg);
		}
		return true;
	}
	if (name==_T("setTransInfo"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			setTransInfo(strContent);
		}
		return true;
	}
	if (name==_T("getTransInfo"))
	{
		retval = CefV8Value::CreateString(CefString(getTransInfo()));
		return true;
	}
	if (name==_T("getCurrentLocation"))
	{
		CString strTemp=_T("");
		if (GetStaroneControl()->m_UserInfo.strArea!=_T(""))
		{
			strTemp.Format(_T("\"%s\""),GetStaroneControl()->m_UserInfo.strArea);
		}
		retval = CefV8Value::CreateString(CefString(strTemp));
		return true;
	}
	if (name==_T("getCurrentHost"))
	{
		CString strTemp=_T("");
		if (GetStaroneControl()->m_UserInfo.strHost!=_T(""))
		{
			strTemp.Format(_T("\"%s\""),GetStaroneControl()->m_UserInfo.strHost);
		}
		retval = CefV8Value::CreateString(CefString(strTemp));
		return true;
	}
	if (name==_T("stopLoadDownload"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			stopLoadDownload(strContent);
		}
		return true;
	}
	if (name==_T("openUrl")) 
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			openUrl(strContent);
		}
		return true;
	}
	if (name==_T("setCallFunctionInfo"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			setCallFunctionInfo(strContent);
		}
		return true;
	}
	if (name==_T("getCallFunctionInfo"))
	{
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
			retval = CefV8Value::CreateString(CefString(getCallFunctionInfo(strContent)));
		}
		return true;
	}
	if (name==_T("gGetLanguage"))
	{
		retval = CefV8Value::CreateString(CefString(gGetLanguage()));
		return true;
	}
	if (name==_T("gChangeLanguage"))
	{
		CString strContent=_T("");
		if(arguments.size()>0&&arguments[0]->IsString())
			strContent.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
		gChangeLanguage(strContent);
		return true;
	}
	if (name==_T("gAccountAction"))
	{
		CString strCmd;
		CString strContent;
		if(arguments.size()>0&&arguments[0]->IsString())
		{
			strCmd.Format(_T("%s"),arguments[0]->GetStringValue().c_str());
		}
		if(arguments.size()>1&&arguments[1]->IsString())
		{
			strContent.Format(_T("%s"),arguments[1]->GetStringValue().c_str());
		}
		retval = CefV8Value::CreateString(CefString(gAccountAction(strCmd,strContent)));
		return true;
	}
	return false;
}