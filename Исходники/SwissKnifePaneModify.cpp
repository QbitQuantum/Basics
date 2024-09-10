LRESULT CSwissKnifePaneModify::OnGridNotify( WPARAM wParam, LPARAM lParam )
{
	if (wParam == XTP_PGN_INPLACEBUTTONDOWN)
	{
		CXTPPropertyGridInplaceButton* pButton = (CXTPPropertyGridInplaceButton*)lParam;
		if (pButton->GetItem()->GetID() == 510 && pButton->GetID() == XTP_ID_PROPERTYGRID_EXPANDBUTTON) // 2 Buttons
		{
			AfxMessageBox(_T("Expand button"));
			return TRUE;
		}
	}

	if (wParam == XTP_PGN_SORTORDER_CHANGED)
	{
		UpdateData(FALSE);
		TRACE(_T("SortOrder Changed.\n"));
	}
	if (wParam == XTP_PGN_ITEMVALUE_CHANGED)
	{
		CXTPPropertyGridItem* pItem = (CXTPPropertyGridItem*)lParam;
		TRACE(_T("Value Changed. Caption = %s, ID = %i, Value = %s\n"), pItem->GetCaption(), pItem->GetID(), pItem->GetValue());

		if (DYNAMIC_DOWNCAST(CXTPPropertyGridItemEnum, pItem))
		{
			if (pItem->GetMetrics(TRUE, FALSE))
			{
				pItem->GetMetrics(TRUE, FALSE)->m_nImage = ((CXTPPropertyGridItemEnum*)pItem)->GetEnum();
			}
		}


		if( pItem->GetID() == ID_CREATE_PHYSIC_LAYER)
		{
			CXTPPropertyGridItemBool* itembool = (CXTPPropertyGridItemBool*)pItem;
			if (m_currTarget && itembool->GetBool())
			{
				if (!m_currTarget->getPhysicLayer())
				{
#ifdef OS_WIN32

						IGameObjectPhysicLayer* pPhysicLayer = gEnv->pPhysics->CreatePhysicLayer();
						m_currTarget->setGameObjectLayer(pPhysicLayer);
						pPhysicLayer->createStatic();

						
#endif

				}
			}
		}
	}
	if (wParam == XTP_PGN_SELECTION_CHANGED)
	{
		CXTPPropertyGridItem* pItem = (CXTPPropertyGridItem*)lParam;
		if (pItem)
		{
			if (pItem->IsKindOf(RUNTIME_CLASS(CXTPPropertyGridItemColor)))
			{
				TRACE(_T("Color Item. Selection Changed. Item = %s\n"), pItem->GetCaption());
			}
		}
	}
	if (wParam == XTP_PGN_EDIT_CHANGED)
	{
		CXTPPropertyGridInplaceEdit* pEdit = DYNAMIC_DOWNCAST(CXTPPropertyGridInplaceEdit, (CWnd*)lParam);
		if (pEdit && pEdit->GetItem())
		{
			// Custom Validation
			// Custom Validation
			if (pEdit->GetItem()->GetCaption() == _T("ItemsInMRUList"))
			{
				CString str;
				pEdit->CEdit::GetWindowText(str);

				int i = _ttoi(str);
				if (i > 20)
				{
					MessageBeep((UINT)-1);
					pEdit->SetSel(0, -1);
					pEdit->ReplaceSel(_T("20"));
				}
			}
		}
	}
	return 0;
}