int RandomBin::randInt(Stream_type Stream, int minInt, int maxInt)
{
	double randNum = 0;
	int retInt = 0;
	MTRand *streamPtr = GetStream(Stream);
	if (streamPtr != NULL) {
		randNum = streamPtr->rand();
		randNum = randNum * static_cast<double>((maxInt - minInt + 1));
		retInt = static_cast<int>(ceil(randNum)) - 1 + minInt;
		return retInt;
	}
	return 0;
}