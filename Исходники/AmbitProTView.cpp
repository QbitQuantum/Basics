/////////////////////////////////////////////////////////////////////////
//For total management all UI information and control logic
//It distribute UI control message for all sub dialog.
UINT WINAPI MainViewTask(LPVOID lpPara)
{

	CAmbitProTView *pMView=(CAmbitProTView *)lpPara;
	MSG msg;
	int i=0;


	while(TRUE)
	{
		if (!WaitMessage())
		{
			continue;
		}
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			switch (msg.message)
			{
			case WM_SWTO_TESTER_DLG:
				pMView->ShowTesterDlg();
				break;
			case WM_SWTO_MAIN_TEST_PANEL:
				pMView->ShowMTestDlg();
				break;
			case WM_SWTO_SFIS_DLG:
				pMView->ShowSfisDlg();
				break;
			case WM_SWTO_MYDAS_DLG:
				pMView->ShowMydasDlg();
				break;
			case WM_VIRTUAL_SMO:
				pCVirtualSmoDlg->ShowWindow(SW_SHOW);
				break;
			case WM_EXIT:
				goto ExitLabel;
				break;
			case WM_SWTO_CONF_DLG://haibin.li 2011/11/07
				pMView->ShowConfDlg();
				break;
			case WM_SWTO_DETAIL_DLG://haibin.li 2011/11/07
				pMView->ShowDetailDlg();
				break;
			case WM_SWTO_RTM_DLG://haibin.li 2011/11/11
				pMView->ShowRtmDlg();
				break;
			default:
				;
			}
		}
	}
ExitLabel:

	return 0;
}