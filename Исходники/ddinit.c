static int
DDCreateWindow(struct ggi_visual *vis)
{
	directx_priv *priv = GGIDIRECTX_PRIV(vis);
	int w = 640, h = 480;	/* default window size */
	int ws_flags = WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX;
	/* toplevel flags */

	if (priv->hParent) {
		/* determine the parent window size */
		RECT r;
		GetWindowRect(priv->hParent, &r);
		w = r.right - r.left;
		h = r.bottom - r.top;
		/* flags for a child window */
		ws_flags = WS_CHILD;
	} else if (priv->fullscreen)
		ws_flags = WS_VISIBLE | WS_POPUP;
	else {
		/* adjust the window size to accommodate for
		 * the client area
		 */
		RECT r;
		r.left = r.top = 0;
		r.right = w;
		r.bottom = h;
		AdjustWindowRectEx(&r, ws_flags, 0, 0);
		w = r.right - r.left;
		h = r.bottom - r.top;
	}

	/* create the window */
	priv->hWnd = CreateWindowEx(0, NAME, TITLE, ws_flags,
				    CW_USEDEFAULT, 0, w, h,
				    priv->hParent, NULL,
				    priv->hInstance, vis);
	if (!priv->hWnd) {
		if (priv->hCursor)
			DestroyCursor(priv->hCursor);
		priv->hCursor = NULL;
		return 0;
	}

	/* make sure the window is initially hidden */
	ShowWindow(priv->hWnd, SW_HIDE);

	/* initialize the DirectDraw interface */
	DirectDrawCreate(NULL, &priv->lpdd, NULL);
	IDirectDraw_QueryInterface(priv->lpdd, &IID_IDirectDraw2,
				   (LPVOID *) & priv->lpddext);

	return 1;
}