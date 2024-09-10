// The `main program' equivalent, creating the windows and returning the
// main frame
bool AudacityApp::OnInit()
{
    // mChecker = new wxSingleInstanceChecker(GetAppName());
    ::wxInitAllImageHandlers();

    wxFileSystem::AddHandler(new wxZipFSHandler);

#ifdef __WXMSW__

    //BG: On Windows, associate the aup file type with Audacity
    {
        wxRegKey associateFileTypes;

        associateFileTypes.SetName("HKCR\\.AUP");
        associateFileTypes.Create(true);
        associateFileTypes = "Audacity.Project";

        associateFileTypes.SetName("HKCR\\Audacity.Project");
        associateFileTypes.Create(true);
        associateFileTypes = "Audacity Project File";

        associateFileTypes.SetName("HKCR\\Audacity.Project\\shell");
        associateFileTypes.Create(true);
        associateFileTypes = "";

        associateFileTypes.SetName("HKCR\\Audacity.Project\\shell\\open");
        associateFileTypes.Create(true);

        associateFileTypes.SetName("HKCR\\Audacity.Project\\shell\\open\\command");
        associateFileTypes.Create(true);
        associateFileTypes = (wxString)argv[0] + (wxString)" %1";
    }

#endif

    InitPreferences();
    InitAudioIO();

    // Locale
    // wxWindows 2.3 has a much nicer wxLocale API.  We can make this code much
    // better once we move to wx 2.3/2.4.

    wxString lang = gPrefs->Read("/Locale/Language", "en");

    if (lang != "en") {
        wxLogNull nolog;
        mLocale = new wxLocale("", lang, "", true, true);
        mLocale->AddCatalog("audacity");
    } else
        mLocale = NULL;

    LoadEffects(wxPathOnly(argv[0]));

#ifdef __WXMAC__

    // Install AppleEvent handlers (allows us to open documents
    // that are dragged to our application's icon)

    AEInstallEventHandler(kCoreEventClass,
                          kAEOpenDocuments,
                          NewAEEventHandlerUPP(AEOpenFiles), 0, 0);
    AEInstallEventHandler(kCoreEventClass,
                          kAEQuitApplication,
                          NewAEEventHandlerUPP(AEQuit), 0, 0);


    // On the Mac, users don't expect a program to quit when you close the last window.
    // Create an offscreen frame with a menu bar.  The frame should never
    // be visible, but when all other windows are closed, this menu bar should
    // become visible.

    gParentFrame = new wxFrame(NULL, -1, "invisible", wxPoint(5000, 5000), wxSize(100, 100));
    wxMenu *fileMenu = new wxMenu();
    fileMenu->Append(NewID, "&New\tCtrl+N");
    fileMenu->Append(OpenID, "&Open...\tCtrl+O");
    fileMenu->AppendSeparator();
    fileMenu->Append(PreferencesID, "&Preferences...\tCtrl+P");
    fileMenu->AppendSeparator();
    fileMenu->Append(ExitID, "Quit\tCtrl+Q");
    wxMenu *helpMenu = new wxMenu();
    helpMenu->Append(AboutID, "About Audacity...");
    wxApp::s_macAboutMenuItemId = AboutID;

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");

    gParentFrame->SetMenuBar(menuBar);
    gParentFrame->Show();

    SetTopWindow(gParentFrame);

#endif

    SetExitOnFrameDelete(true);

    //Initiate pointers to toolbars here, and create
    //the toolbars that should be loaded at startup.


    //Initiate globally-held toolbar stubs here.
    gControlToolBarStub = new ToolBarStub(gParentWindow, ControlToolBarID);

    // Changing the following to NULL will make the application
    // load without the toolbar in memory at all.

    bool editToolBar;
    gPrefs->Read("/GUI/EnableEditToolBar", &editToolBar, true);
    if(editToolBar)
        gEditToolBarStub =  new ToolBarStub(gParentWindow, EditToolBarID);
    else
        gEditToolBarStub = NULL;


    InitFreqWindow(gParentWindow);
    AudacityProject *project = CreateNewAudacityProject(gParentWindow);
    SetTopWindow(project);

    // Can't handle command-line args on Mac OS X yet...
#ifndef __MACOSX__

    // Parse command-line arguments

    if (argc > 1) {
        for (int option = 1; option < argc; option++) {
            if (!argv[option])
                continue;
            bool handled = false;

            if (!wxString("-help").CmpNoCase(argv[option])) {
                printf(_("Command-line options supported:\n"
                         "  -help (this message)\n"
                         "  -test (run self diagnostics)\n"
                         "  -blocksize ### (set max disk block size in bytes)\n"
                         "\n"
                         "In addition, specify the name of an audio file or "
                         "Audacity project\n" "to open it.\n" "\n"));
                exit(0);
            }

            if (option < argc - 1 &&
                    argv[option + 1] &&
                    !wxString("-blocksize").CmpNoCase(argv[option])) {
                long theBlockSize;
                if (wxString(argv[option + 1]).ToLong(&theBlockSize)) {
                    if (theBlockSize >= 256 && theBlockSize < 100000000) {
                        fprintf(stderr, _("Using block size of %ld\n"),
                                theBlockSize);
                        Sequence::SetMaxDiskBlockSize(theBlockSize);
                    }
                }
                option++;
                handled = true;
            }

            if (!handled && !wxString("-test").CmpNoCase(argv[option])) {
                RunBenchmark(NULL);
                exit(0);
            }

            if (argv[option][0] == '-' && !handled) {
                printf(_("Unknown command line option: %s\n"), argv[option]);
                exit(0);
            }

            if (!handled)
                project->OpenFile(argv[option]);

        }                         // for option...
    }                            // if (argc>1)

#endif // not Mac OS X

    return TRUE;
}