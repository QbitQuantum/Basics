//__________________________________________________________________
void _HYPlatformGraphicPane::_InvertRect (_HYRect& rct)
{
	Rect r = HYRect2Rect (rct);
	InvertRect (&r);
}