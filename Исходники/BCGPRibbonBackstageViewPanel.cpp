//**********************************************************************************
void CBCGPRibbonBackstageViewPanel::SelectView(CBCGPBaseRibbonElement* pElem)
{
	ASSERT_VALID(this);

	m_pNewSelected = NULL;

	if (pElem == NULL)
	{
		return;
	}

	ASSERT_VALID(pElem);

	if (pElem->IsDisabled())
	{
		return;
	}

	if (pElem != m_pSelected && pElem->GetBackstageAttachedView() != NULL)
	{
		if (m_pSelected != NULL)
		{
			ASSERT_VALID(m_pSelected);

			if (m_pMainButton->GetParentRibbonBar () != NULL)
			{
				ASSERT_VALID (m_pMainButton->GetParentRibbonBar ());

				m_PageTransitionEffect = m_pMainButton->GetParentRibbonBar ()->GetBackstagePageTransitionEffect();
				m_nPageTransitionTime = m_pMainButton->GetParentRibbonBar ()->GetBackstagePageTransitionTime();
			}

			if (m_bSelectedByMouseClick && m_PageTransitionEffect != BCGPPageTransitionNone && !globalData.IsHighContastMode())
			{
				m_bSelectedByMouseClick = FALSE;

				CBCGPRibbonBackstageViewItemForm* pForm1 = DYNAMIC_DOWNCAST(CBCGPRibbonBackstageViewItemForm, m_pSelected->GetBackstageAttachedView());
				if (pForm1 != NULL && pForm1->m_pWndForm->GetSafeHwnd() != NULL)
				{
					HWND hwndPanel = GetParentMenuBar()->GetSafeHwnd();
					GetParentMenuBar()->SetRedraw(FALSE);

					CBCGPRibbonBackstageViewItemForm* pForm2 = DYNAMIC_DOWNCAST(CBCGPRibbonBackstageViewItemForm, pElem->GetBackstageAttachedView());
					if (pForm2 != NULL && hwndPanel != NULL)
					{
						if (pForm2->m_pWndForm == NULL)
						{
							pForm2->m_pWndForm = pForm2->OnCreateFormWnd();
						}

						if (pForm2->m_pWndForm->GetSafeHwnd() != NULL)
						{
							m_pNewSelected = pElem;

							ReposActiveForm();

							pForm1->m_pWndForm->ShowWindow(SW_HIDE);
							pForm2->m_pWndForm->ShowWindow(SW_HIDE);

							CSize szPageMax(m_rect.Width(), 0);

							m_clrFillFrame = CBCGPVisualManager::GetInstance()->IsRibbonBackstageWhiteBackground() ?
								RGB(255, 255, 255) : globalData.clrBarFace;

							m_pNewSelected->m_bIsChecked = TRUE;
							m_pSelected->m_bIsChecked = FALSE;

							if (StartPageTransition(hwndPanel,
								pForm1->m_pWndForm->GetSafeHwnd(), pForm2->m_pWndForm->GetSafeHwnd(),
								m_pSelected->GetRect().top > pElem->GetRect().top, CSize(0, 0), szPageMax))
							{
								RedrawElement(m_pSelected);
								return;
							}

							GetParentMenuBar()->SetRedraw(TRUE);
						}
					}
				}
			}

			CBCGPBaseRibbonElement* pView = m_pSelected->GetBackstageAttachedView();
			if (pView != NULL)
			{
				ASSERT_VALID(pView);
				pView->SetRect(CRect(0, 0, 0, 0));
				pView->OnAfterChangeRect(NULL);
			}

			m_pSelected->m_bIsChecked = FALSE;
			RedrawElement(m_pSelected);
		}

		m_pSelected = pElem;
		m_pSelected->m_bIsChecked = TRUE;

		ReposActiveForm();
		AdjustScrollBars();
		ReposActiveForm();

		RedrawElement(m_pSelected);
	}
}