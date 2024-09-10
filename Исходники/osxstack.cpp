void MCStack::realize()
{ //create window
	if (!MCnoui && MCModeMakeLocalWindows())
	{
		if ( getextendedstate(ECS_FULLSCREEN) )
		{
		//TS-2008-08-01 : [[Bug 5703 - fullscreen stack prop interacts badly with HideMenuBar]]
			if (!((MCScreenDC*)MCscreen)->getmenubarhidden())
				SetSystemUIMode(kUIModeAllHidden, kUIOptionAutoShowMenuBar);

			const MCDisplay *t_display;
			t_display = MCscreen -> getnearestdisplay(rect);
			MCRectangle t_workarea, t_viewport;
			t_workarea = t_display -> workarea;
			t_viewport = t_display -> viewport ;
			setrect(t_viewport);
		}
		else
		{
			if (!((MCScreenDC*)MCscreen)->getmenubarhidden())
				SetSystemUIMode(kUIModeNormal, NULL);
		}

		Rect wrect;
		MCScreenDC *psdc = (MCScreenDC *)MCscreen;
		psdc->MCRect2MacRect(rect, wrect);
		window = new _Drawable;
		window->type = DC_WINDOW;
		window->handle.window = 0;
		char *tmpname = NULL;
		const unsigned char *namePascal;
		if (!isunnamed())
		{ //set window title to name of stack temporarily.
			tmpname = strclone(getname_cstring()); //it will be changed by setname() later.
			namePascal = c2pstr(tmpname);
		}
		else
			namePascal = (unsigned char*)"\p";

		loadwindowshape();


		window->handle.window = NULL;
		uint32_t wclass;
		uint32_t wattributes;
		getWinstyle(wattributes,wclass);
		
		wattributes |= kWindowCompositingAttribute;

		long testdecorations = WD_TITLE | WD_MENU | WD_CLOSE | WD_MINIMIZE | WD_MAXIMIZE;

		if (m_window_shape != NULL)
		{
			static WindowDefUPP s_window_mask_proc = NULL;
			if (s_window_mask_proc == NULL)
				s_window_mask_proc = NewWindowDefUPP(WindowMaskProc);
			
			WindowDefSpec t_spec;
			t_spec . defType = kWindowDefProcPtr;
			t_spec . u . defProc = s_window_mask_proc;
			
			CreateCustomWindow(&t_spec, wclass, wattributes, &wrect, (WindowPtr *)&window -> handle . window);
			HIWindowChangeFeatures((WindowPtr)window -> handle . window, 0, kWindowIsOpaque);
		}
		else if (((flags & F_DECORATIONS && !(decorations & testdecorations))
		          || wclass == kPlainWindowClass))
		{
			static WindowDefUPP s_borderless_proc = NULL;
			if (s_borderless_proc == NULL)
				s_borderless_proc = NewWindowDefUPP(BorderlessWindowProc);
				
			WindowDefSpec t_spec;
			t_spec . defType = kWindowDefProcPtr;
			t_spec . u . defProc = s_borderless_proc;

			if (wclass == kPlainWindowClass)
				wclass = kUtilityWindowClass;

			CreateCustomWindow(&t_spec, wclass, wattributes, &wrect, (WindowPtr *)&window->handle.window);
		}
		else
			CreateNewWindow(wclass, wattributes,&wrect, (WindowPtr *)&window->handle.window);

		if (wclass == kFloatingWindowClass)
			ChangeWindowAttributes((WindowPtr)window -> handle . window, kWindowNoAttributes, kWindowHideOnSuspendAttribute);
		
		// MW-2009-10-31: Make sure we can collapse any rev window
		HIWindowChangeFeatures((WindowPtr)window -> handle . window, kWindowCanCollapse, 0);
		
		if (window->handle.window == NULL)
			SetWTitle((WindowPtr)window->handle.window, namePascal);
		SetWTitle((WindowPtr)window->handle.window, namePascal);
		setopacity(blendlevel * 255 / 100);
		SetWRefCon((WindowPtr)window->handle.window, mode);
		
		ControlRef t_control;
		MCRevolutionStackViewCreate(this, &t_control);
		ControlRef t_root_control;
		GetRootControl((WindowPtr)window -> handle . window, &t_root_control);
		HIViewAddSubview(t_root_control, t_control);
		ShowControl(t_control);
		
		if (wclass == kDrawerWindowClass)
		{
			Window pwindow = NULL;
			if (parentwindow != DNULL)
				pwindow = parentwindow;
			else
				if (MCdefaultstackptr && MCdefaultstackptr->getw() != DNULL )
					pwindow = MCdefaultstackptr->getw();
			if (pwindow && GetWRefCon((WindowPtr)pwindow->handle.window) != WM_DRAWER)
			{
				SetDrawerParent((WindowPtr)window->handle.window, (WindowPtr)pwindow->handle.window);
				WindowAttributes watt;
				GetWindowAttributes((WindowPtr)pwindow->handle.window,&watt);
				if (wattributes & kWindowResizableAttribute)
					ChangeWindowAttributes((WindowPtr)pwindow->handle.window, kWindowLiveResizeAttribute, 0);
				OptionBits draweredge;
				switch (wposition)
				{
				case WP_PARENTTOP:
					draweredge = kWindowEdgeTop;
					break;
				case WP_PARENTRIGHT:
					draweredge = kWindowEdgeRight;
					break;
				case WP_PARENTBOTTOM:
					draweredge = kWindowEdgeBottom;
					break;
				case WP_PARENTLEFT:
					draweredge = kWindowEdgeLeft;
					break;
				default:
					draweredge =  kWindowEdgeDefault;
					break;
				}
				SetDrawerPreferredEdge((WindowPtr)window->handle.window, draweredge);
				if (walignment)
				{
					MCRectangle parentwindowrect;
					MCscreen->getwindowgeometry(pwindow, parentwindowrect);
					int2 wspace = 0;
					RgnHandle r = NewRgn();
					GetWindowRegion((WindowPtr)window->handle.window, kWindowStructureRgn, r);
					Rect tRect;
					GetRegionBounds(r, &tRect);
					DisposeRgn(r);
					MCRectangle drawerwindowrect;
					psdc->MacRect2MCRect(tRect, drawerwindowrect);
					if (wposition == WP_PARENTTOP || wposition == WP_PARENTBOTTOM)
					{
						wspace = parentwindowrect.width - drawerwindowrect.width;
						if (watt & kWindowMetalAttribute)
							if (wspace)
								wspace += 10; //for metal
					}
					else
					{
						wspace = parentwindowrect.height - drawerwindowrect.height;
						if (watt & kWindowMetalAttribute)
							if (wspace)
								wspace += 5; //for metal
					}
					if (wspace > 0)
						switch (walignment)
						{
						case OP_CENTER:
							SetDrawerOffsets ((WindowPtr)window->handle.window,ceil(wspace/2) -1,floor(wspace/2) + 1);
							break;
						case OP_RIGHT:
						case OP_BOTTOM:
							SetDrawerOffsets ((WindowPtr)window->handle.window,wspace,0);
							break;
						case OP_TOP:
						case OP_LEFT:
							SetDrawerOffsets ((WindowPtr)window->handle.window,0,wspace);
							break;
						}
				}
			}
		}
		delete tmpname;


		// MW-2005-11-06: We also need to catch window constraining events so we can flush
		//   the screen geometry cache.
		EventTypeSpec list[] =
		{
		
			{kEventClassWindow, kEventWindowCollapsed},
			{kEventClassWindow, kEventWindowExpanded},
			{kEventClassMouse, kEventMouseWheelMoved},
			{kEventClassWindow, kEventWindowBoundsChanging},
			{kEventClassWindow, kEventWindowBoundsChanged},
			{kEventClassWindow, kEventWindowConstrain},
			{kEventClassWindow, kEventWindowFocusAcquired},
			{kEventClassWindow, kEventWindowFocusRelinquish},
			{kEventClassWindow, kEventWindowActivated},
			{kEventClassWindow, kEventWindowDeactivated},
			{kEventClassWindow, kEventWindowClose},
		};

		EventHandlerRef ref;
		
		// MW-2005-09-07: Pass the window handle as user data, otherwise 'takewindow' causes problems
		InstallWindowEventHandler((WindowPtr)window->handle.window, MCS_weh, sizeof(list) / sizeof(EventTypeSpec), list, (WindowPtr)window -> handle . window, &ref);
		
		ChangeWindowAttributes((WindowPtr)window->handle.window, 0, kWindowHideOnFullScreenAttribute);
		
		updatemodifiedmark();
	}
	start_externals();
}