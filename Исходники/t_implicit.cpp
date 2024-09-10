GLDEF_C TInt E32Main()
	{

	test.Title();

	if (UserSvr::HalFunction(EHalGroupKernel, EKernelHalSmpSupported, 0, 0) == KErrNone)
		{
		test.Printf(_L("*********************************\n"));
		test.Printf(_L("*  NOT SUPPORTED ON SMP SYSTEMS *\n"));
		test.Printf(_L("*********************************\n"));
		User::After(2000000);
		return(0);
		}

	test.Start(_L("Load LDD"));
	TInt r=User::LoadLogicalDevice(_L("D_IMPLICIT"));
	test(r==KErrNone || r==KErrAlreadyExists);
	test.Next(_L("Open channel"));
	RImpSysTest impSys;
	r=impSys.Open();
	test(r==KErrNone);

	SStats s;
	test.Next(_L("Test with changing priorities"));
	r=impSys.Start(RImpSysTest::ETestPriority);
	test(r==KErrNone);
	Wait(30);
	r=impSys.Stop(s);
	test(r==KErrNone);
	TInt f1=Display(s);

	test.Next(_L("Test with round-robin"));
	r=impSys.Start(RImpSysTest::ETestRoundRobin);
	test(r==KErrNone);
	Wait(30);
	r=impSys.Stop(s);
	test(r==KErrNone);
	TInt f2=Display(s);

	test.Next(_L("Dry run"));
	r=impSys.Start(RImpSysTest::ETestDummy);
	test(r==KErrNone);
	Wait(30);
	r=impSys.Stop(s);
	test(r==KErrNone);
	TInt f3=Display(s);

	test.Next(_L("Close channel"));
	impSys.Close();

	test(f1==0);
	test(f2==0);
	test(f3==0);

	test.End();
	return KErrNone;
	}