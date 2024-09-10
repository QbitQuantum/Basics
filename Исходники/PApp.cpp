PApp::PApp()
	: BApplication("application/x-vnd.dw-PalEdit")
{
	try
	{
		try
		{
			BPath settings;

			FailOSErr(find_directory(B_USER_SETTINGS_DIRECTORY, &settings, true));

			BDirectory e;
			FailOSErrMsg(e.SetTo(settings.Path()), "~/config/settings directory not found ?!?!?");
			if (!e.Contains("PalEdit", B_DIRECTORY_NODE))
				FailOSErr(e.CreateDirectory("PalEdit", &gPrefsDir));
			else
			{
				BEntry d;
				FailOSErr(e.FindEntry("PalEdit", &d, B_DIRECTORY_NODE));
				FailOSErr(gPrefsDir.SetTo(&d));
			}
		}
		catch (HErr& e)
		{
			e.DoError();
		}

		gPrefs = new HPreferences("PalEdit/settings");
		gPrefs->ReadPrefFile();

		app_info ai;
		GetAppInfo(&ai);

		BEntry entry(&ai.ref);

		FailOSErr(gAppFile.SetTo(&entry, B_READ_ONLY));

		BPath appName;
		FailOSErr(entry.GetPath(&appName));

		BPath dir;
		FailOSErr(appName.GetParent(&dir));
		FailOSErr(gAppDir.SetTo(dir.Path()));

		fOpenPanel = new BFilePanel();
		FailNil(fOpenPanel);
		entry_ref cwd_ref;
		fOpenPanel->GetPanelDirectory(&cwd_ref);
		FailOSErr(gCWD.SetTo(&cwd_ref));

		PDoc::LoadAddOns();

		InitUTFTables();

		SetColor(kColorLow,				prf_C_Low,				0xff, 0xff, 0xff);
		SetColor(kColorText,			prf_C_Text,				0x00, 0x00, 0x00);
		SetColor(kColorSelection,		prf_C_Selection,		0xd1, 0xd1, 0xff);
		SetColor(kColorMark,			prf_C_Mark,				0x00, 0x00, 0xff);
		SetColor(kColorKeyword1,		prf_C_Keyword1,			0x00, 0x00, 0xff);
		SetColor(kColorKeyword2,		prf_C_Keyword2,			0x00, 0x00, 0xff);
		SetColor(kColorComment1,		prf_C_Comment1,			0x1e, 0x93, 0x1e);
		SetColor(kColorComment2,		prf_C_Comment2,			0x1e, 0x93, 0x1e);
		SetColor(kColorString1,			prf_C_String1,			0x7e, 0x7e, 0x7e);
		SetColor(kColorString2,			prf_C_String2,			0x7e, 0x7e, 0x7e);
		SetColor(kColorNumber1,			prf_C_Number1,			0x85, 0x0a, 0x48);
		SetColor(kColorNumber2,			prf_C_Number2,			0x85, 0x0a, 0x48);
		SetColor(kColorOperator1,		prf_C_Operator1,		0x00, 0x00, 0x00);
		SetColor(kColorOperator2,		prf_C_Operator2,		0x00, 0x00, 0x00);
		SetColor(kColorSeparator1,		prf_C_Separator1,		0x00, 0x00, 0x00);
		SetColor(kColorSeparator2,		prf_C_Separator2,		0x00, 0x00, 0x00);
		SetColor(kColorPreprocessor1,	prf_C_Preprocessor1,	0x00, 0x00, 0xff);
		SetColor(kColorPreprocessor2,	prf_C_Preprocessor2,	0x00, 0x00, 0xff);
		SetColor(kColorError1,			prf_C_Error1,			0xff, 0x00, 0x00);
		SetColor(kColorError2,			prf_C_Error2,			0xff, 0x00, 0x00);
		SetColor(kColorIdentifierSystem,prf_C_IdentifierSystem,	0x39, 0x79, 0x79);
		SetColor(kColorCharConst,		prf_C_CharConst,		0x7e, 0x7e, 0x7e);
		SetColor(kColorIdentifierUser,	prf_C_IdentifierUser,	0x00, 0x00, 0x00);
		SetColor(kColorTag,				prf_C_Tag,				0x88, 0x88, 0x88);
		SetColor(kColorAttribute,		prf_C_Attribute,		0xff, 0x00, 0x00);
		SetColor(kColorUserSet1,		prf_C_UserSet1,			0x00, 0x00, 0x00);
		SetColor(kColorUserSet2,		prf_C_UserSet2,			0x00, 0x00, 0x00);
		SetColor(kColorUserSet3,		prf_C_UserSet3,			0x00, 0x00, 0x00);
		SetColor(kColorUserSet4,		prf_C_UserSet4,			0x00, 0x00, 0x00);
		SetColor(kColorInvisibles,		prf_C_Invisibles,		0xC8, 0x64, 0x64);

		DefineInvColors(gColor[kColorSelection]);

		gAutoIndent			= gPrefs->GetPrefInt(prf_I_AutoIndent,			1);
		gSyntaxColoring		= gPrefs->GetPrefInt(prf_I_SyntaxColoring,		1);
		gSpacesPerTab		= gPrefs->GetPrefInt(prf_I_SpacesPerTab,		4);
		gBalance			= gPrefs->GetPrefInt(prf_I_BalanceWhileTyping,	1);
		gBlockCursor		= gPrefs->GetPrefInt(prf_I_BlockCursor,			0);
		gFlashCursor		= gPrefs->GetPrefInt(prf_I_FlashCursor,			1);
		gSmartBrace			= gPrefs->GetPrefInt(prf_I_SmartBraces,			1);
		gPopupIncludes		= gPrefs->GetPrefInt(prf_I_ShowIncludes,		1);
		gPopupProtos		= gPrefs->GetPrefInt(prf_I_ShowPrototypes,		1);
		gPopupFuncs			= gPrefs->GetPrefInt(prf_I_ShowTypes,			1);
		gPopupSorted		= gPrefs->GetPrefInt(prf_I_SortPopup,			0);
		gRedirectStdErr		= gPrefs->GetPrefInt(prf_I_RedirectStdErr,		1);
		gUseWorksheet		= gPrefs->GetPrefInt(prf_I_Worksheet,			0);
		gRestorePosition	= gPrefs->GetPrefInt(prf_I_RestorePosition,		1);
		gRestoreFont		= gPrefs->GetPrefInt(prf_I_RestoreFont,			1);
		gRestoreSelection	= gPrefs->GetPrefInt(prf_I_RestoreSelection,	1);
		gRestoreScrollbar	= gPrefs->GetPrefInt(prf_I_RestoreScrollbar,	1);
		gRestoreCWD			= gPrefs->GetPrefInt(prf_I_RestoreCwd,			1);
		gSavedState			= gPrefs->GetPrefInt(prf_I_SavedState,			1);

		if (gPrefs->GetIxPrefString(prf_X_Mimetype, 0) == NULL)
		{
			gPrefs->SetIxPrefString(prf_X_Mimetype, 0, "text/plain");
			gPrefs->SetIxPrefString(prf_X_Mimetype, 1, "text/html");
			gPrefs->SetIxPrefString(prf_X_Mimetype, 2, "text/x-source-code");
		}

		strcpy(gTabChar,		gPrefs->GetPrefString(prf_S_TabChar,		"»"));
		strcpy(gReturnChar,		gPrefs->GetPrefString(prf_S_ReturnChar,		"¬"));
		strcpy(gSpaceChar,		gPrefs->GetPrefString(prf_S_SpaceChar,		"."));
		strcpy(gControlChar,	gPrefs->GetPrefString(prf_S_ControlChar,	"¿"));

		gUid = getuid();
		gGid = getgid();

		gRecentBufferSize = gPrefs->GetPrefInt(prf_I_RecentSize, 10);
		RestoreRecentMenu();

		fFindDialog = DialogCreator<CFindDialog>::CreateDialog("Find", NULL, PDoc::TopWindow());
		fFindDialog->Run();

		InitSelectedMap();

		CLanguageInterface::SetupLanguageInterfaces();

		fIsQuitting = false;

		fPrefsDialog = NULL;
		CPrefOpener *prefOpener = new CPrefOpener;
		fPrefOpener = prefOpener->Thread();

		if (gUseWorksheet)
			OpenWorksheet();

//		prefOpener->Run();
	}
	catch (HErr& e)
	{
		e.DoError();
		exit(1);
	}
	catch(...)
	{
		beep();
		exit(1);
	}
} /* PApp::PApp */