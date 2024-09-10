static void
UpdateHue(AG_HSVPal *pal, int x, int y)
{
	float h;

	h = Atan2((float)y, (float)x);
	if (h < 0) {
		h += (float)(2*AG_PI);
	}
	AG_SetFloat(pal, "hue", h/(2*AG_PI)*360.0);

	UpdatePixelFromHSVA(pal);
	AG_PostEvent(NULL, pal, "h-changed", NULL);
	pal->flags |= AG_HSVPAL_DIRTY;
	AG_Redraw(pal);
}