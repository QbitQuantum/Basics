xfClipboard* xf_clipboard_new(xfContext* xfc)
{
	int n;
	UINT32 id;
	rdpChannels* channels;
	xfClipboard* clipboard;

	clipboard = (xfClipboard*) calloc(1, sizeof(xfClipboard));

	xfc->clipboard = clipboard;

	clipboard->xfc = xfc;

	channels = ((rdpContext*) xfc)->channels;
	clipboard->channels = channels;

	clipboard->system = ClipboardCreate();

	clipboard->requestedFormatId = -1;

	clipboard->root_window = DefaultRootWindow(xfc->display);
	clipboard->clipboard_atom = XInternAtom(xfc->display, "CLIPBOARD", FALSE);

	if (clipboard->clipboard_atom == None)
	{
		WLog_ERR(TAG, "unable to get CLIPBOARD atom");
		free(clipboard);
		return NULL;
	}

	id = 1;
	clipboard->property_atom = XInternAtom(xfc->display, "_FREERDP_CLIPRDR", FALSE);
	clipboard->identity_atom = XInternAtom(xfc->display, "_FREERDP_CLIPRDR_ID", FALSE);

	XChangeProperty(xfc->display, xfc->drawable, clipboard->identity_atom,
			XA_INTEGER, 32, PropModeReplace, (BYTE*) &id, 1);

	XSelectInput(xfc->display, clipboard->root_window, PropertyChangeMask);

#ifdef WITH_XFIXES
	if (XFixesQueryExtension(xfc->display, &clipboard->xfixes_event_base, &clipboard->xfixes_error_base))
	{
		int xfmajor, xfminor;

		if (XFixesQueryVersion(xfc->display, &xfmajor, &xfminor))
		{
			XFixesSelectSelectionInput(xfc->display, clipboard->root_window,
				clipboard->clipboard_atom, XFixesSetSelectionOwnerNotifyMask);
			clipboard->xfixes_supported = TRUE;
		}
		else
		{
			WLog_ERR(TAG, "Error querying X Fixes extension version");
		}
	}
	else
	{
		WLog_ERR(TAG, "Error loading X Fixes extension");
	}
#else
	WLog_ERR(TAG, "Warning: Using clipboard redirection without XFIXES extension is strongly discouraged!");
#endif

	n = 0;

	clipboard->clientFormats[n].atom = XInternAtom(xfc->display, "_FREERDP_RAW", False);
	clipboard->clientFormats[n].formatId = 0;
	n++;

	clipboard->clientFormats[n].atom = XInternAtom(xfc->display, "UTF8_STRING", False);
	clipboard->clientFormats[n].formatId = CF_UNICODETEXT;
	n++;

	clipboard->clientFormats[n].atom = XA_STRING;
	clipboard->clientFormats[n].formatId = CF_TEXT;
	n++;

	clipboard->clientFormats[n].atom = XInternAtom(xfc->display, "image/png", False);
	clipboard->clientFormats[n].formatId = CB_FORMAT_PNG;
	n++;

	clipboard->clientFormats[n].atom = XInternAtom(xfc->display, "image/jpeg", False);
	clipboard->clientFormats[n].formatId = CB_FORMAT_JPEG;
	n++;

	clipboard->clientFormats[n].atom = XInternAtom(xfc->display, "image/gif", False);
	clipboard->clientFormats[n].formatId = CB_FORMAT_GIF;
	n++;

	clipboard->clientFormats[n].atom = XInternAtom(xfc->display, "image/bmp", False);
	clipboard->clientFormats[n].formatId = CF_DIB;
	n++;

	clipboard->clientFormats[n].atom = XInternAtom(xfc->display, "text/html", False);
	clipboard->clientFormats[n].formatId = CB_FORMAT_HTML;
	clipboard->clientFormats[n].formatName = _strdup("HTML Format");
	if (!clipboard->clientFormats[n].formatName)
	{
		ClipboardDestroy(clipboard->system);
		free(clipboard);
		return NULL;
	}
	n++;

	clipboard->numClientFormats = n;

	clipboard->targets[0] = XInternAtom(xfc->display, "TIMESTAMP", FALSE);
	clipboard->targets[1] = XInternAtom(xfc->display, "TARGETS", FALSE);
	clipboard->numTargets = 2;

	clipboard->incr_atom = XInternAtom(xfc->display, "INCR", FALSE);

	return clipboard;
}