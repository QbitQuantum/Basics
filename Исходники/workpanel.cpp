int main(int argc, char **argv)
{
    signal(SIGCHLD, SIG_IGN);
    signal(SIGSEGV, terminationHandler);
    fl_init_locale_support("eworkpanel", PREFIX"/share/locale");
    fl_init_images_lib();

    int X=0,Y=0,W=Fl::w(),H=Fl::h();
    int substract;

    // Get current workarea
    Fl_WM::get_workarea(X,Y,W,H);

    //printf("Free area: %d %d %d %d\n", X,Y,W,H);

    // We expect that other docks are moving away from panel :)
    mPanelWindow = new Fl_Update_Window(X, Y+H-30, W, 30, "Workpanel");
    mPanelWindow->layout_spacing(0);
    // Panel is type DOCK
    mPanelWindow->window_type(Fl_WM::DOCK);
    mPanelWindow->setAutoHide(0);

    // Read config
    bool doShowDesktop;
    pGlobalConfig.get("Panel", "ShowDesktop", doShowDesktop, false);
    bool doWorkspaces;
    pGlobalConfig.get("Panel", "Workspaces", doWorkspaces, true);
    bool doRunBrowser;
    pGlobalConfig.get("Panel", "RunBrowser", doRunBrowser, true);    
    bool doSoundMixer;
    pGlobalConfig.get("Panel", "SoundMixer", doSoundMixer, true);
    bool doCpuMonitor;
    pGlobalConfig.get("Panel", "CPUMonitor", doCpuMonitor, true);
    
    // Group that holds everything..
    Fl_Group *g = new Fl_Group(0,0,0,0);
    g->box(FL_DIV_UP_BOX);
    g->layout_spacing(2);
    g->layout_align(FL_ALIGN_CLIENT);
    g->begin();

    mSystemMenu = new MainMenu();

    Fl_VertDivider *v = new Fl_VertDivider(0, 0, 5, 18, "");
    v->layout_align(FL_ALIGN_LEFT);
    substract = 5;

    if ((doShowDesktop) || (doWorkspaces)) {
	//this is ugly:
	int size;
	if ((doShowDesktop) && (doWorkspaces)) { size=48; } else { size=24; }
	Fl_Group *g2 = new Fl_Group(0,0,size,22);
	g2->box(FL_FLAT_BOX);
	g2->layout_spacing(0);
	g2->layout_align(FL_ALIGN_LEFT);

	// Show desktop button
	if (doShowDesktop) {
		PanelButton *mShowDesktop;
		mShowDesktop = new PanelButton(0, 0, 24, 22, FL_NO_BOX, FL_DOWN_BOX, "ShowDesktop");
		mShowDesktop->layout_align(FL_ALIGN_LEFT);
		mShowDesktop->label_type(FL_NO_LABEL);
		mShowDesktop->align(FL_ALIGN_INSIDE|FL_ALIGN_CENTER);
		mShowDesktop->image(showdesktop_pix);
		mShowDesktop->tooltip(_("Show desktop"));
		mShowDesktop->callback( (Fl_Callback*)cb_showdesktop);
		mShowDesktop->show();
		
		substract += 26;
	}
    
	// Workspaces panel
	if (doWorkspaces) {
		mWorkspace = new PanelMenu(0, 0, 24, 22, FL_NO_BOX, FL_DOWN_BOX, "WSMenu");
		mWorkspace->layout_align(FL_ALIGN_LEFT);
		mWorkspace->label_type(FL_NO_LABEL);
		mWorkspace->align(FL_ALIGN_INSIDE|FL_ALIGN_CENTER);
		mWorkspace->image(desktop_pix);
		mWorkspace->tooltip(_("Workspaces"));
		mWorkspace->end();
		
		substract += 26;
	}
	
	g2->end();
	g2->show();
	g2->resizable();

	v = new Fl_VertDivider(0, 0, 5, 18, "");
        v->layout_align(FL_ALIGN_LEFT);
	substract += 5;
    }
    
    // Run browser
    if (doRunBrowser) {
        runBrowser = new Fl_Input_Browser("",100,FL_ALIGN_LEFT,30);
        //runBrowser->image(run_pix);
        //runBrowser->box(FL_THIN_DOWN_BOX);

        // Added _ALWAYS so callback is in case:
        // 1) select old command from input browser
        // 2) press enter to execute. (this won't work w/o _ALWAYS)
//        runBrowser->input()->when(FL_WHEN_ENTER_KEY_ALWAYS | FL_WHEN_RELEASE_ALWAYS); 
        // Vedran: HOWEVER, with _ALWAYS cb_run_app will be called way
        // too many times, causing fork-attack
        runBrowser->input()->when(FL_WHEN_ENTER_KEY); 
        runBrowser->input()->callback((Fl_Callback*)cb_run_app);
        runBrowser->callback((Fl_Callback*)cb_run_app2);

        v = new Fl_VertDivider(0, 0, 5, 18, "");
        v->layout_align(FL_ALIGN_LEFT);
	substract += 105;
    }


    // Popup menu for the whole taskbar
    Fl_Menu_Button *mPopupPanelProp = new Fl_Menu_Button( 0, 0, W, 28 );
    mPopupPanelProp->type( Fl_Menu_Button::POPUP3 );
    mPopupPanelProp->anim_flags(Fl_Menu_::LEFT_TO_RIGHT);
    mPopupPanelProp->anim_speed(0.8);
    mPopupPanelProp->begin();

    Fl_Item *mPanelSettings = new Fl_Item(_("Settings"));
    mPanelSettings->x_offset(12);
    mPanelSettings->callback( (Fl_Callback*)runUtility, (void*)"epanelconf" );
    new Fl_Divider(10, 5);

    Fl_Item *mAboutItem = new Fl_Item(_("About EDE..."));
    mAboutItem->x_offset(12);
    mAboutItem->callback( (Fl_Callback *)AboutDialog );

    mPopupPanelProp->end();

    // Subgroup to properly align everything
/*    Fl_Group *subgroup;
    {
        subgroup = new Fl_Group(0, 0, W-substract, 18);
        subgroup->box(FL_FLAT_BOX);
        subgroup->layout_align(FL_ALIGN_RIGHT);
        subgroup->show();
        subgroup->begin(); */
    
        // Taskbar...
        tasks = new TaskBar();
        dock = new Dock();

        v = new Fl_VertDivider(0, 0, 5, 18, "");
        v->layout_align(FL_ALIGN_RIGHT);
    
/*        subgroup->end();
    }*/

    {
        // MODEM
        mModemLeds = new Fl_Group(0, 0, 25, 18);
        mModemLeds->box(FL_FLAT_BOX);
        mModemLeds->hide();
        mLedIn = new Fl_Box(2, 5, 10, 10);
        mLedIn->box( FL_OVAL_BOX );
        mLedIn->color( (Fl_Color)968701184);
        mLedOut = new Fl_Box(12, 5, 10, 10);
        mLedOut->box( FL_OVAL_BOX);
        mLedOut->color( (Fl_Color)968701184);
        mModemLeds->end();
    }

    {
        // KEYBOARD SELECT
        mKbdSelect = new KeyboardChooser(0, 0, 20, 18, FL_NO_BOX, FL_DOWN_BOX, "us");
        mKbdSelect->hide();
        mKbdSelect->anim_speed(4);
        mKbdSelect->label_font(mKbdSelect->label_font()->bold());
        mKbdSelect->highlight_color(mKbdSelect->selection_color());
        mKbdSelect->highlight_label_color( mKbdSelect->selection_text_color());
    }

    {
        // CLOCK
        mClockBox = new Fl_Button(0, 0, 50, 20);
        mClockBox->align(FL_ALIGN_INSIDE|FL_ALIGN_LEFT);
        mClockBox->hide();
        mClockBox->box(FL_FLAT_BOX);
        mClockBox->callback( (Fl_Callback*)startUtility, (void*)"Time and date");
    }
 
    dock->add_to_tray(mClockBox);
    dock->add_to_tray(mKbdSelect);
    
    // SOUND applet
    if (doSoundMixer) {
        Fl_Button *mSoundMixer;
        mSoundMixer = new Fl_Button(0, 0, 20, 18);
        mSoundMixer->hide();
        mSoundMixer->box(FL_NO_BOX);
        mSoundMixer->focus_box(FL_NO_BOX);
        mSoundMixer->image(sound_pix);
        mSoundMixer->tooltip(_("Volume control"));
        mSoundMixer->align(FL_ALIGN_INSIDE);
        mSoundMixer->callback( (Fl_Callback*)startUtility, (void*)"Volume Control" );
        dock->add_to_tray(mSoundMixer);
    }

    // CPU monitor
    if (doCpuMonitor) {
        CPUMonitor *cpumon;
        cpumon = new CPUMonitor();
        cpumon->hide();
        dock->add_to_tray(cpumon);
    }


    Fl::focus(mSystemMenu);

    mPanelWindow->end();
    mPanelWindow->show(argc, argv);

    Fl_WM::callback(FL_WM_handler, 0, Fl_WM::DESKTOP_COUNT | 
		    					   Fl_WM::DESKTOP_NAMES |
							   Fl_WM::DESKTOP_CHANGED|
							   Fl_WM::WINDOW_LIST|
							   Fl_WM::WINDOW_DESKTOP|
							   Fl_WM::WINDOW_ACTIVE|
							   Fl_WM::WINDOW_NAME|
							   Fl_WM::WINDOW_ICONNAME);

    updateWorkspaces(0,0);

    Fl::add_timeout(0, clockRefresh);
    Fl::add_timeout(0, updateStats);

    while(mPanelWindow->shown())
        Fl::wait();
}