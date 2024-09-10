CSumItApplication::CSumItApplication()
	  : BApplication(kOpenSumItSignature)
{
#if PRERELEASE
//	{
//		time_t now, expire;
//		time(&now);
//		expire = parsedate("nov 1, 1997", now);
//		printf("expire at %08x\n", expire);
//		expire = 0x345a62f0;

//		if (difftime(now, expire) > 0) {
//			MAlert *a = new MWarningAlert("This version of sum-it has expired");
//			a->Go();
//			exit(1);
//		}
//		TimeLimit limit;
//	}
#endif

	try
	{
		gApp = this;
		
		app_info ai;
		GetAppInfo(&ai);
		
		BEntry entry(&ai.ref);
		entry.GetPath(&gAppName);
		
		BPath dir;
		gAppName.GetParent(&dir);
		gAppDir = new BDirectory(dir.Path());
		gCWD = new BDirectory(*gAppDir);
			
		gResourceManager.SetTo( &gAppName ) ;
		InitFunctions();
		srand((int)(system_time() % INT_MAX));
			
		try
		{
			gPrefs = new CPreferences("Sum-It.Prefs");
			gPrefs->ReadPrefFile();
		}
		catch (CErr& e)
		{
			CATCHED;
			if (e != errIOOpen)
			{
				e.DoError();
				exit(1);
			}
		}
	
		gErrorNan = Nan(1);
		gRefNan = Nan(3);
		gCircleNan = Nan(4);
		gSqrtNan = Nan(5);
		gPowerNan = Nan(6);
		gValueNan = Nan(7);
		gDivNan = Nan(8);
		gAddNan = Nan(9);
		gFinanceNan = Nan(10);
		gEvalNan = Nan(11);
		gInvTrigNan = Nan(12);
		gLogNan = Nan(13);
		gMulNan = Nan(14);
		gNANan = Nan(15);
		gDateNan = Nan(16);
		gTimeNan = Nan(17);
//		gCellNan = Nan(18);
		gFuncNan = Nan(19);
		gNameNan = Nan(20);
		
		font_family fam;
		font_style sty;
		float siz;
		
		be_plain_font->GetFamilyAndStyle(&fam, &sty);
		siz = be_plain_font->Size();
		
		gFontSizeTable.GetFontID(
			gPrefs->GetPrefString("defdoc font family", fam),
			gPrefs->GetPrefString("defdoc font style", sty),
			gPrefs->GetPrefDouble("defdoc font size", siz),
			kBlack);
		
		InitFormatter();
		
		fOpenPanel = NULL;
		
		gClipboard = new CClipboard;
		gClipboard->Run();

		fFindDialog = CFindDialog::Construct();
		fFindDialog->Run();
		
		gWithEqualSign = gPrefs->GetPrefInt("formula starts with equal", 0);
		gGridColor = gPrefs->GetPrefInt("dark gridlines") ? 10 : 6;
		
		InstallMimeType();
		
		SetPulseRate(1000000);
	}
	
	catch (CErr& e)
	{
		CATCHED;
		e.DoError();
		exit(1);
	}
	
	catch (...)
	{
		CATCHED;
		ASSERT(false);
	}
}