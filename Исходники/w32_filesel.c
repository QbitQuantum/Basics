gchar *filesel_select_file_open_folder(const gchar *title, const gchar *path)
{
	PIDLIST_ABSOLUTE pidl;
	gchar *str;
	gunichar2 *path16, *title16;
	glong conv_items;
	GError *error = NULL;
	WinChooserCtx *ctx;
#ifdef USE_PTHREAD
	pthread_t pt;
#endif

	/* Path needs to be converted to UTF-16, so that the native chooser
	 * can understand it. */
	path16 = g_utf8_to_utf16(path ? path : "",
			-1, NULL, &conv_items, &error);
	if (error != NULL) {
		alertpanel_error(_("Could not convert file path to UTF-16:\n\n%s"),
				error->message);
		debug_print("file path '%s' conversion to UTF-16 failed\n", path);
		g_error_free(error);
		return NULL;
	}

	/* Chooser dialog title needs to be UTF-16 as well. */
	title16 = g_utf8_to_utf16(title ? title : "",
			-1, NULL, NULL, &error);
	if (error != NULL) {
		debug_print("dialog title '%s' conversion to UTF-16 failed\n", title);
		g_error_free(error);
	}

	if (focus_window != NULL)
		b.hwndOwner = GDK_WINDOW_HWND(gtk_widget_get_window(focus_window));
	else
		b.hwndOwner = NULL;
	b.pszDisplayName = g_malloc(MAXPATHLEN);
	b.lpszTitle = title16;
	b.ulFlags = 0;
	b.pidlRoot = NULL;
	b.lpfn = _open_folder_callback;
	b.lParam = (LPARAM)path16;

	CoInitialize(NULL);

	ctx = g_new0(WinChooserCtx, 1);
	ctx->data = &b;
	ctx->done = FALSE;

#ifdef USE_PTHREAD
	if (pthread_create(&pt, PTHREAD_CREATE_JOINABLE, threaded_SHBrowseForFolder,
				(void *)ctx) != 0) {
		debug_print("Couldn't run in a thread, continuing unthreaded.\n");
		threaded_SHBrowseForFolder(ctx);
	} else {
		while (!ctx->done) {
			claws_do_idle();
		}
		pthread_join(pt, NULL);
	}
	pidl = ctx->return_value_pidl;
#else
	debug_print("No threads available, continuing unthreaded.\n");
	pidl = SHBrowseForFolder(&b);
#endif

	g_free(b.pszDisplayName);
	g_free(title16);
	g_free(path16);

	if (pidl == NULL) {
		CoUninitialize();
		g_free(ctx);
		return NULL;
	}

	path16 = malloc(MAX_PATH);
	if (!SHGetPathFromIDList(pidl, path16)) {
		CoTaskMemFree(pidl);
		CoUninitialize();
		g_free(path16);
		g_free(ctx);
		return NULL;
	}

	/* Now convert the returned file path back from UTF-16. */
	/* Unfortunately, there is no field in BROWSEINFO struct to indicate
	 * actual length of string in pszDisplayName, so we have to assume
	 * the string is null-terminated. */
	str = g_utf16_to_utf8(path16, -1, NULL, NULL, &error);
	if (error != NULL) {
		alertpanel_error(_("Could not convert file path back to UTF-8:\n\n%s"),
				error->message);
		debug_print("returned file path conversion to UTF-8 failed\n");
		g_error_free(error);
	}
	CoTaskMemFree(pidl);
	CoUninitialize();
	g_free(ctx);
	g_free(path16);

	return str;
}