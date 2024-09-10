void CSXSView::OnTimer(UINT_PTR nIDEvent)
{
	
	CAutoBrowser AutoBrowser((IWebBrowser2 *)GetApplication(),GetIEServerWnd());

	if (nIDEvent == TIME_ID_INPUT_LOGIN)
	{
		KillTimer(nIDEvent);

		//输入用户名
		{
			CElementInformation ElemInfo;
			ElemInfo.SetTagName(L"input");
			ElemInfo.AddElementAttribute(L"id",L"edit-name",TRUE);

			CElemRectList ElemList;
			AutoBrowser.GetAllMatchElemRect(&ElemList,&ElemInfo);

			if (ElemList.GetElemRectCount() == 1)
			{
				ELEM_RECT ElemRect;
				ElemList.GetElemRectByIndex(0,&ElemRect);

				CComQIPtr<IHTMLInputElement> pInput;
				ElemRect.pElem->QueryInterface(IID_IHTMLInputElement,(void **)&pInput);
				pInput->put_value(theApp.m_strUserName.AllocSysString());
			}
		}

		//输入密码
		{
			CElementInformation ElemInfo;
			ElemInfo.SetTagName(L"input");
			ElemInfo.AddElementAttribute(L"id",L"edit-pass",TRUE);


			CElemRectList ElemList;
			AutoBrowser.GetAllMatchElemRect(&ElemList,&ElemInfo);

			if (ElemList.GetElemRectCount() == 1)
			{
				ELEM_RECT ElemRect;
				ElemList.GetElemRectByIndex(0,&ElemRect);

				CComQIPtr<IHTMLInputElement> pInput;
				ElemRect.pElem->QueryInterface(IID_IHTMLInputElement,(void **)&pInput);
				pInput->put_value(theApp.m_strPassWord.AllocSysString());
			}
		}

		//选中验证码框
		{
			CElementInformation ElemInfo;
			ElemInfo.SetTagName(L"input");
			ElemInfo.AddElementAttribute(L"id",L"edit-captcha-response",TRUE);
			AutoBrowser.ClickFirstMatchWebPageElement(&ElemInfo);
		}

	}
	
	if (nIDEvent == TIME_ID_MOUSE_MOVE)
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		AutoBrowser.SetWebPageMousePos(CAutoBrowser::GetRandValue(0,rcClient.Width()),CAutoBrowser::GetRandValue(0,rcClient.Height()));
	}


	if ( nIDEvent == TIME_ID_QUERY_USER_INFO )
	{
		KillTimer(nIDEvent);

		CString strUserRealName;


		CElementInformation ElemInfo;
		ElemInfo.SetTagName(L"a");
		ElemInfo.AddElementAttribute(L"href",L"/admin/std/info",TRUE);

		CElementInformation *pParentInfo = ElemInfo.CreateParentInfo();
		pParentInfo->SetTagName(L"span");
		pParentInfo->AddElementAttribute(L"class",L"user-title",TRUE);

		CElemRectList ElemList;
		AutoBrowser.GetAllMatchElemRect(&ElemList,&ElemInfo);

		if (ElemList.GetElemRectCount() == 1)
		{
			ELEM_RECT ElemRect;
			ElemList.GetElemRectByIndex(0,&ElemRect);

			CComQIPtr<IHTMLElement> pElem;
			ElemRect.pElem->QueryInterface(IID_IHTMLElement,(void **)&pElem);
			if (pElem)
			{
				CComBSTR bstrInnerText;
				pElem->get_innerText(&bstrInnerText);
				strUserRealName = bstrInnerText;
			}
		}

		CMainFrame *pParentFrame = (CMainFrame *)GetParent();
		if (pParentFrame)
		{
			pParentFrame->UpdateFrameTitle(theApp.m_strUserName+L" "+strUserRealName);
			g_loger.StatusOut(L"获取用户信息：%s %s",theApp.m_strUserName,strUserRealName);
		}

	}

	if( nIDEvent == TIME_ID_CLICK_WATCH_CONTINE )
	{
		KillTimer(nIDEvent);

		CElementInformation ElemInfo;
		ElemInfo.SetTagName(L"a");
		ElemInfo.SetTextName(L"继续观看",FALSE);
		ElemInfo.AddElementAttribute(L"href",L"/admin/std/training/",FALSE);
		AutoBrowser.ClickFirstMatchWebPageElement(&ElemInfo);

		g_loger.StatusOut(L"点击继续学习按钮");

	}

	if ( nIDEvent == TIME_ID_CLICK_RESUME )
	{
		KillTimer(nIDEvent);

		CElementInformation ElemInfo;
		CElemRectList ElemList;

		ElemInfo.SetTagName(L"object");
		ElemInfo.AddElementAttribute(L"id",L"VMSPlayer",TRUE);

		AutoBrowser.GetAllMatchElemRect(&ElemList,&ElemInfo);
		if ( ElemList.GetElemRectCount() == 1 )
		{
			// 51 382
			ELEM_RECT ElemRect;
			ElemList.GetElemRectByIndex(0,&ElemRect);
			AutoBrowser.ClickWebPagePoint(ElemRect.rcElem.left+51,ElemRect.rcElem.top+382);
			g_loger.StatusOut(L"点击重新观看按钮 X：%d Y：%d",ElemRect.rcElem.left+51,ElemRect.rcElem.top+382);
		}

	}
	
	if ( nIDEvent == TIME_ID_CHECK_VIDEO_PAUSE )
	{
		CElementInformation ElemInfo;
		CElemRectList ElemList;

		ElemInfo.SetTagName(L"object");
		ElemInfo.AddElementAttribute(L"id",L"VMSPlayer",TRUE);

		AutoBrowser.GetAllMatchElemRect(&ElemList,&ElemInfo);
		if ( ElemList.GetElemRectCount() == 1 )
		{
			// 51 382
			ELEM_RECT ElemRect;
			ElemList.GetElemRectByIndex(0,&ElemRect);
			
			CRect rcElem;
			rcElem = ElemRect.rcElem;
			CPoint ptCenter;
			ptCenter = rcElem.CenterPoint();

			COLORREF refColor = 0;

			HDC hDc = ::GetDC(GetIEServerWnd());
			refColor =  GetPixel(hDc,ptCenter.x,ptCenter.y);
			::ReleaseDC(GetIEServerWnd(),hDc);
			
			if ( m_refPreColor == refColor )
			{
				m_nColorSameCount++;
			}
			else
			{
				m_nColorSameCount=0;
			}

			m_refPreColor = refColor;

			if ( m_nColorSameCount > 20 )
			{
				g_loger.StatusOut(L"窗口定点颜色 %x 超过 20*5 秒没有变化",m_refPreColor);

				KillTimer(nIDEvent);

				CElementInformation ElemInfo;
				ElemInfo.SetTagName(L"input");
				ElemInfo.AddElementAttribute(L"value",L"退出学习",FALSE);
				//ElemInfo.AddElementAttribute(L"type",L"submit",TRUE);
				AutoBrowser.ClickFirstMatchWebPageElement(&ElemInfo);
			}
		
#ifdef DEBUG
			CString strMsgOut;
			strMsgOut.Format(L"0x%x\r\n",refColor);
			OutputDebugStringW(strMsgOut);
#endif
		}
	}

	CIECoreView::OnTimer(nIDEvent);
}