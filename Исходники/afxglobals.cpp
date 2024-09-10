BOOL AFX_GLOBAL_DATA::IsDwmCompositionEnabled()
{
	// It appears that DwmIsCompositionEnabled can fail if called and
	// then called again after a very short time, so use a static var
	// so the last obtained value is returned if the method fails.
	static BOOL bEnabled = FALSE;
	DwmIsCompositionEnabled(&bEnabled);
	return bEnabled;
}