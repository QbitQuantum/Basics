void LLModalDialog::centerOnScreen()
{
	LLVector2 window_size = LLUI::getWindowSize();
	centerWithin(LLRect(0, 0, llround(window_size.mV[VX]), llround(window_size.mV[VY])));
}