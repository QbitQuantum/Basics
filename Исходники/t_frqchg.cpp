void Test1M(const SRatio& aRatio)
	{
	SRatio ratio = aRatio;
	const TInt N = sizeof(MultTestIntegers)/sizeof(MultTestIntegers[0]);
	test.Printf(_L("Testing %d integers\n"), N);
	TInt i;
	for (i=0; i<N; ++i)
		{
		TUint32 I = MultTestIntegers[i];
		TUint32 I0 = I;
		TUint32 I1 = I;
		TInt r0 = RatioMult(aRatio, I0);
		TInt r1 = Driver.RatioMult(ratio, I1);
		if (r0!=KErrNone || r1!=KErrNone)
			{
			if (r0!=r1)
				{
				test.Printf(_L("Return code mismatch r0=%d r1=%d (I=%08x I0=%08x I1=%08x)\n"), r0, r1, I, I0, I1);
				test(0);
				}
			}
		else if (I0!=I1)
			{
			test.Printf(_L("Result mismatch I=%08x I0=%08x I1=%08x\n"), I, I0, I1);
			}
		}
	}