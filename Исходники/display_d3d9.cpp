	virtual void repaint()
	{
		if ( retry_count && !restore_objects() ) return;

		lpdev->Clear( 0L, NULL, D3DCLEAR_TARGET, 0x000000ff, 1.0f, 0L );

		HRESULT rv = lpdev->BeginScene();

		if( SUCCEEDED( rv ) )
		{
			set_vertex( 0, 0, input_width, input_height, surface_width, surface_height, 0, 0, rcWindow.right, rcWindow.bottom );
			lpdev->SetTexture( 0, lptex );
			lpdev->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
			lpdev->EndScene();

			if ( lpdev->Present( NULL, NULL, NULL, NULL ) == D3DERR_DEVICELOST ) retry_count = 60;
		}
		else retry_count = 60;

		ValidateRect( hWnd, & rcWindow );
	}