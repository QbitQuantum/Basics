void doCalccPrintSamples(int channel)
{	// no sample buffering - use in single cal mode
	_beginthread(CalccPrintSamples, 0, (void *)channel);
}