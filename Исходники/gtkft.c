static void
open_button_cb(GtkButton *button, PidginXferDialog *dialog)
{
#ifdef _WIN32
	/* If using Win32... */
	int code;
	if (G_WIN32_HAVE_WIDECHAR_API ()) {
		wchar_t *wc_filename = g_utf8_to_utf16(
				purple_xfer_get_local_filename(
					dialog->selected_xfer),
				-1, NULL, NULL, NULL);

		code = (int) ShellExecuteW(NULL, NULL, wc_filename, NULL, NULL,
				SW_SHOW);

		g_free(wc_filename);
	} else {
		char *l_filename = g_locale_from_utf8(
				purple_xfer_get_local_filename(
					dialog->selected_xfer),
				-1, NULL, NULL, NULL);

		code = (int) ShellExecuteA(NULL, NULL, l_filename, NULL, NULL,
				SW_SHOW);

		g_free(l_filename);
	}

	if (code == SE_ERR_ASSOCINCOMPLETE || code == SE_ERR_NOASSOC)
	{
		purple_notify_error(dialog, NULL,
				_("There is no application configured to open this type of file."), NULL);
	}
	else if (code < 32)
	{
		purple_notify_error(dialog, NULL,
				_("An error occurred while opening the file."), NULL);
		purple_debug_warning("ft", "filename: %s; code: %d\n",
				purple_xfer_get_local_filename(dialog->selected_xfer), code);
	}
#else
	const char *filename = purple_xfer_get_local_filename(dialog->selected_xfer);
	char *command = NULL;
	char *tmp = NULL;
	GError *error = NULL;

	if (purple_running_gnome())
	{
		char *escaped = g_shell_quote(filename);
		command = g_strdup_printf("gnome-open %s", escaped);
		g_free(escaped);
	}
	else if (purple_running_kde())
	{
		char *escaped = g_shell_quote(filename);

		if (purple_str_has_suffix(filename, ".desktop"))
			command = g_strdup_printf("kfmclient openURL %s 'text/plain'", escaped);
		else
			command = g_strdup_printf("kfmclient openURL %s", escaped);
		g_free(escaped);
	}
	else
	{
		purple_notify_uri(NULL, filename);
		return;
	}

	if (purple_program_is_valid(command))
	{
		gint exit_status;
		if (!g_spawn_command_line_sync(command, NULL, NULL, &exit_status, &error))
		{
			tmp = g_strdup_printf(_("Error launching %s: %s"),
							purple_xfer_get_local_filename(dialog->selected_xfer),
							error->message);
			purple_notify_error(dialog, NULL, _("Unable to open file."), tmp);
			g_free(tmp);
			g_error_free(error);
		}
		if (exit_status != 0)
		{
			char *primary = g_strdup_printf(_("Error running %s"), command);
			char *secondary = g_strdup_printf(_("Process returned error code %d"),
									exit_status);
			purple_notify_error(dialog, NULL, primary, secondary);
			g_free(tmp);
		}
	}
#endif
}