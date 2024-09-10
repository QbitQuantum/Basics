void ClientApp::mouseDown( MouseEvent event )
{
	// fake "buttons" to trigger events
	if( infoRect.contains( event.getPos() ) )
	{
		LOG( "testing info logging" );
	}

	if( warnRect.contains( event.getPos() ) )
	{
		LOG_WARN( "testing warn logging" );
	}

	if( errorRect.contains( event.getPos() ) )
	{
		LOG_ERR( "testing error logging" );
	}

	if( eventRect.contains( event.getPos() ) )
	{
		AMPMClient::get()->sendEvent( "category", "action", "label", 10 );
	}

	if( crashRect.contains( event.getPos() ) )
	{
		quit();
	}
}