void G_loadAPI() {
	char homepath[512];
	char basepath[512];

	trap_Cvar_VariableStringBuffer("fs_homepath", homepath, sizeof (homepath));
	trap_Cvar_VariableStringBuffer("fs_basepath", basepath, sizeof (basepath));

	// Load the module
	if (!loadModule(basepath, homepath)) {
		printError();
		G_Error("Error loading %s\n", g_APImoduleName.string);
	}

	// Load the APIquery function
	if (!loadAPISymbols()) {
		printError();
		G_Error("Error loading symbols from %s\n", g_APImoduleName.string);
	}

	if (API_init(homepath, basepath, g_APImoduleName.string) != 0) {
		G_Error("Error calling API_init()");
	}

	G_Printf("%s: API module loaded!\n", GAME_VERSION);
}