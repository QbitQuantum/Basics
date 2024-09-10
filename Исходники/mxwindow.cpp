mxWindow::mxWindow (mxWindow *parent, int x, int y, int w, int h, const char *label, int style)
: mxWidget (parent, x, y, w, h, label)
{
	d_this = new mxWindow_i;
	d_this->d_uTimer = 0;

	DWORD dwStyle = 0;
	if (style == Normal)
		dwStyle = WS_OVERLAPPEDWINDOW;
	else if (style == Popup)
		dwStyle = WS_POPUP;
	else if (style == Dialog || style == ModalDialog)
		dwStyle = WS_CAPTION | WS_SYSMENU;

	void *parentHandle = 0;
	if (parent)
	{
		parentHandle = parent->getHandle ();
		dwStyle = WS_CHILD | WS_VISIBLE;
	}

	void *handle = (void *) CreateWindowEx (0, "mx_class", label, dwStyle,
					x, y, w, h, (HWND) parentHandle,
					(HMENU) NULL, (HINSTANCE) GetModuleHandle (NULL), NULL);

	SetWindowLong ((HWND) handle, GWL_USERDATA, reinterpret_cast< LONG >( this ) );

	setHandle (handle);
	setType (MX_WINDOW);
	setParent (parent);
	//setLabel (label);
	//setBounds (x, y, w, h);

	if (!parent && !g_mainWindow)
		g_mainWindow = this;
}