void DumpMemoryGui::OnOK(UINT uNotifyCode, int nID, CWindow wndCtl)
{
	DoDataExchange(DDX_SAVE);

	if (EditMemoryAddress.GetValue() == 0 || EditMemorySize.GetValue() == 0)
	{
		wndCtl.MessageBoxW(L"Textbox is empty!",L"Error",MB_ICONERROR);
	}
	else
	{
		if (dumpMemory())
		{
			EndDialog(1);
		}
		else
		{
			wndCtl.MessageBoxW(L"Reading memory from process failed",L"Error",MB_ICONERROR);
		}		
	}	
}