/*
** WG_RestoreGamma
*/
void WG_RestoreGamma( void ) {
	if ( glConfig.deviceSupportsGamma ) {
		if ( qwglSetDeviceGammaRamp3DFX ) {
			qwglSetDeviceGammaRamp3DFX( glw_state.hDC, s_oldHardwareGamma );
		} else
		{
			HDC hDC;

			hDC = GetDC( GetDesktopWindow() );
			SetDeviceGammaRamp( hDC, s_oldHardwareGamma );
			ReleaseDC( GetDesktopWindow(), hDC );
		}
	}
}