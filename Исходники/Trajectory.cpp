float AdInput(UINT channel)
{
	float volts;
	long adcvalue;
	long value;

	CHECKERROR(olDaGetSingleValue(board.hdass, &adcvalue, channel, gain));

	if (encoding != OL_ENC_BINARY) {
		value ^= 1L << (resolution - 1);
		value &= (1L << resolution) - 1;
	}

	volts = ((float)max - (float)min) / (1L << resolution) * adcvalue;// + (float)min;
	olDaReleaseDASS(board.hdass);

	return volts;
}