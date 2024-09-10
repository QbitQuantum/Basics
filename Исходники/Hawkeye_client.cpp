void CHawkeye_clientApp::ReceiveData()
{
	CommandMes cm;
	clasock->Receive(&cm,sizeof(cm));
	if(cm.mtype == SELF_KILLING)
	{
		SelfKilling();
	}
	else if(cm.mtype == REG_TRUE)
	{
		phe->m_againreg = true;
		phe->SetRegistyStartProgram(TRUE);
		CString dtime;
		_wstrtime((TCHAR*)dtime.GetString());
		phe->m_listlog.InsertItem(0,dtime);
		phe->m_listlog.SetItemText(0,1,L"COMMAND");
		phe->m_listlog.SetItemText(0,2,L"Regstry Able");
		phe->m_listlog.UpdateData(false);
	}
	else if(cm.mtype == REG_FALSE)
	{
		phe->m_againreg = false;
		phe->SetRegistyStartProgram(FALSE);
		CString dtime;
		_wstrtime((TCHAR*)dtime.GetString());
		phe->m_listlog.InsertItem(0,dtime);
		phe->m_listlog.SetItemText(0,1,L"COMMAND");
		phe->m_listlog.SetItemText(0,2,L"Regstry Disable");
		phe->m_listlog.UpdateData(false);
	}
	else if(cm.mtype == SEND_MES)
	{
		AfxMessageBox(cm.minfo,MB_ICONEXCLAMATION);
		CString dtime;
		_wstrtime((TCHAR*)dtime.GetString());
		phe->m_listlog.InsertItem(0,dtime);
		phe->m_listlog.SetItemText(0,1,L"COMMAND");
		phe->m_listlog.SetItemText(0,2,L"Message");
		phe->m_listlog.UpdateData(false);
	}
	else if(cm.mtype == ON_PROGRAM)
	{
		::ShellExecute(NULL, L"open", cm.minfo,L"", NULL, SW_SHOW);
		CString dtime;
		_wstrtime((TCHAR*)dtime.GetString());
		phe->m_listlog.InsertItem(0,dtime);
		phe->m_listlog.SetItemText(0,1,L"COMMAND");
		phe->m_listlog.SetItemText(0,2,L"Execute");
		phe->m_listlog.UpdateData(false);
	}
	else if(cm.mtype == TM_PROGRAM)
	{
		HWND hExit;
		hExit = ::FindWindowW(NULL,cm.minfo);
		if(hExit != NULL)
		{
			::PostMessageW(hExit,WM_QUIT,0,0);
			CString dtime;
			_wstrtime((TCHAR*)dtime.GetString());
			phe->m_listlog.InsertItem(0,dtime);
			phe->m_listlog.SetItemText(0,1,L"COMMAND");
			phe->m_listlog.SetItemText(0,2,L"Terminate");
			phe->m_listlog.UpdateData(false);
		}
	}
	else if(cm.mtype == SHUT_DOWN)
	{
		phe->SystemShutdown(0);
		CString dtime;
		_wstrtime((TCHAR*)dtime.GetString());
		phe->m_listlog.InsertItem(0,dtime);
		phe->m_listlog.SetItemText(0,1,L"COMMAND");
		phe->m_listlog.SetItemText(0,2,L"Shutdown");
		phe->m_listlog.UpdateData(false);
	}
	else if(cm.mtype == RE_BOOT)
	{
		phe->SystemShutdown(1);
		CString dtime;
		_wstrtime((TCHAR*)dtime.GetString());
		phe->m_listlog.InsertItem(0,dtime);
		phe->m_listlog.SetItemText(0,1,L"COMMAND");
		phe->m_listlog.SetItemText(0,2,L"Reboot");
		phe->m_listlog.UpdateData(false);
	}
	else if(cm.mtype == RE_BOOT)
	{
		phe->SystemShutdown(2);
		CString dtime;
		_wstrtime((TCHAR*)dtime.GetString());
		phe->m_listlog.InsertItem(0,dtime);
		phe->m_listlog.SetItemText(0,1,L"COMMAND");
		phe->m_listlog.SetItemText(0,2,L"Hibernates");
		phe->m_listlog.UpdateData(false);
	}
	else if(cm.mtype == BLOCK_PROGRAM)
	{
		phe->InsertBlockList(cm.minfo);
		CString dtime;
		_wstrtime((TCHAR*)dtime.GetString());
		phe->m_listlog.InsertItem(0,dtime);
		phe->m_listlog.SetItemText(0,1,L"COMMAND");
		phe->m_listlog.SetItemText(0,2,L"InsertBlock");
		phe->m_listlog.UpdateData(false);
	}
	else if(cm.mtype == UNBLOCK_PROGRAM)
	{
		phe->DeleteBlockList(cm.minfo);
		CString dtime;
		_wstrtime((TCHAR*)dtime.GetString());
		phe->m_listlog.InsertItem(0,dtime);
		phe->m_listlog.SetItemText(0,1,L"COMMAND");
		phe->m_listlog.SetItemText(0,2,L"DeleteBlock");
		phe->m_listlog.UpdateData(false);
	}
	else if(cm.mtype == ALLRELEASE_PROGRAM)
	{
		phe->AllDeleteBlockList();
		CString dtime;
		_wstrtime((TCHAR*)dtime.GetString());
		phe->m_listlog.InsertItem(0,dtime);
		phe->m_listlog.SetItemText(0,1,L"COMMAND");
		phe->m_listlog.SetItemText(0,2,L"AllRelease");
		phe->m_listlog.UpdateData(false);
	}
}