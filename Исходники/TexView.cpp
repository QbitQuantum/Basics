void TexView::AttachedToWindow()
{
	SetViewColor(prefs->bg_color);
	SetColorSpace(B_RGB32);
	BTextView::AttachedToWindow();
	MakeFocus(true);
}