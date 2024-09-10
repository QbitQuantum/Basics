void DialogDeclBrowser::OnSize( UINT nType, int cx, int cy ) {
	CRect clientRect, rect;

	LockWindowUpdate();

	CDialog::OnSize( nType, cx, cy );

	GetClientRect( clientRect );

	if ( declTree.GetSafeHwnd() ) {
		rect.left = BORDER_SIZE;
		rect.top = BORDER_SIZE;
		rect.right = clientRect.Width() - BORDER_SIZE;
		rect.bottom = clientRect.Height() - 100;
		declTree.MoveWindow( rect.left, rect.top, rect.Width(), rect.Height() );
	}

	if ( findNameStatic.GetSafeHwnd() ) {
		rect.left = BORDER_SIZE + 2;
		rect.top = clientRect.Height() - 100 + BUTTON_SPACE + 2;
		rect.right = BORDER_SIZE + 80;
		rect.bottom = clientRect.Height() - 76 + 2;
		findNameStatic.MoveWindow( rect.left, rect.top, rect.Width(), rect.Height() );
	}

	if ( findTextStatic.GetSafeHwnd() ) {
		rect.left = BORDER_SIZE + 2;
		rect.top = clientRect.Height() - 78 + BUTTON_SPACE + 2;
		rect.right = BORDER_SIZE + 80;
		rect.bottom = clientRect.Height() - 54 + 2;
		findTextStatic.MoveWindow( rect.left, rect.top, rect.Width(), rect.Height() );
	}

	if ( findNameEdit.GetSafeHwnd() ) {
		rect.left = BORDER_SIZE + 80;
		rect.top = clientRect.Height() - 100 + BUTTON_SPACE;
		rect.right = clientRect.Width() - BORDER_SIZE;
		rect.bottom = clientRect.Height() - 76;
		findNameEdit.MoveWindow( rect.left, rect.top, rect.Width(), rect.Height() );
	}

	if ( findTextEdit.GetSafeHwnd() ) {
		rect.left = BORDER_SIZE + 80;
		rect.top = clientRect.Height() - 78 + BUTTON_SPACE;
		rect.right = clientRect.Width() - BORDER_SIZE;
		rect.bottom = clientRect.Height() - 54;
		findTextEdit.MoveWindow( rect.left, rect.top, rect.Width(), rect.Height() );
	}

	if ( findButton.GetSafeHwnd() ) {
		findButton.GetClientRect( rect );
		int width = rect.Width();
		int height = rect.Height();
		rect.left = BORDER_SIZE;
		rect.top = clientRect.Height() - TOOLBAR_HEIGHT - height;
		rect.right = BORDER_SIZE + width;
		rect.bottom = clientRect.Height() - TOOLBAR_HEIGHT;
		findButton.MoveWindow( rect.left, rect.top, rect.Width(), rect.Height() );
	}

	if ( editButton.GetSafeHwnd() ) {
		editButton.GetClientRect( rect );
		int width = rect.Width();
		int height = rect.Height();
		rect.left = BORDER_SIZE + BUTTON_SPACE + width;
		rect.top = clientRect.Height() - TOOLBAR_HEIGHT - height;
		rect.right = BORDER_SIZE + BUTTON_SPACE + 2 * width;
		rect.bottom = clientRect.Height() - TOOLBAR_HEIGHT;
		editButton.MoveWindow( rect.left, rect.top, rect.Width(), rect.Height() );
	}

	if ( newButton.GetSafeHwnd() ) {
		newButton.GetClientRect( rect );
		int width = rect.Width();
		int height = rect.Height();
		rect.left = BORDER_SIZE + 2 * BUTTON_SPACE + 2 * width;
		rect.top = clientRect.Height() - TOOLBAR_HEIGHT - height;
		rect.right = BORDER_SIZE + 2 * BUTTON_SPACE + 3 * width;
		rect.bottom = clientRect.Height() - TOOLBAR_HEIGHT;
		newButton.MoveWindow( rect.left, rect.top, rect.Width(), rect.Height() );
	}

	if ( reloadButton.GetSafeHwnd() ) {
		reloadButton.GetClientRect( rect );
		int width = rect.Width();
		int height = rect.Height();
		rect.left = BORDER_SIZE + 3 * BUTTON_SPACE + 3 * width;
		rect.top = clientRect.Height() - TOOLBAR_HEIGHT - height;
		rect.right = BORDER_SIZE + 3 * BUTTON_SPACE + 4 * width;
		rect.bottom = clientRect.Height() - TOOLBAR_HEIGHT;
		reloadButton.MoveWindow( rect.left, rect.top, rect.Width(), rect.Height() );
	}

	if ( cancelButton.GetSafeHwnd() ) {
		cancelButton.GetClientRect( rect );
		int width = rect.Width();
		int height = rect.Height();
		rect.left = clientRect.Width() - BORDER_SIZE - width;
		rect.top = clientRect.Height() - TOOLBAR_HEIGHT - height;
		rect.right = clientRect.Width() - BORDER_SIZE;
		rect.bottom = clientRect.Height() - TOOLBAR_HEIGHT;
		cancelButton.MoveWindow( rect.left, rect.top, rect.Width(), rect.Height() );
	}

	if ( statusBar.GetSafeHwnd() ) {
		rect.left = clientRect.Width() - 2;
		rect.top = clientRect.Height() - 2;
		rect.right = clientRect.Width() - 2;
		rect.bottom = clientRect.Height() - 2;
		statusBar.MoveWindow( rect.left, rect.top, rect.Width(), rect.Height() );
	}

	UnlockWindowUpdate();
}