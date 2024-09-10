int __cdecl wmain(int argc, wchar_t *wargv[])
{
	int ret = 0;

	// Global URL cache to not download anything twice
	json_t *url_cache = json_object();
	// Repository ID cache to prioritize the most local repository if more
	// than one repository with the same name is discovered in the network
	json_t *id_cache = json_object();

	json_t *repo_list = NULL;

	const char *start_repo = "http://thcrap.nmlgc.net/repos/nmlgc/";

	json_t *sel_stack = NULL;
	json_t *new_cfg = json_pack("{s[]}", "patches");

	size_t cur_dir_len = GetCurrentDirectory(0, NULL) + 1;
	VLA(char, cur_dir, cur_dir_len);
	json_t *games = NULL;

	const char *run_cfg_fn = NULL;
	const char *run_cfg_fn_js = NULL;
	char *run_cfg_str = NULL;

	json_t *args = json_array_from_wchar_array(argc, wargv);

	wine_flag = GetProcAddress(
		GetModuleHandleA("kernel32.dll"), "wine_get_unix_file_name"
	) != 0;

	strings_mod_init();
	log_init(1);

	// Necessary to correctly process *any* input of non-ASCII characters
	// in the console subsystem
	w32u8_set_fallback_codepage(GetOEMCP());

	GetCurrentDirectory(cur_dir_len, cur_dir);
	PathAddBackslashA(cur_dir);
	str_slash_normalize(cur_dir);

	// Maximize the height of the console window... unless we're running under
	// Wine, where this 1) doesn't work and 2) messes up the console buffer
	if(!wine_flag) {
		CONSOLE_SCREEN_BUFFER_INFO sbi = {0};
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD largest = GetLargestConsoleWindowSize(console);
		HWND console_wnd = GetConsoleWindow();
		RECT console_rect;

		GetWindowRect(console_wnd, &console_rect);
		SetWindowPos(console_wnd, NULL, console_rect.left, 0, 0, 0, SWP_NOSIZE);
		GetConsoleScreenBufferInfo(console, &sbi);
		sbi.srWindow.Bottom = largest.Y - 4;
		SetConsoleWindowInfo(console, TRUE, &sbi.srWindow);
	}

	http_init();

	if(json_array_size(args) > 1) {
		start_repo = json_array_get_string(args, 1);
	}

	log_printf(
		"==========================================\n"
		"Touhou Community Reliant Automatic Patcher - Patch configuration tool\n"
		"==========================================\n"
		"\n"
		"\n"
		"This tool will create a new patch configuration for the\n"
		"Touhou Community Reliant Automatic Patcher.\n"
		"\n"
		"\n"
		"The configuration process has two steps:\n"
		"\n"
		"\t\t1. Selecting patches\n"
		"\t\t2. Download game-independent data\n"
		"\t\t3. Locating game installations\n"
		"\t\t4. Download game-specific data\n"
		"\n"
		"\n"
		"\n"
		"Patch repository discovery will start at\n"
		"\n"
		"\t%s\n"
		"\n"
		"You can specify a different URL as a command-line parameter.\n"
		"Additionally, all patches from previously discovered repositories, stored in\n"
		"subdirectories of the current directory, will be available for selection.\n"
		"\n"
		"\n",
		start_repo
	);
	pause();

	if(RepoDiscoverAtURL(start_repo, id_cache, url_cache)) {
		goto end;
	}
	if(RepoDiscoverFromLocal(id_cache, url_cache)) {
		goto end;
	}
	repo_list = RepoLoad();
	if(!json_object_size(repo_list)) {
		log_printf("No patch repositories available...\n");
		pause();
		goto end;
	}
	sel_stack = SelectPatchStack(repo_list);
	if(json_array_size(sel_stack)) {
		json_t *new_cfg_patches = json_object_get(new_cfg, "patches");
		size_t i;
		json_t *sel;

		log_printf("Downloading game-independent data...\n");
		stack_update(update_filter_global, NULL);

		/// Build the new run configuration
		json_array_foreach(sel_stack, i, sel) {
			json_array_append_new(new_cfg_patches, patch_build(sel));
		}
	}