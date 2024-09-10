//
// Generic handler for press on any BResultType button.  
// Records which button was pressed, then pops up the result type menu.
// 
void CPageDisplay::OnBResultType( int which_button ) 
{
	CMenu menu;
	CRect button_rect;
	RECT screen_rect;
	int menu_height, menu_x, menu_y;

	// Record which button was pressed, for later use by OnMDisplay().
	selected_button = which_button;

	// This prevents the menu from popping up if the user is "unchecking" the button.
	if ( ( (CButton*)GetDlgItem( BResultType1 + selected_button ) )->GetCheck() ) 
	{
		( (CButton*)GetDlgItem( BResultType1 + selected_button ) )->
			SetCheck( FALSE );
		return;
	}

	// Create the popup menu from the resource.
	VERIFY(menu.LoadMenu(IDR_POPUP_DISPLAY_LIST));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	// Find the first non-child window to be the popup's parent.
	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	// Get the screen coordinates of the button that was pressed.
	GetDlgItem( BResultType1 + selected_button )->GetWindowRect( &button_rect );

	// Position the menu with its upper left corner at the lower left corner of the button.
	menu_x = button_rect.TopLeft().x;
	menu_y = button_rect.BottomRight().y;

	// If the menu would go off the bottom of the screen, make it go *up* from the button instead.
	menu_height = GetSystemMetrics(SM_CYMENUSIZE) * MDisplayNumSubmenus;
	if ( SystemParametersInfo( SPI_GETWORKAREA, 0, &screen_rect, 0) && 
		(menu_y + menu_height > screen_rect.bottom) )
	{
		menu_y = button_rect.TopLeft().y - menu_height + 1;
	}

	// Set the button's visual state to "pressed" as long as the menu is popped up.
	( (CButton*)GetDlgItem( BResultType1 + selected_button ) )->SetCheck( TRUE );

	// Pop up the menu.
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, menu_x, menu_y, pWndPopupOwner);

	// The user's selection (if any) from the pop-up menu will result in a call to one of the 
	// CGalileoView::OnMDisplay...() functions, which will in turn call CPageDisplay::OnMDisplay().

	// Set the button's visual state to "not pressed" after the menu is dismissed.
	( (CButton*)GetDlgItem( BResultType1 + selected_button ) )->SetState( FALSE );
}