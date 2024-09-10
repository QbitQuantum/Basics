//**************************************************************************
void CBCGPRibbonComboBox::DropDownList ()
{
	ASSERT_VALID (this);

	if (IsDisabled ())
	{
		return;
	}

	if (m_pWndEdit->GetSafeHwnd () != NULL && !m_pWndEdit->IsWindowVisible ())
	{
		return;
	}

	if (CBCGPPopupMenu::GetActiveMenu () != NULL)
	{
		if (CBCGPPopupMenu::GetActiveMenu ()->GetMenuBar () != m_pParentMenu)
		{
			CBCGPPopupMenu::GetActiveMenu ()->SendMessage (WM_CLOSE);
			return;
		}
	}

	CBCGPBaseRibbonElement::OnShowPopupMenu ();

	if (m_bIsCalculator)
	{
		if (m_pCalcPopup != NULL)
		{
			m_pCalcPopup->SendMessage (WM_CLOSE);
			m_pCalcPopup = NULL;

			SetDroppedDown(NULL);
		}
		else
		{
			if (CBCGPPopupMenu::GetActiveMenu () != NULL)
			{
				if (CBCGPPopupMenu::GetActiveMenu ()->GetMenuBar () != m_pParentMenu)
				{
					CBCGPPopupMenu::GetActiveMenu ()->SendMessage (WM_CLOSE);
					return;
				}
			}

			CBCGPBaseRibbonElement::OnShowPopupMenu ();

			double dblValue = 0.;

			CString strValue = GetEditText ();
			if (!strValue.IsEmpty ())
			{
				strValue.Replace (_T(','), _T('.'));
	#if _MSC_VER < 1400
				_stscanf (strValue, _T("%lf"), &dblValue);
	#else
				_stscanf_s (strValue, _T("%lf"), &dblValue);
	#endif
			}

			m_pCalcPopup = new CBCGPCalculatorPopup (dblValue, 0, this);
			m_pCalcPopup->m_bAutoDestroyParent = FALSE;
			m_pCalcPopup->SetParentRibbonElement (this);

			CBCGPCalculator* pCalc = DYNAMIC_DOWNCAST (CBCGPCalculator, m_pCalcPopup->GetMenuBar());
			if (pCalc != NULL)
			{
				ASSERT_VALID (pCalc);

				if (!m_lstCalcAdditionalCommands.IsEmpty ())
				{
					pCalc->SetAdditionalCommands (m_lstCalcAdditionalCommands);
				}

				if (!m_lstCalcExtCommands.IsEmpty ())
				{
					pCalc->SetExtendedCommands (m_lstCalcExtCommands);
				}

				if (!m_strCalcDisplayFormat.IsEmpty())
				{
					pCalc->SetDisplayFormat(m_strCalcDisplayFormat);
				}
			}

			CRect rectWindow;
			m_pWndEdit->GetWindowRect (rectWindow);

			if (!m_pCalcPopup->Create (m_pWndEdit, rectWindow.left - m_szMargin.cx, rectWindow.bottom + m_szMargin.cy, NULL, TRUE))
			{
				ASSERT (FALSE);
				m_pCalcPopup = NULL;
			}
			else
			{
				SetDroppedDown(m_pCalcPopup);

				m_pCalcPopup->GetMenuBar()->SetFocus ();
				
				CRect rect;
				m_pCalcPopup->GetWindowRect (&rect);
				m_pCalcPopup->UpdateShadow (&rect);
			}
		}

		return;
	}

	CBCGPDropDownList* pList = new CBCGPDropDownList (this);
	pList->SetParentRibbonElement (this);

	int i = 0;
	for (POSITION pos = m_lstItems.GetHeadPosition (); pos != NULL; i++)
	{
		CString strItem = m_lstItems.GetNext (pos);
		pList->AddString (strItem);

		if (m_bHasEditBox && strItem == m_strEdit)
		{
			m_iSelIndex = i;
		}
	}

	pList->SetCurSel (m_iSelIndex);
	pList->SetMaxHeight (m_nDropDownHeight);
	pList->SetMinWidth (m_rect.Width ());

	CWnd* pWndParent = GetParentWnd ();
	if (pWndParent == NULL)
	{
		ASSERT (FALSE);
		return;
	}

	const BOOL bIsRTL = (pWndParent->GetExStyle () & WS_EX_LAYOUTRTL);

	CRect rect = m_rectCommand.IsRectEmpty () ? m_rect : m_rectCommand;
	pWndParent->ClientToScreen (&rect);

	SetDroppedDown (pList);

	if (m_pParent != NULL)
	{
		ASSERT_VALID (m_pParent);
		m_pParent->HighlightPanel (NULL, CPoint (-1, -1));
	}

	if (m_pWndEdit->GetSafeHwnd () != NULL)
	{
		m_pWndEdit->SetFocus ();
		m_pWndEdit->SetSel (0, -1);
	}

	if (m_bResizeDropDownList)
	{
		pList->EnableVertResize (2 * globalData.GetTextHeight ());
	}

	pList->Track (CPoint (
		bIsRTL ? rect.right : rect.left, rect.bottom), pWndParent->GetOwner ());
}