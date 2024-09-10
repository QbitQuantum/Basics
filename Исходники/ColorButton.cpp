static BOOL onWM_COMMAND(uiControl *c, HWND hwnd, WORD code, LRESULT *lResult)
{
	uiColorButton *b = uiColorButton(c);
	HWND parent;
	struct colorDialogRGBA rgba;

	if (code != BN_CLICKED)
		return FALSE;

	parent = GetAncestor(b->hwnd, GA_ROOT);		// TODO didn't we have a function for this
	rgba.r = b->r;
	rgba.g = b->g;
	rgba.b = b->b;
	rgba.a = b->a;
	if (showColorDialog(parent, &rgba)) {
		b->r = rgba.r;
		b->g = rgba.g;
		b->b = rgba.b;
		b->a = rgba.a;
		invalidateRect(b->hwnd, NULL, TRUE);
		(*(b->onChanged))(b, b->onChangedData);
	}

	*lResult = 0;
	return TRUE;
}