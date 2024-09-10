int
main (int argc, char *argv[])
{
	int i;
	int ret;

        // BEGIN NEW CODE
        server *fake_serv;
        GIOChannel *channel;
        session *sess;
        // END NEW CODE

#ifdef WIN32
	HRESULT coinit_result;
#endif

	srand ((unsigned int) time (NULL)); /* CL: do this only once! */

	/* We must check for the config dir parameter, otherwise load_config() will behave incorrectly.
	 * load_config() must come before fe_args() because fe_args() calls gtk_init() which needs to
	 * know the language which is set in the config. The code below is copy-pasted from fe_args()
	 * for the most part. */
	if (argc >= 2)
	{
		for (i = 1; i < argc; i++)
		{
			if ((strcmp (argv[i], "-d") == 0 || strcmp (argv[i], "--cfgdir") == 0)
				&& i + 1 < argc)
			{
				xdir = g_strdup (argv[i + 1]);
			}
			else if (strncmp (argv[i], "--cfgdir=", 9) == 0)
			{
				xdir = g_strdup (argv[i] + 9);
			}

			if (xdir != NULL)
			{
				if (xdir[strlen (xdir) - 1] == G_DIR_SEPARATOR)
				{
					xdir[strlen (xdir) - 1] = 0;
				}
				break;
			}
		}
	}

#if ! GLIB_CHECK_VERSION (2, 36, 0)
        // RFM: Don't think we hit this
	g_type_init ();
#endif

	if (check_config_dir () == 0)
	{
		if (load_config () != 0)
			load_default_config ();
	} else
	{
		/* this is probably the first run */
		load_default_config ();
		make_config_dirs ();
		make_dcc_dirs ();
	}

	/* we MUST do this after load_config () AND before fe_init (thus gtk_init) otherwise it will fail */
	// RFM: Does nothing on *NIX
        set_locale ();

        // RFM: Parses some command line crap. Not important
	ret = fe_args (argc, argv);
	if (ret != -1)
		return ret;
	
#ifdef USE_DBUS
	hexchat_remote ();
#endif

#ifdef USE_LIBPROXY
        // RFM: Not using
	libproxy_factory = px_proxy_factory_new();
#endif

#ifdef WIN32
	coinit_result = CoInitializeEx (NULL, COINIT_APARTMENTTHREADED);
	if (SUCCEEDED (coinit_result))
	{
		CoInitializeSecurity (NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	}
#endif

        // RFM: Inits some fe-text stuff
	fe_init ();

        // RFM: Pretty sure this just allows us to save chats...
	/* This is done here because cfgfiles.c is too early in
	* the startup process to use gtk functions. */
	if (g_access (get_xdir (), W_OK) != 0)
	{
		char buf[2048];

		g_snprintf (buf, sizeof(buf),
			_("You do not have write access to %s. Nothing from this session can be saved."),
			get_xdir ());
		fe_message (buf, FE_MSG_ERROR);
	}

        // RFM: Checks if root on *NIX 
#ifndef WIN32
#ifndef __EMX__
	/* OS/2 uses UID 0 all the time */
	if (getuid () == 0)
		fe_message (_("* Running IRC as root is stupid! You should\n"
			      "  create a User Account and use that to login.\n"), FE_MSG_WARN|FE_MSG_WAIT);
#endif
#endif /* !WIN32 */

        // RFM: Loads a bunch of configure options
	xchat_init ();

        // BEGIN NEW CODE
        fake_serv = server_new();
        fake_serv->sok = STDIN_FILENO;
        //        fake_serv->pos = 0; //??? 
        sess = session_new(fake_serv, "fake_sess", SESS_CHANNEL, 0);
        fake_serv->server_session = sess;
        fake_serv->front_session = sess;
        channel = g_io_channel_unix_new(STDIN_FILENO);
        g_io_add_watch(channel, G_IO_IN, (GIOFunc)server_read, fake_serv);
        //g_io_add_watch(channel, G_IO_IN, (GIOFunc)io_callback, fake_serv);
        g_io_channel_unref(channel);
        // END NEW CODE

	fe_main ();

#ifdef WIN32
	if (SUCCEEDED (coinit_result))
	{
		CoUninitialize ();
	}
#endif

#ifdef USE_LIBPROXY
	px_proxy_factory_free(libproxy_factory);
#endif

#ifdef WIN32
	WSACleanup ();
#endif

	return 0;
}