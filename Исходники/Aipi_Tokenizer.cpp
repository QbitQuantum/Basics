void CAipi_Tokenizer::v_printTokenizer()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];

	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  TOKENIZER  *******"));
	
	//Print map container
	for( CMainFrame::g_vTokenizer::const_iterator iter = pMainFrame->gvTokenizer.begin(); iter!= pMainFrame->gvTokenizer.end(); ++iter)
	{
		CString strIndex =_T("");
		CString strPos1 =_T("");
		CString strPos2 =_T("");
		CString strLine = _T("");
		CString strIntForm =_T("");
		CString strCateg =_T("");
		
			
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Token Element  *******"));

		
		CAipi_Tokenizer tk = (CAipi_Tokenizer)(*iter);

 		int index = tk.getIndex();
		int pos1 = tk.getPos1();
		int pos2 = tk.getPos2();
		int line = tk.getLine();
		double iform = tk.getIntForm();
		int categ = tk.getCategory();
		tstring token = tk.getToken(); 

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Index: "));
		strIndex +=  _itot( index, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strIndex);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Pos1: "));
		strPos1 +=  _itot( pos1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPos1);
	
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Pos2: "));
		strPos2 +=  _itot( pos2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPos2);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Line: "));
		strLine +=  _itot( line, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strLine);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("IntForm: "));
		strIntForm.Format(_T("%f" ), iform);
		pMainFrame->m_wndOutputTabView.AddMsg1(strIntForm);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Category: "));
		strCateg +=  _itot( categ, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCateg);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Token: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(token.data());

			
	}

}