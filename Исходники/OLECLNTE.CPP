void WaitOleNotBusy( OLESTATUS oleStatus, LPOLEOBJECT lpObject ,
			unsigned line, char * file )
{
	MSG msg;
	if ( oleStatus == OLE_WAIT_FOR_RELEASE )
	{
		while ( ( oleStatus = OleQueryReleaseStatus( lpObject )) == OLE_BUSY )
		{
			if ( GetMessage( &msg , NULL, NULL, NULL ))
			{
				TranslateMessage( &msg );
				DispatchMessage(  &msg );
			}
		}
		if ( oleStatus == OLE_OK || oleStatus == OLE_ERROR_OBJECT ) return;
	}
	CheckOleError( oleStatus, line, file );
}