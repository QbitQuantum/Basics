int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpOriginalCmdLine,
	int nCmdShow)
{
	int i;
	LOADED_IMAGE oImg;
	LPWSTR lpCmdLine;
	wchar_t parentDir[MAX_PATH+1] = L"", exePath[MAX_PATH+1] = L"";
	size_t szParentDir, szExeStr, szCmdLine, szPlatExe;
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	LPWSTR *argv = __wargv;
	int argc = __argc;

	// Zero out our loaded image struct.
	ZeroMemory(&oImg, sizeof(oImg));

	/* Make sure we have args. */
	if(argc == 1) {
		Fatal(1L, L"No images specified.");
	}
	

	/* Get our exe's parent folder. */
	if(!GetParentDir(parentDir, &szParentDir)) {
		Fatal(1L, L"Could not get parent folder of image, \"%s\". This should not happen ever.", argv[0]);
	}

	/* Iterate through our arguments */
	for(i = 1; i < argc; i++) {
		/* Verify file exists. */
		if(_waccess(argv[i], 00) == -1) {
			Fatal(1L, L"File does not exist.\nFile: %s", argv[i]);
		}

		/* Get the binary type. */
		if(!MapAndLoadW(argv[i], &oImg)) {
			Fatal(1L, L"Unable to get binary type for image.\nImage: %s", argv[i]);
		}

		lstrcpyW(exePath, parentDir);
		switch(oImg.FileHeader->FileHeader.Machine)
		{
			case IMAGE_FILE_MACHINE_I386:
				lstrcatW(exePath, x86exe);
				szPlatExe = SZ_86_EXE;
				break;
			// TODO: Differentiate between x64 platforms.
			case IMAGE_FILE_MACHINE_AMD64:
				lstrcatW(exePath, amd64exe);
				szPlatExe = SZ_AMD_EXE;
				break;
			case IMAGE_FILE_MACHINE_IA64:
				lstrcatW(exePath, ia64exe);
				szPlatExe = SZ_IA_EXE;
				break;
			default:
				Fatal(1L, L"Unknown binary type returned for image.\nImage: %s\n\nBinary Type: %d", argv[i], oImg.FileHeader->FileHeader.Machine);
		}

		if(!UnMapAndLoad(&oImg)) {
			Fatal(1L, L"Failed to unload/unmap image.\nImage: %s", argv[i]);
		}

		/* Calculate the length of the eventual exe path with surrounding quotes. */
		lstrcatW(exePath, depsexe);
		szExeStr = szParentDir + szPlatExe + 2; // +2 for the two "s surrounding the image path.

		/* Allocate our command line string. */
		// szExeStr+         1 +1+wcslen(argv)+1
		// "(path)depends.exe" "argv"
		szCmdLine = szExeStr + lstrlenW(argv[i]) + 3;
		lpCmdLine = (LPWSTR)LocalAlloc(LPTR, sizeof(wchar_t) * (szCmdLine + 1));
		if(lpCmdLine == NULL) {
			Fatal(1L, L"Could not allocate memory.\nMemory required (bytes): %d", sizeof(wchar_t) * (szCmdLine + 1));
		}
		if(swprintf(lpCmdLine, szCmdLine+1, L"\"%s\" \"%s\"", exePath, argv[i]) == -1) {
			LocalFree(lpCmdLine);
			FatalCall(L"swprintf");
		}

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		/* Depends launching. */
		if (!CreateProcessW(
			NULL,		/* No module name (use command line) */
			lpCmdLine,	/* Command line */
			NULL,		/* Process handle not inheritable */
			NULL,		/* Thread handle not inheritable */
			FALSE,		/* Set handle inheritance to FALSE */
			0,			/* No creation flags */
			NULL,		/* Use parent's environment block */
			NULL,		/* Use parent's starting directory */
			&si,		/* Pointer to STARTUPINFO structure */
			&pi			/* Pointer to PROCESS_INFORMATION structure */
		)) {
			// len("CreateProcessW") + len(" - ") + len(cmdline)
			szCmdLine += 17;
			LocalFree(lpCmdLine);
			lpCmdLine = (LPWSTR)LocalAlloc(LPTR, sizeof(wchar_t) * (szCmdLine + 1));
			swprintf(lpCmdLine, szCmdLine+1, L"CreateProcessW - \"%s\" \"%s\"", exePath, argv[i]);
			FatalCall(lpCmdLine);
		}
		LocalFree(lpCmdLine);
	}
	return 0;
}