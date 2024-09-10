/*
 * Dialog-box function for the main PuTTYgen dialog box.
 */
static int CALLBACK MainDlgProc(HWND hwnd, UINT msg,
				WPARAM wParam, LPARAM lParam)
{
    static const char generating_msg[] =
	"Please wait while a key is generated...";
    static const char entropy_msg[] =
	"Please generate some randomness by moving the mouse over the blank area.";
    struct MainDlgState *state;

    switch (msg) {
      case WM_INITDIALOG:
        if (help_path)
            SetWindowLong(hwnd, GWL_EXSTYLE,
                          GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_CONTEXTHELP);
        else {
            /*
             * If we add a Help button, this is where we destroy it
             * if the help file isn't present.
             */
        }
        requested_help = FALSE;
	SendMessage(hwnd, WM_SETICON, (WPARAM) ICON_BIG,
		    (LPARAM) LoadIcon(hinst, MAKEINTRESOURCE(200)));

	state = snew(struct MainDlgState);
	state->generation_thread_exists = FALSE;
	state->collecting_entropy = FALSE;
	state->entropy = NULL;
	state->key_exists = FALSE;
	SetWindowLong(hwnd, GWL_USERDATA, (LONG) state);
	{
	    HMENU menu, menu1;

	    menu = CreateMenu();

	    menu1 = CreateMenu();
	    AppendMenu(menu1, MF_ENABLED, IDC_LOAD, "&Load private key");
	    AppendMenu(menu1, MF_ENABLED, IDC_SAVEPUB, "Save p&ublic key");
	    AppendMenu(menu1, MF_ENABLED, IDC_SAVE, "&Save private key");
	    AppendMenu(menu1, MF_SEPARATOR, 0, 0);
	    AppendMenu(menu1, MF_ENABLED, IDC_QUIT, "E&xit");
	    AppendMenu(menu, MF_POPUP | MF_ENABLED, (UINT) menu1, "&File");
	    state->filemenu = menu1;

	    menu1 = CreateMenu();
	    AppendMenu(menu1, MF_ENABLED, IDC_GENERATE, "&Generate key pair");
	    AppendMenu(menu1, MF_SEPARATOR, 0, 0);
	    AppendMenu(menu1, MF_ENABLED, IDC_KEYSSH1, "SSH&1 key (RSA)");
	    AppendMenu(menu1, MF_ENABLED, IDC_KEYSSH2RSA, "SSH2 &RSA key");
	    AppendMenu(menu1, MF_ENABLED, IDC_KEYSSH2DSA, "SSH2 &DSA key");
	    AppendMenu(menu, MF_POPUP | MF_ENABLED, (UINT) menu1, "&Key");
	    state->keymenu = menu1;

	    menu1 = CreateMenu();
	    AppendMenu(menu1, MF_ENABLED, IDC_IMPORT, "&Import key");
	    AppendMenu(menu1, MF_SEPARATOR, 0, 0);
	    AppendMenu(menu1, MF_ENABLED, IDC_EXPORT_OPENSSH,
		       "Export &OpenSSH key");
	    AppendMenu(menu1, MF_ENABLED, IDC_EXPORT_SSHCOM,
		       "Export &ssh.com key");
	    AppendMenu(menu, MF_POPUP | MF_ENABLED, (UINT) menu1,
		       "Con&versions");
	    state->cvtmenu = menu1;

	    menu1 = CreateMenu();
	    AppendMenu(menu1, MF_ENABLED, IDC_ABOUT, "&About");
	    if (help_path)
		AppendMenu(menu1, MF_ENABLED, IDC_GIVEHELP, "&Help");
	    AppendMenu(menu, MF_POPUP | MF_ENABLED, (UINT) menu1, "&Help");

	    SetMenu(hwnd, menu);
	}

	/*
	 * Centre the window.
	 */
	{			       /* centre the window */
	    RECT rs, rd;
	    HWND hw;

	    hw = GetDesktopWindow();
	    if (GetWindowRect(hw, &rs) && GetWindowRect(hwnd, &rd))
		MoveWindow(hwnd,
			   (rs.right + rs.left + rd.left - rd.right) / 2,
			   (rs.bottom + rs.top + rd.top - rd.bottom) / 2,
			   rd.right - rd.left, rd.bottom - rd.top, TRUE);
	}

	{
	    struct ctlpos cp, cp2;

	    /* Accelerators used: acglops1rbd */

	    ctlposinit(&cp, hwnd, 4, 4, 4);
	    beginbox(&cp, "Key", IDC_BOX_KEY);
	    cp2 = cp;
	    statictext(&cp2, "No key.", 1, IDC_NOKEY);
	    cp2 = cp;
	    statictext(&cp2, "", 1, IDC_GENERATING);
	    progressbar(&cp2, IDC_PROGRESS);
	    bigeditctrl(&cp,
			"&Public key for pasting into authorized_keys file:",
			IDC_PKSTATIC, IDC_KEYDISPLAY, 5);
	    SendDlgItemMessage(hwnd, IDC_KEYDISPLAY, EM_SETREADONLY, 1, 0);
	    staticedit(&cp, "Key f&ingerprint:", IDC_FPSTATIC,
		       IDC_FINGERPRINT, 75);
	    SendDlgItemMessage(hwnd, IDC_FINGERPRINT, EM_SETREADONLY, 1,
			       0);
	    staticedit(&cp, "Key &comment:", IDC_COMMENTSTATIC,
		       IDC_COMMENTEDIT, 75);
	    staticpassedit(&cp, "Key p&assphrase:", IDC_PASSPHRASE1STATIC,
			   IDC_PASSPHRASE1EDIT, 75);
	    staticpassedit(&cp, "C&onfirm passphrase:",
			   IDC_PASSPHRASE2STATIC, IDC_PASSPHRASE2EDIT, 75);
	    endbox(&cp);
	    beginbox(&cp, "Actions", IDC_BOX_ACTIONS);
	    staticbtn(&cp, "Generate a public/private key pair",
		      IDC_GENSTATIC, "&Generate", IDC_GENERATE);
	    staticbtn(&cp, "Load an existing private key file",
		      IDC_LOADSTATIC, "&Load", IDC_LOAD);
	    static2btn(&cp, "Save the generated key", IDC_SAVESTATIC,
		       "Save p&ublic key", IDC_SAVEPUB,
		       "&Save private key", IDC_SAVE);
	    endbox(&cp);
	    beginbox(&cp, "Parameters", IDC_BOX_PARAMS);
	    radioline(&cp, "Type of key to generate:", IDC_TYPESTATIC, 3,
		      "SSH&1 (RSA)", IDC_KEYSSH1,
		      "SSH2 &RSA", IDC_KEYSSH2RSA,
		      "SSH2 &DSA", IDC_KEYSSH2DSA, NULL);
	    staticedit(&cp, "Number of &bits in a generated key:",
		       IDC_BITSSTATIC, IDC_BITS, 20);
	    endbox(&cp);
	}
	CheckRadioButton(hwnd, IDC_KEYSSH1, IDC_KEYSSH2DSA, IDC_KEYSSH2RSA);
	CheckMenuRadioItem(state->keymenu, IDC_KEYSSH1, IDC_KEYSSH2DSA,
			   IDC_KEYSSH2RSA, MF_BYCOMMAND);
	SetDlgItemInt(hwnd, IDC_BITS, DEFAULT_KEYSIZE, FALSE);

	/*
	 * Initially, hide the progress bar and the key display,
	 * and show the no-key display. Also disable the Save
	 * buttons, because with no key we obviously can't save
	 * anything.
	 */
	ui_set_state(hwnd, state, 0);

	/*
	 * Load a key file if one was provided on the command line.
	 */
	if (cmdline_keyfile)
	    load_key_file(hwnd, state, filename_from_str(cmdline_keyfile), 0);

	return 1;
      case WM_MOUSEMOVE:
	state = (struct MainDlgState *) GetWindowLong(hwnd, GWL_USERDATA);
	if (state->collecting_entropy &&
	    state->entropy && state->entropy_got < state->entropy_required) {
	    state->entropy[state->entropy_got++] = lParam;
	    state->entropy[state->entropy_got++] = GetMessageTime();
	    SendDlgItemMessage(hwnd, IDC_PROGRESS, PBM_SETPOS,
			       state->entropy_got, 0);
	    if (state->entropy_got >= state->entropy_required) {
		struct rsa_key_thread_params *params;
		DWORD threadid;

		/*
		 * Seed the entropy pool
		 */
		random_add_heavynoise(state->entropy, state->entropy_size);
		memset(state->entropy, 0, state->entropy_size);
		sfree(state->entropy);
		state->collecting_entropy = FALSE;

		SetDlgItemText(hwnd, IDC_GENERATING, generating_msg);
		SendDlgItemMessage(hwnd, IDC_PROGRESS, PBM_SETRANGE, 0,
				   MAKELPARAM(0, PROGRESSRANGE));
		SendDlgItemMessage(hwnd, IDC_PROGRESS, PBM_SETPOS, 0, 0);

		params = snew(struct rsa_key_thread_params);
		params->progressbar = GetDlgItem(hwnd, IDC_PROGRESS);
		params->dialog = hwnd;
		params->keysize = state->keysize;
		params->is_dsa = state->is_dsa;
		params->key = &state->key;
		params->dsskey = &state->dsskey;

		if (!CreateThread(NULL, 0, generate_rsa_key_thread,
				  params, 0, &threadid)) {
		    MessageBox(hwnd, "Out of thread resources",
			       "Key generation error",
			       MB_OK | MB_ICONERROR);
		    sfree(params);
		} else {
		    state->generation_thread_exists = TRUE;
		}
	    }
	}
	break;
      case WM_COMMAND:
	switch (LOWORD(wParam)) {
	  case IDC_KEYSSH1:
	  case IDC_KEYSSH2RSA:
	  case IDC_KEYSSH2DSA:
	    {
		state = (struct MainDlgState *)
		    GetWindowLong(hwnd, GWL_USERDATA);
		if (!IsDlgButtonChecked(hwnd, LOWORD(wParam)))
		    CheckRadioButton(hwnd, IDC_KEYSSH1, IDC_KEYSSH2DSA,
				     LOWORD(wParam));
		CheckMenuRadioItem(state->keymenu, IDC_KEYSSH1, IDC_KEYSSH2DSA,
				   LOWORD(wParam), MF_BYCOMMAND);
	    }
	    break;
	  case IDC_QUIT:
	    PostMessage(hwnd, WM_CLOSE, 0, 0);
	    break;
	  case IDC_COMMENTEDIT:
	    if (HIWORD(wParam) == EN_CHANGE) {
		state = (struct MainDlgState *)
		    GetWindowLong(hwnd, GWL_USERDATA);
		if (state->key_exists) {
		    HWND editctl = GetDlgItem(hwnd, IDC_COMMENTEDIT);
		    int len = GetWindowTextLength(editctl);
		    if (*state->commentptr)
			sfree(*state->commentptr);
		    *state->commentptr = snewn(len + 1, char);
		    GetWindowText(editctl, *state->commentptr, len + 1);
		    if (state->ssh2) {
			setupbigedit2(hwnd, IDC_KEYDISPLAY, IDC_PKSTATIC,
				      &state->ssh2key);
		    } else {
			setupbigedit1(hwnd, IDC_KEYDISPLAY, IDC_PKSTATIC,
				      &state->key);
		    }
		}
	    }