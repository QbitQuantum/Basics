void CExtChildResizablePropertySheet::_TrickSyncActviveChild()
{
CPropertyPage * pWnd = CPropertySheet::GetActivePage();
CTabCtrl * pTabCtrl = CPropertySheet::GetTabControl();
	if(		pWnd != NULL
		&&	pWnd->GetSafeHwnd() != NULL
		&&	::IsWindow( pWnd->GetSafeHwnd() )
		&&	pTabCtrl != NULL
		&&	pTabCtrl->GetSafeHwnd() != NULL
		&&	::IsWindow( pTabCtrl->GetSafeHwnd() )
		)
	{

		if( !m_bTabStylesInitialized )
		{
			m_bTabStylesInitialized = true;
			DWORD dwStylesRemove = 0L;
			DWORD dwStylesAdd = 0L;
			if( m_bInitTabSingleLine )
			{
				dwStylesRemove |= TCS_MULTILINE;
				dwStylesAdd |= TCS_SINGLELINE;
			}
			if( m_bInitTabButtons )
			{
				dwStylesAdd |= TCS_BUTTONS;
				if( m_bInitTabButtonsFlat )
					dwStylesAdd |= TCS_FLATBUTTONS;
			}
			if( dwStylesRemove != 0 || dwStylesAdd != 0 )
				pTabCtrl->ModifyStyle(
					dwStylesRemove,
					dwStylesAdd,
					SWP_FRAMECHANGED
					);
			if( m_bInitTabButtons && m_bInitTabButtonsFlat && m_bInitTabSeparatorsFlat )
				pTabCtrl->SetExtendedStyle( TCS_EX_FLATSEPARATORS, TCS_EX_FLATSEPARATORS );
		}
		
		RECT lpRect;
		GetClientRect(&lpRect);
		// dirty fix of the access vialation bug of
		// the tab control with single item when item's
		// width/height is same as tab control width/height
		__try
		{
			pTabCtrl->AdjustRect(FALSE, &lpRect);
		}
		__except( EXCEPTION_EXECUTE_HANDLER )
		{
			lpRect.right ++;
			lpRect.bottom ++;
			__try
			{
				pTabCtrl->AdjustRect(FALSE, &lpRect);
			}
			__except( EXCEPTION_EXECUTE_HANDLER )
			{
			}
		}
		pWnd->MoveWindow(&lpRect, TRUE);   
	}
}		