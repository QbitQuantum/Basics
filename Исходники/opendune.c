int main(int argc, char **argv)
#endif /* __APPLE__ */
{
	bool commit_dune_cfg = false;
#if defined(_WIN32)
	#if defined(__MINGW32__) && defined(__STRICT_ANSI__)
		int __cdecl __MINGW_NOTHROW _fileno (FILE*);
	#endif
	FILE *err = fopen("error.log", "w");
	FILE *out = fopen("output.log", "w");

	#if defined(_MSC_VER)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

	if (err != NULL) _dup2(_fileno(err), _fileno(stderr));
	if (out != NULL) _dup2(_fileno(out), _fileno(stdout));
	FreeConsole();
#endif
	CrashLog_Init();

	VARIABLE_NOT_USED(argc);
	VARIABLE_NOT_USED(argv);

	/* Load opendune.ini file */
	Load_IniFile();

	if (!File_Init()) {
		Error("Cannot initialise files. Does %s directory exist ?\n", DATA_DIR);
		exit(1);
	}

	/* Loading config from dune.cfg */
	if (!Config_Read("dune.cfg", &g_config)) {
		Config_Default(&g_config);
		commit_dune_cfg = true;
	}
	/* reading config from opendune.ini which prevail over dune.cfg */
	SetLanguage_From_IniFile(&g_config);

	/* Writing config to dune.cfg */
	if (commit_dune_cfg && !Config_Write("dune.cfg", &g_config)) {
		Error("Error writing to dune.cfg file.\n");
		exit(1);
	}

	Input_Init();

	Drivers_All_Init();

	if (!Unknown_25C4_000E()) exit(1);

	g_var_7097 = 0;

	GameLoop_Main();

	printf("%s\n", String_Get_ByIndex(STR_THANK_YOU_FOR_PLAYING_DUNE_II));

	PrepareEnd();
	Free_IniFile();
	exit(0);
}