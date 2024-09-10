void CLineDrawer::UpdateLineStipple()
{
	stippleTimer += (gu->lastFrameTime * cmdColors.StippleSpeed());
	stippleTimer = fmodf(stippleTimer, (16.0f / 20.0f));
}