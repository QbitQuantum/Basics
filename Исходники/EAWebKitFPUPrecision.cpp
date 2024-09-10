AutoFPUPrecision::AutoFPUPrecision(EA::WebKit::FPUPrecision precisionDesired)
{
	unsigned int controlWord = 0;

	switch (precisionDesired)
	{
	case kFPUPrecisionExtended:
		controlWord = _PC_64;
		break;
	case kFPUPrecisionDouble:
		controlWord = _PC_53;
		break;
	case kFPUPrecisionSingle:
		controlWord = _PC_24;
		break;
	default:
		EAW_ASSERT_MSG(false,"Invalid FPUPrecision specified");
		break;
	}
	_controlfp_s(&mSavedControlWord, 0, 0); //Save original Control word
	_controlfp_s(NULL, controlWord, MCW_PC);//Set the higher precision
}