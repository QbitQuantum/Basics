	BOOL OGLWindow::queryNewPalette()
	{
		if (hRC_ && hPalette_)
		{	
			wglMakeCurrent(hDC (), hRC_);
			UnrealizeObject(hPalette_);
			SelectPalette(hDC (), hPalette_, FALSE);
			RealizePalette(hDC ());

			return TRUE;
		}
		return FALSE;
	}