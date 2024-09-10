// Windows procedure override.
LRESULT Brainchild::WindowProc( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  // Evaluate the message...
	switch ( uMsg )
	{
		case	WM_KEYDOWN:
      /*if (wParam == 13)   // Return key
        m_pOwner->m_pFrame->SendMessage(WM_COMMAND, IDM_OPEN_SELECTED_PATH);*/

      // Pass on all keys except the Context menu key.
			if ( wParam != 0x5D )
				break;

		case	WM_RBUTTONUP:
		{
			// Open the context menu at the cursor position.
			ClsPoint pt;
			GetCursorPos( pt );
			TrackPopupMenuEx( m_pOwner->m_pFrame->m_ContextMenu, TPM_LEFTBUTTON | TPM_RIGHTBUTTON, pt.X(), pt.Y(), *m_pOwner->m_pFrame, NULL );

			// If we got here because of a Context menu key
			// we return so that the brainchild control does
			// not get a chance to process it.
			if ( uMsg == WM_KEYDOWN && wParam == 0x5D ) return 0;
			break;
		}
	}
	return ClsBrainchild::WindowProc( uMsg, wParam, lParam );
}