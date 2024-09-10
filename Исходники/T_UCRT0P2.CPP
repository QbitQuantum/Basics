//DEF074278: Java VM requires more command line testArguments.
void Defect_DEF074278_Part2()
	{
   	TBuf<180> testArguments(_L("one two three four five six seven eight nine ten eleven twelve thirteen fourteen fifteen sixteen seventeen eighteen nineteen twenty twenty-one twenty-two twenty-three twenty-four "));
	TBuf<210> inputArguments;

	TUint testArgNo = 25;

	int argc=0;
	char** argv=0;
	char** envp=0;

	TheTest.Printf(_L("Retrieving the arguments passed in from T_UCRT0P1\n"));
	__crt0(argc,argv,envp);			// get args & environment from somewhere

	//Get all the arguments into a descriptor, beginning at pos 1, as pos 0 contains
	//the T_UCRT0P2 exe path and name.
	for (TInt i=1; i < argc; i++)
		{
		char *str=argv[i];
		while(*str)
			inputArguments.Append((TChar)*str++);
		inputArguments.Append(' ');
		}

	//tests all the arguments were passed to the new process correctly.
	TheTest.Printf(_L("Checking all arguements were passed to the new process correctly... "));
	TEST(testArguments == inputArguments );
	TEST2(testArgNo, argc);

	exit(0);
	}