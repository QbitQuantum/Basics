void MainFrame::OnClick(TNotifyUI& msg)
{
	WindowImplBase::OnClick(msg);
	if (_tcsicmp(msg.pSender->GetName(), kHideLeftMainPannelControlName) == 0)
	{
		CControlUI* left_main_pannel = m_PaintManager.FindControl(kLeftMainPannelControlName);
		CControlUI* hide_left_main_pannel = m_PaintManager.FindControl(kHideLeftMainPannelControlName);
		CControlUI* show_left_main_pannel = m_PaintManager.FindControl(kShowLeftMainPannelControlName);
		if ((left_main_pannel != NULL) && (show_left_main_pannel != NULL) && (hide_left_main_pannel != NULL))
		{
			hide_left_main_pannel->SetVisible(false);
			left_main_pannel->SetVisible(false);
			show_left_main_pannel->SetVisible(true);
		}
	}
	else if (_tcsicmp(msg.pSender->GetName(), kShowLeftMainPannelControlName) == 0)
	{
		CControlUI* left_main_pannel = m_PaintManager.FindControl(kLeftMainPannelControlName);
		CControlUI* hide_left_main_pannel = m_PaintManager.FindControl(kHideLeftMainPannelControlName);
		CControlUI* show_left_main_pannel = m_PaintManager.FindControl(kShowLeftMainPannelControlName);
		if ((left_main_pannel != NULL) && (show_left_main_pannel != NULL) && (hide_left_main_pannel != NULL))
		{
			hide_left_main_pannel->SetVisible(true);
			left_main_pannel->SetVisible(true);
			show_left_main_pannel->SetVisible(false);
		}
	}
	else if (_tcsicmp(msg.pSender->GetName(), kSignatureTipsControlName) == 0)
	{
		msg.pSender->SetVisible(false);
		CEditUI* signature = static_cast<CEditUI*>(m_PaintManager.FindControl(kSignatureControlName));
		if (signature != NULL)
		{
			signature->SetText(msg.pSender->GetText());
			signature->SetVisible(true);
		}
	}
	else if (_tcsicmp(msg.pSender->GetName(), kSearchEditTipControlName) == 0)
	{
		msg.pSender->SetVisible(false);
		CEditUI* search_edit = static_cast<CEditUI*>(m_PaintManager.FindControl(kSearchEditControlName));
		if (search_edit != NULL)
		{
			search_edit->SetText(msg.pSender->GetText());
			search_edit->SetVisible(true);
		}
	}
	else if (_tcsicmp(msg.pSender->GetName(), kChangeBkSkinControlName) == 0)
	{
		CControlUI* background = m_PaintManager.FindControl(kBackgroundControlName);
		if (background != NULL)
		{
			TCHAR szBuf[MAX_PATH] = { 0 };
			++bk_image_index_;
			if (kBackgroundSkinImageCount < bk_image_index_)
				bk_image_index_ = 0;

			_stprintf_s(szBuf, MAX_PATH - 1, _T("file='bg%d.png' corner='600,200,1,1'"), bk_image_index_);

			background->SetBkImage(szBuf);

			SkinChangedParam param;
			CControlUI* background = m_PaintManager.FindControl(kBackgroundControlName);
			if (background != NULL)
			{
				param.bkcolor = background->GetBkColor();
				if (_tcslen(background->GetBkImage()) > 0)
				{
					_stprintf_s(szBuf, MAX_PATH - 1, _T("bg%d.png"), bk_image_index_);
				}

				param.bgimage = szBuf;
			}
			skin_changed_observer_.Broadcast(param);
		}
	}
	else if (_tcsicmp(msg.pSender->GetName(), kChangeColorSkinControlName) == 0)
	{
		CDuiRect rcWindow;
		GetWindowRect(m_hWnd, &rcWindow);
		rcWindow.top = rcWindow.top + msg.pSender->GetPos().bottom;
		new ColorSkinWindow(this, rcWindow);
	}
	else if (0 == _tcsicmp(msg.pSender->GetName(), _T("phone")))
	{
		logic::GetLogic()->asynNotifyObserver(module::KEY_LOGIN_USERID,10);
	}
	else if (0 == _tcsicmp(msg.pSender->GetName(), _T("QQpalycenter")))
	{
		logic::GetLogic()->removeObserver(this);
	}
	else if (0 == _tcsicmp(msg.pSender->GetName(), _T("MainMenu")))
	{
		CMenuWnd* pMenu = new CMenuWnd(m_hWnd);
		DuiLib::CPoint point = msg.ptMouse;
		ClientToScreen(m_hWnd, &point);
		STRINGorID xml(_T("menutest.xml"));
		pMenu->Init(NULL, xml, _T("xml"), point);
	}
	else if (0 == _tcsicmp(msg.pSender->GetName(), _T("ToolsBtn")))//设置按钮
	{
		MakeGroupWnd* pFrame = new MakeGroupWnd();
		if (pFrame == NULL) return;
		pFrame->Create(NULL, _T("MakeGroupWnd"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 600, 800);
		pFrame->CenterWindow();
		pFrame->ShowWindow(true);

	}
	else if (0 == _tcsicmp(msg.pSender->GetName(), _T("QQSafeBtn")))//安全中心
	{
	}
	else if (0 == _tcsicmp(msg.pSender->GetName(), _T("messageCenterBtn")))//消息中心
	{
		FloatWnd* pFloatWnd = new FloatWnd();
		if (pFloatWnd == NULL) return;
		pFloatWnd->Create(m_hWnd, _T("FloatWnd"), UI_WNDSTYLE_FRAME|WS_THICKFRAME,  WS_EX_TOOLWINDOW | WS_EX_TOPMOST| WS_EX_STATICEDGE, 0, 0, 0, 0);
		//pFloatWnd->ShowWindow(true);
		pFloatWnd->BringToTop();
	}
	else if (0 == _tcsicmp(msg.pSender->GetName(), _T("QzoneBtn")))
	{

	}
	else if (0 == _tcsicmp(msg.pSender->GetName(), _T("QQTradeCenterBtn")))
	{
		int n = 0;
		n++;
	}
	else if (0 == _tcsicmp(msg.pSender->GetName(), _T("paipaiBtn")))
	{
		int n = 0;
		n++;
	}
	else if (0 == _tcsicmp(msg.pSender->GetName(), _T("PaiPaiChongzhiBtn")))
	{
		int n = 0;
		n++;
	}
	else if (0 == _tcsicmp(msg.pSender->GetName(), _T("addBtn")))
	{
		int n = 0;
		n++;
	}
	else if (0 == _tcsicmp(msg.pSender->GetName(), _T("friend_circleBtn")))
	{
		LoginWnd* pLoginWnd = new LoginWnd();
		if (pLoginWnd == NULL) return;
		pLoginWnd->Create(NULL, _T("LoginWnd"), /*WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS*/UI_WNDSTYLE_FRAME | WS_POPUP, 0/*WS_EX_LAYERED*/, 0, 0, 0, 0);
		pLoginWnd->CenterWindow();
		pLoginWnd->ShowWindow(true); 
	}
	else if (0 == _tcsicmp(msg.pSender->GetName(), _T("mailBtn")))
	{
		MainDialog* pMainDialog = new MainDialog();
		if (pMainDialog == NULL) return;
		pMainDialog->Create(NULL, _T("MainDialog"), UI_WNDSTYLE_FRAME | WS_POPUP, 0, 0, 0, 0, 0);
		pMainDialog->CenterWindow();
		pMainDialog->ShowWindow(true);
	}
	else if (0 == _tcsicmp(msg.pSender->GetName(), _T("XiaoYouBtn")))
	{
		int n = 0;
		n++;
	}
	else if (0 == _tcsicmp(msg.pSender->GetName(), _T("sosoBtn")))
	{
		int n = 0;
		n++;
	}
}