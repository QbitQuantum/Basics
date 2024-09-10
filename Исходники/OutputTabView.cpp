void COutputTabView::OnItemchangedList3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	//AfxMessageBox(_T("hola"));
	
	//CAIPIEditView notification modified message
	g_bNotificationModified = false;
	

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*) pNMHDR;
	int nSelected = pNMListView->iItem;
	
	CString strItemLine		= m_listCtrl3.GetItemText(nSelected, 1);
	CString strItemPos		= m_listCtrl3.GetItemText(nSelected, 2);
	CString strFilePath		= m_listCtrl3.GetItemText(nSelected, 3);
	CString strFileName		= m_listCtrl3.GetItemText(nSelected, 4);
	
	CString strPathName = strFilePath + strFileName;

	int iLine = _ttoi(strItemLine);
	long iPos = _ttoi(strItemPos);
	int len = m_strFindText.GetLength();

		
	if ( pNMListView->uNewState & LVIS_SELECTED)
	{
			
		if( strFileName != _T(" - ") )
		{
		
			CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
			BOOL alreadyOpen = pApp->SetDocumentView(strPathName);
		

				//if document is not already open then open it
			if( alreadyOpen == FALSE )
			{
				CString strExt = strPathName.Right(3);

			
				if( strExt == _T("knw") || strExt == _T("txt") )
				{
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					pMainFrame->m_wndOutputTabView.AddMsg1(_T("The file  (") + strFileName + _T(")  was opened."));		
				}
				else if ( strExt == _T("ssn") || strExt == _T("rtf") )
				{
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					pMainFrame->m_wndOutputTabView.AddMsg1(_T("WARNING: Aipi session file found (.ipi). The file  (") + strFileName + _T(")  do not belong to Aipi knowlegde files. Check the path and the name of the file."));	
				}
				else if( strExt == _T("csv") || _T("idt") || _T("tre") )
				{
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					pMainFrame->m_wndOutputTabView.AddMsg1(_T("WARNING: Aipi tree file (.adt). The file  (") + strFileName + _T(")  do not belong to Aipi knowledge files. Check the path and the name of the file."));
				}
				else
				{
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					pMainFrame->m_wndOutputTabView.AddMsg1(_T("WARNING: The file  (") + strFileName + _T(")   do not belong to Aipi knowledge files. Check the path and the name of the file."));
				}
		
				pApp->m_pAIPIEditorDocTemplate->OpenDocumentFile(strPathName);
				if( pApp == NULL )
				{
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					pMainFrame->m_wndOutputTabView.AddMsg1(_T("ERROR: The file  (") + strFileName + _T(")   could not be linked. Check if the file is not corrupted."));
					return;
				}
		
		
			}
			else
			{
				CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
				CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
				CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
				ASSERT(pView);
				CScintillaCtrl& rCtrl = pView->GetCtrl();
				// Reset Scintilla Markers 
				rCtrl.MarkerDeleteAll(0);

				// Initilaize error markers
				rCtrl.MarkerDefine(0, SC_MARK_SHORTARROW);
				rCtrl.MarkerSetFore(0, RGB( 0, 0, 255 ));
				rCtrl.MarkerSetBack(0, RGB( 0, 0, 255 ));
		
				// Set error marker to proper line
				rCtrl.GotoLine(iLine -1 );
				rCtrl.MarkerAdd((iLine - 1), 0);

				//Set the cursor position in the GUI
				rCtrl.SetFocus();
				rCtrl.SetSel(iPos - len, iPos);
				
				//int n = pApp->CountOpenDocuments();
				//int b = n;
			}

		}

		 
		
		
	}	

	
	*pResult;
	Beep(iPos, 100);

	g_bNotificationModified = true;
	
	
	
}