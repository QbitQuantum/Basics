GLDEF_C TInt E32Main()
	{
	test.Title();
	test.Start(_L("Create chunk"));
	RChunk c;
	TInt r=c.CreateDisconnectedLocal(0,0x1000,0x100000);
	test(r==KErrNone);
	r=c.Commit(0x10000,0x1000);
	test(r==KErrNone);
	TUint8* pBuf1=c.Base();
	TUint8* pBuf2=pBuf1+0x10000;

	TInt s;
	TInt d;
	TInt l;

	for (l=1; l<300; l+=3)
		{
		for (s=0; s<=4096-l; s+=227)
			{
			test.Printf(_L("\ns=%4d l=%4d: "),s,l);
			for (d=0; d<=4096-l; d+=229)
				{
				DoTest(pBuf1,pBuf2,4096,s,d,l,0);
				DoTest(pBuf1,pBuf2,4096,s,d,l,1);
				}
			}
		}

	for (l=1; l<300; l+=3)
		{
		for (s=4096-l; s>=0; s-=227)
			{
			test.Printf(_L("\ns=%4d l=%4d: "),s,l);
			for (d=4096-l; d>=0; d-=229)
				{
				DoTest(pBuf1,pBuf2,4096,s,d,l,0);
				DoTest(pBuf1,pBuf2,4096,s,d,l,1);
				}
			}
		}
	
	for (l=1; l<400; l+=((l<=64)?1:3) )
		{
		test.Printf(_L("\nOverlap test: l=%4d: "),l);
		for (s=32; s<=4096-32-l; s+=101)	// want s to take all values 0...31 modulo 32
			{
			for (d=s-32; d<=s+32; ++d)
				{
				DoOverlapTest(pBuf1,pBuf2,4096,s,d,l);
				}
			}
		}
	
	c.Close();
	test.End();
	return 0;
	}