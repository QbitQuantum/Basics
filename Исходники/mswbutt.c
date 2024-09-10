void wButtonSetLabel(
		wButton_p b,
		const char * label )
{
	if ((b->option&BO_ICON) == 0) {
		/*b->labelStr = label;*/
		SetWindowText( b->hWnd, label );
	} else {
		b->icon = (wIcon_p)label;
	}
	InvalidateRgn( b->hWnd, NULL, FALSE );
}