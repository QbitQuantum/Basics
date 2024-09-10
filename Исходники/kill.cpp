GLDEF_C TInt E32Main()
	{
	test.Title();
	TBuf<256> cmd;
	TFullName fn;
	User::CommandLine(cmd);
	TLex lex(cmd);
	TPtrC threadSpec(lex.NextToken());
	TFindThread ft(threadSpec);
	TExitType exitType=EExitKill;
	TInt exitCode=0;
	if (!lex.Eos())
		{
		TPtrC xtSpec(lex.NextToken());
		TPtrC xc(xtSpec);
		TChar xt0=xtSpec[0];
		if (xt0.IsAlpha())
			{
			xt0.LowerCase();
			if (xt0==TChar('t'))
				exitType=EExitTerminate;
			else if (xt0==TChar('p'))
				exitType=EExitPanic;
			new(&xc) TPtrC(lex.NextToken());
			}
		if (xc.Length())
			{
			TLex lex2(xc);
			lex2.Val(exitCode);
			}
		}
	while (ft.Next(fn)==KErrNone)
		{
		test.Printf(_L("Killing %S\n"),&fn);
		RThread t;
		TInt r=t.Open(ft);
		if (r==KErrNone)
			{
			// FIXME: SHOULD REMOVE CRITICALNESS - WOULD NEED DEVICE DRIVER
			switch (exitType)
				{
				case EExitKill:	t.Kill(exitCode); break;
				case EExitTerminate: t.Terminate(exitCode); break;
				case EExitPanic: t.Panic(KPanicCat,exitCode); break;
				default: break;
				}
			t.Close();
			}
		}
	return 0;
	}