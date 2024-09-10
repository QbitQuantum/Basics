/********************************************
GetMargins
	Purpose
		This wraps the GetThemeMargins call, which returns the margins of the area 
		which will be taken up by drawing the theme edge.
	Params
		hwnd	   - the window to draw to, often NULL
		hdc        - the HDC to draw to
		type	   - the cell type to draw
		state      - the state of the cell ( selected, current, etc )
		propId    - the margin type to return
		prc        - the rect to draw to
		XPMARGINS  - an internal struct which copies the MARGINS struct, so this code
					 will work if the XPThemes header files are available or not.
	Return
		A bool to indicate success or failure.
*********************************************/
bool UGXPThemes::GetMargins(HWND hwnd, HDC hdc, UGXPCellType type, UGXPThemeState state, int propID,
		RECT *prc, XPMARGINS *pMargins)
{
	bool success = false;

	if (useThemes)
	{
		UGThemeData * td = LookupThemeData(type, state);

		if (!td)
		{
			return false;
		}

		HANDLE themeHandle = OpenThemeData(hwnd, td->GetThemeName());

		if (!themeHandle)
			return false;

		success = SUCCEEDED(GetThemeMargins(themeHandle, hdc, td->GetPartID(), td->GetStateID(), propID, prc, pMargins));
	}

	return success;
}