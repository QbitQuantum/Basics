/*
** VG_RestoreGamma
*/
void VG_RestoreGamma( void )
{
	HDC hDC;

	hDC = GetDC( GetDesktopWindow() );

	if (deviceSupportsGamma)
	{
		SetDeviceGammaRamp(hDC, oldHardwareGamma);
	}

	ReleaseDC(GetDesktopWindow(), hDC);
}