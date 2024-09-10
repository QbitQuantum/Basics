//
//	timer - used to animate the fade in/out of the transparent window
//
LRESULT DockPanel_Timer(DOCKPANEL *dpp, UINT_PTR id)
{
	extern HWND hwndAnimPanel;
	HWND hwndParam = (HWND)id;

	// get current alpha value
	BYTE alpha = (BYTE)GetWindowLongPtr(hwndParam, GWLP_USERDATA);
	BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, -1, AC_SRC_ALPHA };		

	if(hwndAnimPanel != hwndParam || alpha == 0)
	{
		KillTimer(dpp->hwndPanel, id);
		DestroyWindow(hwndParam);
		return 0;
	}

	// adjust alpha value towards '0'
	alpha = alpha < 24 ? 0 : alpha - 24;
	SetWindowLongPtr(hwndParam, GWLP_USERDATA, alpha);

	// update the layered window transparency
	blendPixelFunction.SourceConstantAlpha = alpha;
	UpdateLayeredWindow(hwndParam, 0, 0, 0, 0, 0, 0, &blendPixelFunction, ULW_ALPHA);

	return 0;
}