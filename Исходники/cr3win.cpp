int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

    CRLog::setFileLogger( "crengine.log", true );
    CRLog::setLogLevel( CRLog::LL_TRACE );
    //InitCREngineLog("/root/abook/crengine/crlog.ini");

#if 0
	MMapTest();
#endif

    lString8 exe_dir;
    char exe_fn[MAX_PATH+1];
    GetModuleFileNameA( NULL, exe_fn, MAX_PATH );
    lChar16 exe_fn16[MAX_PATH+1];
    GetModuleFileNameW( NULL, exe_fn16, MAX_PATH );
	lString16 exedir = LVExtractPath(lString16(exe_fn16));	
	lString8 exedir8 = UnicodeToUtf8( exedir );

	CRMoFileTranslator * translator = new CRMoFileTranslator();
	translator->openMoFile(exedir + L"/po/ru.mo");
	CRI18NTranslator::setTranslator( translator );


	lChar16 sysdir[MAX_PATH+1];
	GetWindowsDirectoryW(sysdir, MAX_PATH);
	lString16 fontdir( sysdir );
	fontdir << L"\\Fonts\\";
	lString8 fontdir8( UnicodeToUtf8(fontdir) );
	lString8 fd = UnicodeToLocal(exedir);
	lString16Collection fontDirs;
	//fontDirs.add( fontdir );
    fontDirs.add( exedir + L"fonts" );
	InitCREngine( exe_fn, fontDirs );
    const char * fontnames[] = {
#if 1
        "arial.ttf",
        "ariali.ttf",
        "arialb.ttf",
        "arialbi.ttf",
#endif
        "arialn.ttf",
        "arialni.ttf",
        "arialnb.ttf",
        "arialnbi.ttf",
        "cour.ttf",
        "couri.ttf",
        "courbd.ttf",
        "courbi.ttf",
        "times.ttf",
        "timesi.ttf",
        "timesb.ttf",
        "timesbi.ttf",
        "comic.ttf",
        "comicbd.ttf",
        "verdana.ttf",
        "verdanai.ttf",
        "verdanab.ttf",
        "verdanaz.ttf",
        "bookos.ttf",
        "bookosi.ttf",
        "bookosb.ttf",
        "bookosbi.ttf",
#if 1
        "calibri.ttf",
        "calibrii.ttf",
        "calibrib.ttf",
        "calibriz.ttf",
        "cambria.ttf",
        "cambriai.ttf",
        "cambriab.ttf",
        "cambriaz.ttf",
        "georgia.ttf",
        "georgiai.ttf",
        "georgiab.ttf",
        "georgiaz.ttf",
#endif
        NULL
    };
    for ( int fi = 0; fontnames[fi]; fi++ ) {
        fontMan->RegisterFont( fontdir8 + fontnames[fi] );
    }
    //LVCHECKPOINT("WinMain start");

    if (!fontMan->GetFontCount())
    {
        //error
        char str[1000];
#if (USE_FREETYPE==1)
        sprintf(str, "Cannot open font file(s) fonts/*.ttf \nCannot work without font\nPlace some TTF files to font\\ directory" );
#else
        sprintf(str, "Cannot open font file(s) font#.lbf \nCannot work without font\nUse FontConv utility to generate .lbf fonts from TTF" );
#endif
        MessageBoxA( NULL, str, "CR Engine :: Fb2Test -- fatal error!", MB_OK);
        return 1;
    }

    lString8 cmdline(lpCmdLine);
    if ( cmdline.empty() )
        return 2; // need filename

    hInst = hInstance;
    MyRegisterClass(hInstance);

    {

		CRWin32WindowManager winman(500, 700);

		const char * keymap_locations [] = {
			exedir8.c_str(),
			NULL,
		};
		loadKeymaps( winman, keymap_locations );
		

        ldomDocCache::init( exedir + L"cache", 0x100000 * 96 ); /*96Mb*/

        winman.loadSkin( LVExtractPath(LocalToUnicode(lString8(exe_fn))) + L"skin" );
        V3DocViewWin * main_win = new V3DocViewWin( &winman, LVExtractPath(LocalToUnicode(lString8(exe_fn))) );
        main_win->getDocView()->setBackgroundColor(0xFFFFFF);
        main_win->getDocView()->setTextColor(0x000000);
        main_win->getDocView()->setFontSize( 20 );
		main_win->loadCSS( exedir + L"fb2.css" );
		main_win->loadSettings( exedir + L"cr3.ini" );
		main_win->setHelpFile( exedir + L"cr3-manual-ru.fb2" );
		HyphMan::initDictionaries( exedir + L"hyph" );
		main_win->loadDefaultCover( exedir + L"cr3_def_cover.png" );
		main_win->setBookmarkDir(lString16("c:\\cr3\\bookmarks\\"));
		lString8 exedir8 = UnicodeToUtf8( exedir );
		const char * dirs[] = {
			exedir8.c_str(),
			NULL
		};

		loadKeymaps( winman, dirs );

        main_win->loadHistory( exedir + L"cr3hist.bmk" );

        winman.activateWindow( main_win );
        if ( !main_win->loadDocument( LocalToUnicode( cmdline )) ) {
            char str[100];
            sprintf(str, "Cannot open document file %s", cmdline.c_str());
            MessageBoxA( NULL, str, "CR Engine :: Fb2Test -- fatal error!", MB_OK);
            return 1;
        } else {
            winman.runEventLoop();
        }
    }
    //ShutdownFontManager();

    return 0;
}