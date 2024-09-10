static void ScaleLogFont(LPLOGFONT plf, const CDC& dcFrom, const CDC& dcTo)
	// helper to scale log font member from one DC to another!
{
	plf->lfHeight = MulDiv(plf->lfHeight,
		dcTo.GetDeviceCaps(LOGPIXELSY), dcFrom.GetDeviceCaps(LOGPIXELSY));
	plf->lfWidth = MulDiv(plf->lfWidth,
		dcTo.GetDeviceCaps(LOGPIXELSX), dcFrom.GetDeviceCaps(LOGPIXELSX));
}