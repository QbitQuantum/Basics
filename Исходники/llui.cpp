//static
void LLUI::glPointToScreen(S32 gl_x, S32 gl_y, S32 *screen_x, S32 *screen_y)
{
	*screen_x = llround((F32)gl_x / getScaleFactor().mV[VX]);
	*screen_y = llround((F32)gl_y / getScaleFactor().mV[VY]);
}