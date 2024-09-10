RKCaughtX11Window::RKCaughtX11Window (WId window_to_embed, int device_number) : RKMDIWindow (0, X11Window) {
	RK_TRACE (MISC);

	commonInit (device_number);
	embedded = window_to_embed;

#ifdef Q_WS_WIN
	// unfortunately, trying to get KWindowInfo as below hangs on windows (KDElibs 4.2.3)
	WINDOWINFO wininfo;
	wininfo.cbSize = sizeof (WINDOWINFO);
	GetWindowInfo (embedded, &wininfo);

	// clip off the window frame and menubar
	xembed_container->setContentsMargins (wininfo.rcWindow.left - wininfo.rcClient.left, wininfo.rcWindow.top - wininfo.rcClient.top,
				wininfo.rcClient.right - wininfo.rcWindow.right, wininfo.rcClient.bottom - wininfo.rcWindow.bottom);
	// set a fixed size until the window is shown
	xembed_container->setFixedSize (wininfo.rcClient.right - wininfo.rcClient.left, wininfo.rcClient.bottom - wininfo.rcClient.top);
	setGeometry (wininfo.rcClient.left, wininfo.rcClient.right, wininfo.rcClient.top, wininfo.rcClient.bottom);	// see comment in X11 section
	move (wininfo.rcClient.left, wininfo.rcClient.top);		// else the window frame may be off scree on top/left.
#elif defined Q_WS_X11
	KWindowInfo wininfo = KWindowSystem::windowInfo (embedded, NET::WMName | NET::WMGeometry);
	RK_ASSERT (wininfo.valid ());

	// set a fixed size until the window is shown
	xembed_container->setFixedSize (wininfo.geometry ().width (), wininfo.geometry ().height ());
	setGeometry (wininfo.geometry ());	// it's important to set a size, even while not visible. Else DetachedWindowContainer will assign a default size of 640*480, and then size upwards, if necessary.
	setCaption (wininfo.name ());
#endif

	// somehow in Qt 4.4.3, when the RKCaughtWindow is reparented the first time, the QX11EmbedContainer may kill its client. Hence we delay the actual embedding until after the window was shown.
	// In some previous version of Qt, this was not an issue, but I did not track the versions.
	QTimer::singleShot (0, this, SLOT (doEmbed()));
}