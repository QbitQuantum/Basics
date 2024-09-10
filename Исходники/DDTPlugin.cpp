DLLExport MACPASCAL void PluginMain(const int16 selector,
	FormatRecordPtr formatParamBlock,
	intptr_t * data,
	int16 * result)
{
	PSHandleSuite1* sPSHandleSuite;

	Boolean oldLock = FALSE;

	gFormatRecord = formatParamBlock;
	gResult = result;

	if (selector == formatSelectorAbout) {
#ifdef MSWindows
		MessageBox(GetActiveWindow(),
			TEXT("Age of Empires III DirectDraw Texture Plug-in for Adobe Photoshop\n\n")
			TEXT("Copyright(C) 2016, Cliff Kang"),
			TEXT("About"),
			MB_ICONINFORMATION | MB_OK);
#endif
	}
	else {

		*gResult = gFormatRecord->sSPBasic->AcquireSuite(kPSHandleSuite, kPSHandleSuiteVersion1,
			(const void**)&sPSHandleSuite);

		if (*gResult != noErr)
			return;

		if (*data == NULL) {

			Boolean oldLock = FALSE;

			*data = reinterpret_cast<intptr_t>(sPSHandleSuite->New(sizeof(DDTPlugInData)));

			sPSHandleSuite->SetLock(reinterpret_cast<Handle>(*data),
				TRUE, reinterpret_cast<Ptr*>(&gPlugInData), &oldLock);

			gPlugInData->InputTextureType = DDT_BGRA;
			gPlugInData->Options.TextureUsage = DDT_DIFFUSE;
			gPlugInData->Options.TextureAlphaUsage = DDT_NONE;
			gPlugInData->Options.TextureType = DDT_BGRA;
			gPlugInData->Options.ImageCount = 1;
			gPlugInData->Options.MIPMapSharpness = 0.25f;
		}
		else
			sPSHandleSuite->SetLock(reinterpret_cast<Handle>(*data), 
				TRUE, reinterpret_cast<Ptr*>(&gPlugInData), &oldLock);

		switch (selector)
		{
		case formatSelectorReadPrepare:
			gFormatRecord->maxData = 0;
			break;
		case formatSelectorReadStart:
			DDTReadBegin();
			break;
		case formatSelectorReadContinue:
			DDTReadContinue();
			break;
		case formatSelectorReadFinish:
			gFormatRecord->maxData = 0;
			break;

		case formatSelectorOptionsPrepare:
			gFormatRecord->maxData = 0;
			break;
		case formatSelectorOptionsStart:
			DDTCreateOptionsDialog();

			if (*gResult != noErr)
				return;

			gFormatRecord->data = NULL;
			break;
		case formatSelectorOptionsContinue:
			break;
		case formatSelectorOptionsFinish:
			break;

		case formatSelectorEstimatePrepare:
			gFormatRecord->maxData = 0;
			break;
		case formatSelectorEstimateStart:
			DDTEstimateBegin();
			break;
		case formatSelectorEstimateContinue:
			break;
		case formatSelectorEstimateFinish:
			break;

		case formatSelectorWritePrepare:
			gFormatRecord->maxData = 0;
			break;
		case formatSelectorWriteStart:
			DDTWriteBegin();
			break;
		case formatSelectorWriteContinue:
			DDTWriteContinue();
			break;
		case formatSelectorWriteFinish:
			break;

		case formatSelectorFilterFile:
			DDTFilterFile();
			break; 

		default:
			*result = formatBadParameters;
		}

		if (*data != NULL)
			sPSHandleSuite->SetLock(reinterpret_cast<Handle>(*data), 
			FALSE, reinterpret_cast<Ptr*>(&gPlugInData), &oldLock);

		*result = formatParamBlock->sSPBasic->ReleaseSuite(kPSHandleSuite, kPSHandleSuiteVersion1);
	}
}