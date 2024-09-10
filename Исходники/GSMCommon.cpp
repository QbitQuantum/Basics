double Clock::systime(const GSM::Time& when) const
{
	ScopedLock lock(mLock);
	const double slotMicroseconds = (48.0 / 13e6) * 156.25;
	const double frameMicroseconds = slotMicroseconds * 8.0;
	int32_t elapsedFrames = when.FN() - mBaseFN;
	if (elapsedFrames<0) elapsedFrames += gHyperframe;
	double elapsedUSec = elapsedFrames * frameMicroseconds + when.TN() * slotMicroseconds;
	double baseSeconds = mBaseTime.sec() + mBaseTime.usec()*1e-6;
	double st = baseSeconds + 1e-6*elapsedUSec;
	return st;
}