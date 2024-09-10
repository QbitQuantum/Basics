static void static_WindowSmooth(const SCORE Score[], unsigned uCount, unsigned uWindowLength,
  SCORE SmoothScore[], double dCeil)
	{
#define	Ceil(x)	((SCORE) ((x) > dCeil ? dCeil : (x)))

	if (1 != uWindowLength%2)
		Quit("WindowSmooth=%u must be odd", uWindowLength);

	if (uCount <= uWindowLength)
		{
		for (unsigned i = 0; i < uCount; ++i)
			SmoothScore[i] = 0;
		return;
		}

	const unsigned w2 = uWindowLength/2;
	for (unsigned i = 0; i < w2; ++i)
		{
		SmoothScore[i] = 0;
		SmoothScore[uCount - i - 1] = 0;
		}

	SCORE scoreWindowTotal = 0;
	for (unsigned i = 0; i < uWindowLength; ++i)
		{
		scoreWindowTotal += Ceil(Score[i]);
		}

	for (unsigned i = w2; ; ++i)
		{
		SmoothScore[i] = scoreWindowTotal/uWindowLength;
		if (i == uCount - w2 - 1)
			break;

		scoreWindowTotal -= Ceil(Score[i - w2]);
		scoreWindowTotal += Ceil(Score[i + w2 + 1]);
		}
#undef Ceil
	}