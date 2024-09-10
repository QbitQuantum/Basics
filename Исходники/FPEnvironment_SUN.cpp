float FPEnvironmentImpl::copySignImpl(float target, float source)
{
	return (float) copysign(target, source);
}