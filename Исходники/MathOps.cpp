bool EqualRel(float a, float b, float maxRelError)
{
	if (a == b) return true; // Handles the special case where a and b are both zero.
	float relativeError = Abs((a-b)/Max(a, b));
	return relativeError <= maxRelError;
}