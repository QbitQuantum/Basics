size_t hundredNanoSecondsToFrames( ::REFERENCE_TIME timeHundredNs, size_t sampleRate )
{
	return lround( (double)sampleRate * (double)timeHundredNs * 0.0000001 );
}