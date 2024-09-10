static void menu_0_1(ldr_config *conf)
{
	wchar_t  auth[MAX_PATH];
	wchar_t *dp_type;
	char     ch;
			
	do
	{
		cls_console();

		if (conf->options & OP_EPS_TMO) 
		{
			_snwprintf(
				auth, sizeof_w(auth), L"%d seconds", conf->timeout);
		} else {
			wcscpy(auth, L"disabled");
		}

		if (conf->logon_type & LT_DSP_PASS) {
			dp_type = L"display \"*\"";
		} else {
			dp_type = L"disabled";
		}

		wprintf(
			L"1 - On/Off \"enter password\" message (%s)\n"
			L"2 - Change display password type (%s)\n"
			L"3 - Change password prompt text (%S)\n"
			L"4 - Enable embedded keyfile (%s)\n"
			L"5 - Change authentication timeout (%s)\n"
			L"6 - Cancel timeout if any key pressed (%s)\n"
			L"7 - Return to main menu\n\n",
			on_off(conf->logon_type & LT_MESSAGE),
			dp_type,
			conf->eps_msg,
			conf->logon_type & LT_EMBED_KEY ? L"enabled":L"disabled",
			auth,
			on_off(conf->options & OP_TMO_STOP));

		if ( (ch = getchr('1', '7')) == '7' ) {
			break;
		}

		if (ch == '1') 
		{
			set_flag(
				conf->logon_type, LT_MESSAGE, onoff_req());
		}

		if (ch == '2')
		{
			wprintf(
				L"1 - disabled\n"
				L"2 - display \"*\"\n");

			if (getchr('1', '2') == '2') {
				conf->logon_type |= LT_DSP_PASS;
			} else {
				conf->logon_type &= ~LT_DSP_PASS;
			}
		}

		if (ch == '3') {
			wprintf(L"Enter new prompt text: ");
			s_gets(conf->eps_msg, sizeof(conf->eps_msg));			
		}

		if (ch == '4')
		{
			wchar_t path[MAX_PATH];
			u8     *keyfile;
			u32     keysize;

			wprintf(L"Please enter path to keyfile: ");

			zeroauto(&conf->emb_key, sizeof(conf->emb_key));
			conf->logon_type &= ~LT_EMBED_KEY;
			conf->logon_type |= LT_GET_PASS;
			
			if (s_wgets(path, sizeof(path)) != 0)
			{
				if (load_file(path, &keyfile, &keysize) != ST_OK) {
					wprintf(L"keyfile not loaded\n");
					Sleep(1000);
				} else
				{
					if (keysize != 64) {
						wprintf(L"Embedded keyfile must be 64byte size\n");						
						Sleep(1000);
					} else 
					{
						wprintf(
							L"1 - Use embedded keyfile and password\n"
							L"2 - Use only embedded keyfile\n");

						if (getchr('1', '2') == '2') {							
							conf->logon_type &= ~LT_GET_PASS;
						}

						autocpy(&conf->emb_key, keyfile, sizeof(conf->emb_key));
						conf->logon_type |= LT_EMBED_KEY;
					}
					zeromem(keyfile, keysize);
					free(keyfile);
				}
			}
		}

		if (ch == '5')
		{				
			wprintf(L"Enter new timeout in seconds or 0 to disable: ");

			if (wscanf(L"%d", &conf->timeout) == 0) {
				conf->timeout = 0;
			}

			set_flag(
				conf->options, OP_EPS_TMO, (conf->timeout != 0));
		}

		if (ch == '6') 
		{
			set_flag(
				conf->options, OP_TMO_STOP, onoff_req());
		}
	} while (1);
}