int main(int argc, char **argv)
{
	GError     *error = NULL;
	GtkBuilder *builder;

#if defined(_WIN32) && defined(GFT_USE_MANIFEST)
	{
		INITCOMMONCONTROLSEX tim;
		memset(&tim, 0, sizeof tim);
		tim.dwSize = sizeof tim;
		tim.dwICC = ICC_ANIMATE_CLASS | ICC_BAR_CLASSES | ICC_COOL_CLASSES |
								ICC_DATE_CLASSES | ICC_HOTKEY_CLASS | ICC_INTERNET_CLASSES |
								ICC_LISTVIEW_CLASSES | ICC_NATIVEFNTCTL_CLASS |
								ICC_PAGESCROLLER_CLASS | ICC_PROGRESS_CLASS |
								ICC_TAB_CLASSES | ICC_TREEVIEW_CLASSES |
								ICC_UPDOWN_CLASS | ICC_USEREX_CLASSES | ICC_STANDARD_CLASSES;

		if(InitCommonControlsEx(&tim) == FALSE)
			fputs("warning: InitCommomControlsEx() failed\n", stderr);
	}
#endif

#ifndef _WIN32
	if(signal(SIGCHLD, SIG_IGN) == SIG_ERR)
		perror("signal(SIGCHLD)");
#endif

	ft_zero(&ft);
	ft_async(&ft) = 1;
	gtk_init(&argc, &argv); /* bail here if !$DISPLAY */

#ifdef _WIN32
	{
		int debug = 0;

		if(argc == 2){
			if(!strcmp(argv[1], "-d")){
				debug = 1;
				fprintf(stderr, "%s: debug on\n",
						*argv);
			}else{
usage:
				fprintf(stderr, "Usage: %s [-d]\n",
						*argv);
				return 1;
			}
		}else if(argc != 1)
			goto usage;

		if(!debug){
			fputs("gft: debug off\n", stderr);
			FreeConsole();
		}
	}
#else
	if(argc != 1){
		fprintf(stderr, "Usage: %s\n", *argv);
		return 1;
	}
#endif

	builder = gtk_builder_new();

	if(gladegen_init())
		return 1;

	if(!gtk_builder_add_from_file(builder, GLADE_XML_FILE, &error)){
		g_warning("%s", error->message);
		/*g_free(error);*/
		return 1;
	}
	gladegen_term();

	if(getobjects(builder))
		return 1;

	gtk_builder_connect_signals(builder, NULL);

	glist_init(&listTransfers, treeTransfers);

	/* don't need it anymore */
	g_object_unref(G_OBJECT(builder));

	/* signal setup */
	g_signal_connect(G_OBJECT(winMain), "delete-event" ,       G_CALLBACK(on_winMain_delete_event),    NULL);
	g_signal_connect(G_OBJECT(winMain), "destroy",             G_CALLBACK(on_winMain_destroy),         NULL);

	cfg_read(cboHost);
	tray_init(winMain, *argv);
	transfers_init(&listDone, treeDone);

	gtk_widget_set_sensitive(btnSend, FALSE);
	drag_init();

	cmds();
	gtk_widget_show_all(winMain);
	gtk_main();

	tray_term();

	return 0;
}