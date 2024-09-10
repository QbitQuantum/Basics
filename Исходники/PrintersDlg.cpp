void CPrintersDlg::OnAlterar()
{	
	CString sPrinter;

	POSITION p = m_lstPrinters.GetFirstSelectedItemPosition();
	int selected = m_lstPrinters.GetNextSelectedItem(p);

	sPrinter = m_lstPrinters.GetItemText(selected, 1);

	if(m_lstPrinters.GetSelectedCount() == 0)
	{
		CString msg;
		msg.LoadString(IDS_IMPRESSORA_PADRAO);

		MessageBox(msg, L"Mensagem", MB_OK | MB_ICONINFORMATION);
		return;
	}

	Registry reg(HKEY_CURRENT_USER, BT_REG_KEY_APP);
	if(!reg.Open())
	{
		STLOG_WRITE("%s(%d): Open registry: %s", __FUNCTION__, __LINE__,
					reg.GetLastErrorString());

		CString msg;
		msg.LoadString(IDS_ERRO_IMPRESSORA_PADRAO);

		MessageBox(msg, L"Erro", MB_OK | MB_ICONERROR);
	}
	else
	{
		if(!reg.SetValue(L"DefaultPrinter", sPrinter))
		{
			STLOG_WRITE("%s(%d): read registry: %s", __FUNCTION__, __LINE__,
						reg.GetLastErrorString());
			
			CString msg;
			msg.LoadString(IDS_ERRO_IMPRESSORA_PADRAO);

			MessageBox(msg, L"Erro", MB_OK | MB_ICONERROR);
		}
		else
		{
#ifdef TESTE_IMPRESSORA
			CBTPrinter pp;
			pp.SaveDefaultPrinterAddr();

			CGetPinDlg gp;
			gp.DoModal();
			
			pp.SavePIN(gp.sPin);

#endif
			CString msg;
			msg.LoadString(IDS_IMPRESSORA_PADRAO_OK);

			MessageBox(msg, L"Mensagem", MB_OK | MB_ICONINFORMATION);
		}

		reg.Close();
	}

	EndDialog(IDOK);
	
}