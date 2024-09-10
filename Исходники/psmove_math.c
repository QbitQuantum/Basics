//-- public methods -----
float clampf(float x, float lo, float hi)
{
	return fminf(fmaxf(x, lo), hi);
}