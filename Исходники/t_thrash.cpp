void TestDistribution(TRandom& aRandom, TInt aSamples)
	{
	TUint32* data = new TUint32[aSamples];
	test_NotNull(data);

	TInt i;
	TReal mean = 0.0;
	for (i = 0 ; i < aSamples ; ++i)
		{
		data[i] = aRandom.Next();
		mean += (TReal)data[i] / aSamples;
		}

	TReal sum2 = 0.0;
	for (i = 0 ; i < aSamples ; ++i)
		{
		TReal d = (TReal)data[i] - mean;
		sum2 += d * d;
		}
	TReal variance = sum2 / (aSamples - 1);

	test.Printf(_L("  mean == %f\n"), mean);
	test.Printf(_L("  variance == %f\n"), variance);

	delete [] data;
	}