bool NewBrowserInstance(IUIControler *pUIControl,PVOID *ppPageRef,CString strUrl,LONG * nNewPageID/*=NULL*/)
{
	IWBCoreNotifyer *pCoreNotify = NULL;
	IUINotifyer *pUINotify = NULL;
	if( pUIControl == NULL )
	{
		//创建一个新框架
		pUIControl = NewMainFrame(NULL,NULL,theApp.m_bMutiTab,theApp.m_bMenuBar,theApp.m_bToolBar,theApp.m_bCommandBar);

		//创建一个新的UI和浏览器内核通知实例
		pUINotify = new INotifyerInstance(pUIControl);
	}
	else
	{
		pUIControl->GetNofiyerPoint(&pUINotify);
	}
	
	pCoreNotify = dynamic_cast<IWBCoreNotifyer *>(pUINotify);


	//创建一个新的浏览器内核
	HANDLE hPageThread = NULL;
	CRect rcClient(0,0,800,600);
	pUIControl->ControlQueryClientRect(&rcClient);
	IWBCoreControler *pWBCoreControl = NewWBCore( pCoreNotify, ppPageRef,&hPageThread,NULL ,rcClient,nNewPageID);
	
	HWND hCoreWnd = NULL;
	pWBCoreControl->ControlQueryWnd(&hCoreWnd);

	SetPropW(hCoreWnd,L"CorePageThread",hPageThread);

	pUIControl->SetNofiyerPoint(pUINotify);

	//连接内核和框架
	AttachWBCoreToFrame(pWBCoreControl,pCoreNotify,pUIControl);
	if ( strUrl.GetLength() > 0 )
	{
		pWBCoreControl->ControlGotoUrl(strUrl);
	}

	return true;
}