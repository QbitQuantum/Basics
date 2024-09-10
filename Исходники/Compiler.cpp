RCX_Image *Compiler::Compile(Buffer *b, const RCX_Target *target, int flags)
{
	// reset compiler if needed
	if (fDirty)
	{
		Reset();
	}

	fDirty = true;
	gProgram = new Program(target);

	// define compiler target and compat mode
	Define(target->fDefine, target->fDefValue);
	if (flags & kCompat_Flag)
		Define("__NQC1");

	// define NQC version number
	char versionCode[5];
	sprintf(versionCode, "%d", MAJOR_VERSION * 100 + MINOR_VERSION);
	Define("__NQC__", versionCode);

	LexPush(b);

	// system file
	if ((flags & kNoSysFile_Flag) == 0)
	{
		LexPush(CreateApiBuffer(flags & kCompat_Flag));
	}

	ErrorHandler::Get()->Reset();

	yyparse();

	RCX_Image *image = 0;
	if (ErrorHandler::Get()->GetErrorCount() == 0)
	{
		image = gProgram->CreateImage();
		if (ErrorHandler::Get()->GetErrorCount())
		{
			delete image;
			image = 0;
		}
	}

	return image;
}