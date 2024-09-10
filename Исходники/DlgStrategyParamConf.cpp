long CDlgStrategyParamConf::LoadCurExp(WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/)
{	
	m_sSingleSel.m_nType = hx_DefMaxValues;

	CDlgFormulaMan* pParentDlg  = (CDlgFormulaMan*)AfxGetMainWnd();
	if( pParentDlg == NULL )
		return 0;

	EnableItem(FALSE);

	if( wParam == CTreeCtrlFormula::YlsBrowser )
	{
		if(m_nType == 1)
		{
			CTreeGroup* pTreeGroup = (CTreeGroup*)lParam;
			//	CString strItem = *(CString*)lParam;
			/*	if( !strItem.CompareNoCase(CTreeCtrlFormula::g_strUnionCondition) )
			{
			m_sSingleSel.m_nType = CExpression::Union;
			m_sSingleSel.m_strExp.Format("%s",CTreeCtrlFormula::g_strUnionCondition);

			m_wndPeriod.ShowWindow(SW_HIDE);
			m_wndPeriodStc.ShowWindow(SW_HIDE);

			m_wndConNotes.ShowWindow(SW_HIDE);
			m_wndCon.ShowWindow(SW_HIDE);
			m_wndStaticCon.ShowWindow(SW_HIDE);

			m_wndCompare.ShowWindow(SW_HIDE);
			m_wndData1.ShowWindow(SW_HIDE);

			m_wndAndOr.ShowWindow(SW_HIDE);
			m_wndData2.ShowWindow(SW_HIDE);
			m_wndMiddle.ShowWindow(SW_HIDE);

			}*/
			//	else if( !strItem.CompareNoCase(CTreeCtrlFormula::g_strJiben) )
			/*	else*/ if( pTreeGroup->m_dwID == CExpression::JiBenMian )
			{
				m_sSingleSel.m_nType = CExpression::JiBenMian;
				m_sSingleSel.m_strExp.Format("%s",CTreeCtrlFormula::g_strJiben);

				m_wndPeriod.ShowWindow(SW_HIDE);

#ifdef _ONLY_SUPPORT_DAYLINE

				m_wndPeriod.SetCurSel(0);
#else

				m_wndPeriod.SetCurSel(5);
#endif
				m_wndPeriodStc.ShowWindow(SW_HIDE);

 				m_wndConNotes.ShowWindow(SW_SHOW);
 				m_wndConNotes.SetWindowText(HS_LANGUAGE("财务指标"));
				m_wndCon.ShowWindow(SW_SHOW);
				m_wndStaticCon.ShowWindow(SW_SHOW);

				m_wndCompare.ShowWindow(SW_SHOW);
				m_wndData1.ShowWindow(SW_SHOW);

				m_wndAndOr.ShowWindow(SW_HIDE);
				m_wndData2.ShowWindow(SW_HIDE);
				m_wndMiddle.ShowWindow(SW_HIDE);

				m_wndData1.ResetContent();
				m_wndData2.ResetContent();

				m_wndCon.ResetContent();
				CDlgCondition::InitCWData(&m_wndCon,YLS_GB_GUBEN_NAME);
				CDlgCondition::InitCWData(&m_wndCon,YLS_Cj_GUBEN_NAME);

				CDlgCondition::InitCondition(&m_wndCompare,4);
			}
		}
	}
	else if( wParam == CCompileEditView::UpdateExpress )
	{
		CDlgFormulaEdit* pDlg = pParentDlg->GetExpDlg();
		if( pDlg != NULL )
		{
			if(pDlg->SendMessage(HX_USER_LOADCUR,wParam,lParam))
			{
				pParentDlg->Enable(FALSE);
				pDlg->ShowWindowEx(SW_SHOWNORMAL);
			}
		}
	}
	else if( wParam == HX_EXPRESSSENTENCE )
	{
		//EnableItem(FALSE);

		CExpression* pExpression = (CExpression*)lParam;
		if( pExpression == NULL )
			return 0;

		//
		if(m_nType == 1)
		{
			m_sSingleSel.m_nType = pExpression->GetExpressType();
			m_sSingleSel.m_strExp.Format("%s",pExpression->GetName());
			CDlgCondition::InitCondition(&m_wndCompare,-1);

			switch ( m_sSingleSel.m_nType )
			{
			case CExpression::Tech:
				{
					//"选出技术指标数值满足下列条件的股票:");

					m_wndPeriod.ShowWindow(SW_SHOW);
#ifdef _ONLY_SUPPORT_DAYLINE

					m_wndPeriod.SetCurSel(0);
#else

					m_wndPeriod.SetCurSel(5);
#endif
					m_wndPeriodStc.ShowWindow(SW_SHOW);

 					m_wndConNotes.ShowWindow(SW_SHOW);
 					m_wndConNotes.SetWindowText(HS_LANGUAGE("指标线"));
					m_wndCon.ShowWindow(SW_SHOW);
					m_wndCon.ResetContent();
					m_wndStaticCon.ShowWindow(SW_SHOW);

					m_wndCompare.ShowWindow(SW_SHOW);
					m_wndData1.ShowWindow(SW_SHOW);

					CValue* valoare = NULL;
					if( CExpression::m_pExternExpression->Lookup(pExpression->GetName(),pExpression->GetExpressType(),valoare) ) // over
					{
						CExpValue* pExpValue = (CExpValue*)valoare;

						BOOL bFree = FALSE;
						CExpression* pCurExpression = pExpValue->GetExp();
						if( pCurExpression && pCurExpression == pExpression )
						{
							if( !pCurExpression->IsCompile() )
							{
								if( !pCurExpression->Compile() )
								{
									bFree = TRUE;
								}
							}
							CArray<CFormulaDrawParam*,CFormulaDrawParam*> ayDraw;
							CString strParam;
							int nCount = pCurExpression->GetDraw(strParam,ayDraw);
							CFormulaDrawParam* pParam;
							if( nCount > 0 )
							{
								for(int i = 0; i < nCount; i++)
								{
									pParam = ayDraw.GetAt(i);
									if( nCount == 1 && CString(pParam->m_strName).IsEmpty() )
									{
										m_wndCon.AddString(CTreeCtrlFormula::g_strFirstTechLine);
									}
									else
									{
										m_wndCon.AddString(pParam->m_strName);
									}
									delete pParam;
								}
							}
							else
							{
								m_wndCon.AddString(CTreeCtrlFormula::g_strFirstTechLine);
							}
							m_wndCon.SetCurSel(m_wndCon.GetCount()-1);

							OnSelchangeCompare();
						}
						if( bFree )
						{
							pExpValue->Free();
						}
					}

				}
				break;
			case CExpression::Condition:
				{
					//"选出满足下列条件的股票:");

					m_sSingleSel.m_SubData.m_cType = FormulaCompareSubData::Condition;

					m_wndPeriod.ShowWindow(SW_SHOW);

#ifdef _ONLY_SUPPORT_DAYLINE

					m_wndPeriod.SetCurSel(0);
#else

					m_wndPeriod.SetCurSel(5);
#endif
					m_wndPeriodStc.ShowWindow(SW_SHOW);

					m_wndConNotes.ShowWindow(SW_HIDE);
					m_wndCon.ShowWindow(SW_HIDE);
					m_wndStaticCon.ShowWindow(SW_HIDE);

					m_wndCompare.ShowWindow(SW_HIDE);
					m_wndData1.ShowWindow(SW_HIDE);

					m_wndAndOr.ShowWindow(SW_HIDE);
					m_wndData2.ShowWindow(SW_HIDE);
					m_wndMiddle.ShowWindow(SW_HIDE);
				}
				break;
			case CExpression::Exchange:
				{
					//"选出交易系统发出以下信号的股票:");

					m_sSingleSel.m_SubData.m_cType = FormulaCompareSubData::Exchange;

					m_wndPeriod.ShowWindow(SW_SHOW);
#ifdef _ONLY_SUPPORT_DAYLINE

					m_wndPeriod.SetCurSel(0);
#else

					m_wndPeriod.SetCurSel(5);
#endif
					m_wndPeriodStc.ShowWindow(SW_SHOW);

 					m_wndConNotes.ShowWindow(SW_HIDE);
 					m_wndConNotes.SetWindowText(HS_LANGUAGE("发出"));
					m_wndCon.ShowWindow(SW_HIDE);
					m_wndStaticCon.ShowWindow(SW_HIDE);

					m_wndCompare.ShowWindow(SW_HIDE);
					m_wndData1.ShowWindow(SW_HIDE);

					m_wndAndOr.ShowWindow(SW_HIDE);
					m_wndData2.ShowWindow(SW_HIDE);
					m_wndMiddle.ShowWindow(SW_HIDE);
				}
				break;
			case CExpression::MoreKLine:
				{
					//"选出五彩Ｋ线发出指示的股票:");

					m_sSingleSel.m_SubData.m_cType = FormulaCompareSubData::MoreKLine;

					m_wndPeriod.ShowWindow(SW_SHOW);
#ifdef _ONLY_SUPPORT_DAYLINE

					m_wndPeriod.SetCurSel(0);
#else

					m_wndPeriod.SetCurSel(5);
#endif
					m_wndPeriodStc.ShowWindow(SW_SHOW);

					m_wndConNotes.ShowWindow(SW_HIDE);
					m_wndCon.ShowWindow(SW_HIDE);
					m_wndStaticCon.ShowWindow(SW_HIDE);

					m_wndCompare.ShowWindow(SW_HIDE);
					m_wndData1.ShowWindow(SW_HIDE);

					m_wndAndOr.ShowWindow(SW_HIDE);
					m_wndData2.ShowWindow(SW_HIDE);
					m_wndMiddle.ShowWindow(SW_HIDE);
				}
				break;
			}
		}

		// 注释/参数修改
// 		CWnd* pWnd = GetDlgItem(IDC_NOTES);
// 		pWnd->ShowWindow(SW_SHOW);
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