void nGraphics::Render()
{
	// Check if we have a valid render device, if not we don't have anything to render with
	if(!m_pDevice)
		return;

	HRESULT hr = NULL;

	// Check if device ok
	if(FAILED(hr = m_pDevice->TestCooperativeLevel()))
	{
		// Yield some CPU time to other processes
		Trace(__FUNCTION__" Sleeping on test coop level (100 ms).\n");
		Sleep(100);

		// The device has been lost but cannot be reset at this time. 
		// Therefore, rendering is not possible and we'll have to return 
		// and try again at a later time.
		if(hr == D3DERR_DEVICELOST)
		{
			nMainFrame::LastError("Display Device lost.");
			Trace(__FUNCTION__" Display Device lost.\n");
			return;
		}

		// The device has been lost but it can be reset at this time. 
		if(hr == D3DERR_DEVICENOTRESET)
		{
			// If the device can be restored, the application prepares the 
			// device by destroying all video-memory resources and any 
			// swap chains. 
			this->InvalidateDeviceObjects();

			if(FAILED(m_pDevice->Reset(&m_PresentParameters)))
			{
				nMainFrame::LastError("Failed to reset Display Device.");
				Trace(__FUNCTION__" Failed to reset Display Device.\n");
				return;
			}

			Trace(__FUNCTION__" Display Device reset.\n");

			// Finally, a lost device must re-create resources (including  
			// video memory resources) after it has been reset.

			this->RestoreDeviceObjects();
		}
	}

	// Clear the screen with the backgroun color
	m_pDevice->Clear(0,0,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,COLOR_BACKGROUND,1.0f,0);

	// Begin the scene
	if(SUCCEEDED(m_pDevice->BeginScene()))
	{
		// Begin sprite drawing
		SpriteBegin();

		// Draw the game
		nGetInstance()->GetGame()->Render();

		// Draw the status text
		DrawStatusText();

		// End 2D drawing
		SpriteEnd();

		// End the scene
		m_pDevice->EndScene();
	}

	// Present the scene to the user
	m_pDevice->Present(0,0,0,0);
}