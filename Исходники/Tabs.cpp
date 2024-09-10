bool SetTabThemeTexture(HWND Window, bool Enable)
{
	assert(IsWindow(Window));

	if(VisualStylesEnabled())
	{
		return (S_OK == EnableThemeDialogTexture(Window, Enable ? ETDT_ENABLETAB : ETDT_DISABLE));
	}
	return false;
}