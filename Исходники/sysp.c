//============================================
// scan module...
//--------------------------------------------
void ScanModule(str name) {
	string module = name;
	// ...
	// Mouse scan
	// ---
	if (module == "mouse") {
		ScanMouse mouse;
		mouse.SetFile(MOUSE_DATA);
		mouse.Scan(); PrintMouseData(mouse);
		if (! InfoOnly) {
			mouse.Save();
		}
		exit(0);
	}
 	// ...
	// Keyboard scan
	// ---
	if (module == "keyboard") {
		ScanKeyboard key(KBD_MAP);
		key.SetFile(KEYBOARD_DATA);
		key.Scan(); PrintKeyboardData(key);
		if (! InfoOnly) {
			key.Save();
		}
		exit(0);
	}
	// ...
	// Server scan
	// ---
	if (module == "server") {
		ScanServer server;
		str module ; strcpy(module,ModuleToUse.c_str());
		str card   ; strcpy(card,CardToUse.c_str());
		server.SetFile(SERVER_DATA);
		server.SetQuestion(AskForFlag);
		if (CheckQuestionOnly == 1) {
			server.CheckForQuestionOnly();
		}
		server.SetCheckForPCIVendor (CheckPCIVendor);
		server.SetXAvailable(UseXForQuestions);
		server.SetCardModule(module);
		server.SetCard(card);
		server.Scan(); PrintServerData(server);
		if (! InfoOnly) {
			server.Save();
		}
		exit(0);
	}
	// ...
	// XStuff scan
	// ---
	if (module == "xstuff") {
		str module ; strcpy(module,ModuleToUse.c_str());
		str card   ; strcpy(card,CardToUse.c_str());
		ScanXStuff stuff (AskForFlag,UseXForQuestions,card,module);
		stuff.SetFile(STUFF_DATA);
		if (ddc == 0) {
			stuff.DisableDDC();
		}
		stuff.Scan(); PrintStuffData(stuff);
		if (! InfoOnly) {
			stuff.Save();
		}
		exit(0);
	}
	// ...
	// 3D scan
	// ---
	if (module == "3d") {
		str module ; strcpy(module,ModuleToUse.c_str());
		str card   ; strcpy(card,CardToUse.c_str());
		Scan3D delta (ANSWER_3D_WITH_YES,UseXForQuestions,card,module);
		delta.SetFile(D3_DATA);
		delta.SetCheck (checkFlag);
		delta.Scan(); Print3DData(delta);
		if (! InfoOnly) {
			delta.Save();
		}
		exit(0); 
	}
	cout << "sysp: no module for: " << module << endl;
	exit(1);  
}