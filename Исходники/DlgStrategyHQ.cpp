long CDlgStrategyHQ::LoadCurExp(WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/)
{	
	CDlgFormulaMan* pParentDlg  = (CDlgFormulaMan*)AfxGetMainWnd();
	if( pParentDlg == NULL )
		return 0;

	EnableItem(FALSE);

	if( wParam == CCompileEditView::UpdateExpress )
	{
		CDlgFormulaEdit* pDlg = pParentDlg->GetExpDlg();
		if( pDlg != NULL )
		{
			if(pDlg->SendMessage(HX_USER_LOADCUR,wParam,lParam))
			{
				pParentDlg->Enable(FALSE);
				pDlg->ShowWindow(SW_SHOWNORMAL);
			}
		}
	}
	else if( wParam == HX_EXPRESSSENTENCE )
	{
		//EnableItem(FALSE);

		CExpression* pExpression = (CExpression*)lParam;
		if( pExpression == NULL )
			return 0;
		CString csName = pExpression->GetName();
		CString cExpName = m_pStrategy->m_sExpName;
		if (m_bSetVar && csName == cExpName && m_pStrategy->m_pData->m_pCurVal)
		{
			CExpression *pex = ((CExpValue*)(m_pStrategy->m_pData->m_pCurVal))->GetExp();
			if (pex)//设置参数
			{
				CMapVariabile *pMap = pExpression->GetParamVar();
				CMapVariabile *pMv = pex->GetParamVar();
				//--------------------------------------------------
				if (pMv && pMap)
				{
					CString key;
					CValue *cvalue;
					CValue *pval;
					POSITION pos;
					pos = pMv->GetStartPosition();
					while(pos)
					{
						pMv->GetNextAssoc(pos,key,cvalue);
						if (pMap->Lookup(key,pval))
						{
							((CNumericValue*)pval)->SetValueOnly(cvalue->GetValue());
						}
					}
					//=====================================================================
				}
			}
		}
		CString cs = pExpression->GetName();
		m_EditEidolon.ShowWindow(SW_SHOW);

		CDlgNotesAndEidolon* pDlgNotes = pParentDlg->GetDlgNotes();
		CDlgNotesAndEidolon* pDlgParam = pParentDlg->GetDlgParam();
		if( pDlgNotes != NULL && 
			pDlgNotes->IsWindowVisible() )
		{
			pDlgNotes->SetNotes(pExpression->GetNotes(), pExpression->GetName());
		}

		if( m_EditEidolon.m_hWnd != NULL )
		{		
			CString strText;
			strText.Format("%s",pExpression->GetEidolon());
			if( !strText.IsEmpty() )
			{
				m_EditEidolon.SetText(strText,pExpression->GetParamVar(),FALSE);
			}
			else
			{
				CStringArray* pArray = pExpression->GetDefEidolon();
				if(pArray->GetSize() <= 1)
				{
					pArray = NULL;
				}
				m_EditEidolon.SetText(pArray,pExpression->GetParamVar(),FALSE);
			}
			m_EditEidolon.Invalidate();
		}
	}

	return 0;
}