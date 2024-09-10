BOOL EnableBuddyButton( HWND hwndEdit, HWND hwndButton, UINT uStyle )
{
	//
	//	Quick check to amke sure our parameters are good
	if( uStyle == BBS_LEFT || uStyle == BBS_RIGHT )
	{
		if( IsWindow( hwndEdit ) && IsWindow( hwndButton ) )
		{
			//
			//	Subclass the edit control so we can catch some handy messages
			FARPROC lpfnWndProc = reinterpret_cast<FARPROC>( SetWindowLong( hwndEdit, GWL_WNDPROC, (LONG) SubClassedProc ) );
			ASSERT( lpfnWndProc != NULL );
			VERIFY( ::SetProp( hwndEdit, g_szOldProc, reinterpret_cast<HANDLE>( lpfnWndProc ) ) );

			//
			//	Create our data object. We later give this to our subclassed edit control so we can 
			CData *pData = new CData;
			pData->m_uStyle = uStyle;

			CRect rcButton;
			::GetWindowRect( hwndButton, rcButton );

			pData->m_uButtonWidth = rcButton.Width();
			pData->m_hwndButton = hwndButton;

			VERIFY( ::SetProp( hwndEdit, g_szData, reinterpret_cast<HANDLE>( pData ) ) );

			//
			//	Doing this forces our edit window to pay attention to our change in it's client size
			SetWindowPos( hwndEdit, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED );

			return TRUE;
		}
		else
		{
			//
			//	Set the last error to be something meaningful
			SetLastErrorEx( ERROR_INVALID_WINDOW_HANDLE, SLE_ERROR );
		}
	}
	else
	{
		//
		//	Set the last error to be something meaningful
		SetLastErrorEx( ERROR_INVALID_DATA, SLE_ERROR );
	}
	return FALSE;
}