bool AP_Win32App::handleModelessDialogMessage( MSG * msg )
{
	int iCounter;
	HWND hWnd = NULL;

	// Try to knock off the easy case quickly
	if( m_IdTable[ 0 ].id == -1 )
		return false;

    for( iCounter = 0; iCounter <= NUM_MODELESSID; iCounter++ )
	{
		if( m_IdTable[ iCounter ].id != -1 )
		{
			hWnd = (HWND) m_IdTable[ iCounter ].pDialog->pGetWindowHandle();

			if( hWnd && IsDialogMessageW( hWnd, msg ) )
				return true;
		}
		else
			break;
	}

	return false;
}