wxMenuBar* NewtonDemos::CreateMainMenu()
{
	wxMenuBar* const mainMenu =  new wxMenuBar();

	// adding the file menu
	{
		wxMenu* const fileMenu = new wxMenu;

		fileMenu->Append(wxID_ABOUT, wxT("About"));
		
		fileMenu->AppendSeparator();
		fileMenu->Append(wxID_PREFERENCES, wxT("Preferences"));

		fileMenu->AppendSeparator();
		fileMenu->Append(wxID_NEW, wxT("&New"), wxT("Create a blank new scene"));

		fileMenu->AppendSeparator();
		fileMenu->Append(wxID_OPEN, wxT("&Open"), wxT("Open visual scene in dScene newton format"));
		fileMenu->Append(wxID_SAVE, wxT("&Save"), wxT("Save visual scene in dScene newton format"));

		fileMenu->AppendSeparator();
		fileMenu->Append(ID_SERIALIZE, wxT("&Serialize"), wxT("Serialize scene to binary file"));
		fileMenu->Append(ID_DESERIALIZE, wxT("&Deserialize"), wxT("Load previuoslly serialized scame"));

	//	fileMenu->AppendSeparator();
	//	fileMenu->Append(m_idImportPhysics, wxT("&Open physics scene"), wxT("Open physics scene in collada format"));
	//	fileMenu->Append(m_idExportPhysics, wxT("&Save physics scene"), wxT("Save physics in collada format"));

		fileMenu->AppendSeparator();
		fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"), wxT("Quit SDK sample") );

		// add main menus to menu bar
		mainMenu->Append(fileMenu, wxT("&File"));
	}

	// engine all demo examples
	{
		wxMenu* const sdkDemos = new wxMenu;
		int demosCount = int (sizeof (m_demosSelection) / sizeof m_demosSelection[0]);
		for (int i = 0; i < demosCount; i ++) {
			sdkDemos->AppendRadioItem (NewtonDemos::ID_RUN_DEMO + i,  m_demosSelection[i].m_name, m_demosSelection[i].m_description);
		}

		mainMenu->Append(sdkDemos, wxT("&Demos"));
	}

	// option menu
	{
		wxMenu* const optionsMenu = new wxMenu;;

		optionsMenu->AppendCheckItem(ID_AUTOSLEEP_MODE, wxT("Auto sleep mode"), wxT("toogle auto sleep bodies"));
		optionsMenu->Check (ID_AUTOSLEEP_MODE, m_autoSleepState);

		optionsMenu->AppendCheckItem(ID_SHOW_STATISTICS, wxT("Show Stats on screen"), wxT("toogle on screen frame rate and other stats"));
		optionsMenu->AppendCheckItem(ID_USE_PARALLEL_SOLVER, wxT("Parallel solver on"));

		optionsMenu->AppendSeparator();
		optionsMenu->AppendRadioItem(ID_BROADPHSE_TYPE0, wxT("Default broaphase"), wxT("for scenes with more dynamics bodies than static"));
		optionsMenu->AppendRadioItem(ID_BROADPHSE_TYPE1, wxT("Persintent broaphase"), wxT("for scenes with lot more static bodies than dynamics"));

		optionsMenu->AppendSeparator();
		optionsMenu->AppendRadioItem(ID_SOLVER_MODE + 0, wxT("Exact solver on"));
		optionsMenu->AppendRadioItem(ID_SOLVER_MODE + 1, wxT("Iterative solver one passes"));
		optionsMenu->AppendRadioItem(ID_SOLVER_MODE + 2, wxT("Iterative solver two passes"));
		optionsMenu->AppendRadioItem(ID_SOLVER_MODE + 3, wxT("Iterative solver four passes"));
		optionsMenu->AppendRadioItem(ID_SOLVER_MODE + 4, wxT("Iterative solver eight passes"));

		dAssert (m_solverModeIndex >= 0);
		dAssert (m_solverModeIndex < int (sizeof (m_solverModes)/sizeof (m_solverModes[0])));
		optionsMenu->Check (ID_SOLVER_MODE + m_solverModeIndex, true);

		optionsMenu->AppendSeparator();
		optionsMenu->AppendRadioItem(ID_SOLVER_QUALITY + 0, wxT("Iterative Solver Quality Low"));
		optionsMenu->AppendRadioItem(ID_SOLVER_QUALITY + 1, wxT("Iterative Solver Quality High"));
		optionsMenu->Check (ID_SOLVER_QUALITY + m_solverModeQuality, true);

		optionsMenu->AppendSeparator();
		optionsMenu->AppendRadioItem(ID_SHOW_COLLISION_MESH, wxT("Hide collision Mesh"));
		optionsMenu->AppendRadioItem(ID_SHOW_COLLISION_MESH + 1, wxT("Show solid collision Mesh"));
		optionsMenu->AppendRadioItem(ID_SHOW_COLLISION_MESH + 2, wxT("Show wire frame collision Mesh"));

		optionsMenu->AppendSeparator();
		optionsMenu->AppendCheckItem(ID_HIDE_VISUAL_MESHES, wxT("Hide visual meshes"));
		optionsMenu->AppendCheckItem(ID_SHOW_CONTACT_POINTS, wxT("Show contact points"));
		optionsMenu->AppendCheckItem(ID_SHOW_NORMAL_FORCES, wxT("Show normal forces"));
		optionsMenu->AppendCheckItem(ID_SHOW_AABB, wxT("Show aabb"));
		optionsMenu->AppendCheckItem(ID_SHOW_CENTER_OF_MASS, wxT("Show center of mass"));
		optionsMenu->AppendCheckItem(ID_SHOW_JOINTS, wxT("show Joint debug info"));
	

		optionsMenu->AppendSeparator();
		int platformsCount = NewtonEnumerateDevices (m_scene->GetNewton());
		for (int i = 0; i < platformsCount; i ++) {
			wxString label;
			char platform[256];
			

			NewtonGetDeviceString (m_scene->GetNewton(), i, platform, sizeof (platform));
			#ifdef _POSIX_VER
				wxChar wPlatform[256];
				mbstowcs (wPlatform, platform, sizeof (platform));
				wxString tmp (wPlatform);
				label.Printf (wxT(" hardware mode %s"), tmp.c_str());
			#else 
				label.Printf (wxT(" hardware mode %s"), wxString(platform));
			#endif
			optionsMenu->AppendRadioItem(ID_PLATFORMS + i, label);
		}
		//optionsMenu->Check(ID_PLATFORMS, true);

		optionsMenu->AppendSeparator();
		optionsMenu->AppendCheckItem(ID_CONCURRENT_PHYSICS_UPDATE, wxT("Concurrent physics update"));

		wxMenu* const microThreadedsSubMenu = new wxMenu;
		for (int i = 0 ; i < int (sizeof (m_threadsTracks)/ sizeof (m_threadsTracks[0])); i ++) {
			wxString msg;
			msg.Printf(wxT ("%d micro threads"), m_threadsTracks[i]);
			microThreadedsSubMenu->AppendRadioItem(ID_SELECT_MICROTHREADS + i, msg);
		}
		optionsMenu->AppendSubMenu (microThreadedsSubMenu, wxT("select microThread count"));


		mainMenu->Append(optionsMenu, wxT("&Options"));
	}

	// add help menu
	{
		wxMenu* const helpMenu = new wxMenu;;

		helpMenu->Append(wxID_HELP, wxT("About"));
//		helpMenu->Append(NewtonDemos::ID_ON_ABOUT, wxT("About"));
		mainMenu->Append(helpMenu, wxT("&Help"));
	}

	SetMenuBar(mainMenu);
	return mainMenu;
}