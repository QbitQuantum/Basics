// Create the windowed direct draw device for Direct3D to display with.
void BoidsWin::createWinDevice( )
{
	// Create the Direct Draw clipper
	DirectDrawCreateClipper( 0, &clipper, NULL );
	clipper -> SetHWnd( 0, m_hWnd );


	// Create the D3DRM drawing device.
	CRect size;
	GetClientRect( &size );

	if ( showControlPanel )  // Make space for the control panel.
	{
		size.right -= CONTROL_PANEL_SIZE;
	}

	d3drm -> CreateDeviceFromClipper( clipper, NULL,
							size.right, size.bottom, &device );


	// If the scene is not constructed, set the device to -
	// - the default render style and then create the scene.
	if ( scene == NULL )
	{
		// Set the initial render style.
		device -> SetQuality( DEFAULT_RENDER_STYLE );

		// IMPORTANT STEP: Set up all the simulation's graphics.
		createScene( );
	}
	else
	{
		// The scene has already been created, -
		// - just reconfigure the device and viewport.
		device -> SetQuality( renderStyle );  // Restore the render style.
		// Create the viewport.
		d3drm -> CreateViewport( device, camera, 0, 0,
				device -> GetWidth( ), device -> GetHeight( ), &viewPort );
		// Set the range of vision, default is 100.
		viewPort -> SetBack( D3DVALUE( VIEWPORT_BACK_DISTANCE ) );
	}
}