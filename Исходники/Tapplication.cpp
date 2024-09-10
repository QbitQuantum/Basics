void Tapplication::BlankScreen()
{
	TRACE("Blanking screen\n");
	TAP_Osd_FillBox(screenRgn, 0, 0, MAX_SCREEN_X, MAX_SCREEN_Y, COLOR_None);
}