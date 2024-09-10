	void GetOptions(char**& argv, int& i) {
		char* p, *ps;
		char c[LINEMAX];
		while (argv[i] && *argv[i] == '-') {
			if (*(argv[i] + 1) == '-') {
				p = argv[i++] + 2;
			} else {
				p = argv[i++] + 1;
			}
			memset(c, 0, LINEMAX); //todo
			ps = STRSTR(p, "=");
			if (ps != NULL) {
				STRNCPY(c, LINEMAX, p, (int)(ps - p));
			} else {
				STRCPY(c, LINEMAX, p);
			}

			if (!strcmp(c, "lstlab")) {
				AddLabelListing = 1;
			} else if (!strcmp(c, "help")) {
				// nothing
			} else if (!strcmp(c, "sym")) {
				if ((ps)&&(ps+1)) {
					STRCPY(SymbolListFName, LINEMAX, ps+1);
				} else {
					_COUT "No parameters found in " _CMDL argv[i-1] _ENDL;
				}
			} else if (!strcmp(c, "lst")) {
				if ((ps)&&(ps+1)) {
					STRCPY(ListingFName, LINEMAX, ps+1);
				} else {
					_COUT "No parameters found in " _CMDL argv[i-1] _ENDL;
				}
			} else if (!strcmp(c, "exp")) {
				if ((ps)&&(ps+1)) {
					STRCPY(ExportFName, LINEMAX, ps+1);
				} else {
					_COUT "No parameters found in " _CMDL argv[i-1] _ENDL;
				}
			/*} else if (!strcmp(c, "zxlab")) {
				if (ps+1) {
					STRCPY(UnrealLabelListFName, LINEMAX, ps+1);
				} else {
					_COUT "No parameters found in " _CMDL argv[i] _ENDL;
				}*/
			} else if (!strcmp(c, "raw")) {
				if ((ps)&&(ps+1)) {
					STRCPY(RAWFName, LINEMAX, ps+1);
				} else {
					_COUT "No parameters found in " _CMDL argv[i-1] _ENDL;
				}
			} else if (!strcmp(c, "fullpath")) {
				IsShowFullPath = 1;
			} else if (!strcmp(c, "reversepop")) {
				IsReversePOP = 1;
			} else if (!strcmp(c, "nologo")) {
				HideLogo = 1;
			} else if (!strcmp(c, "dos866")) {
				ConvertEncoding = ENCDOS;
			} else if (!strcmp(c, "dirbol")) {
				IsPseudoOpBOF = 1;
			} else if (!strcmp(c, "inc")) {
				if ((ps)&&(ps+1)) {
					IncludeDirsList = new CStringsList(ps+1, IncludeDirsList);
				} else {
					_COUT "No parameters found in " _CMDL argv[i-1] _ENDL;
				}
			} else if (*p == 'i' || *p == 'I') {
				IncludeDirsList = new CStringsList(p+1, IncludeDirsList);
			} else {
				_COUT "Unrecognized option: " _CMDL c _ENDL;
			}
		}
	}