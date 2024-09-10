consolewin_info::consolewin_info(debugger_windows_interface &debugger) :
	disasmbasewin_info(debugger, true, "Debug", NULL),
	m_devices_menu(NULL)
{
	if ((window() == NULL) || (m_views[0] == NULL))
		goto cleanup;

	// create the views
	m_views[1].reset(global_alloc(debugview_info(debugger, *this, window(), DVT_STATE)));
	if (!m_views[1]->is_valid())
		goto cleanup;
	m_views[2].reset(global_alloc(debugview_info(debugger, *this, window(), DVT_CONSOLE)));
	if (!m_views[2]->is_valid())
		goto cleanup;

	{
		// Add image menu only if image devices exist
		image_interface_iterator iter(machine().root_device());
		device_image_interface *img = iter.first();
		if (img != NULL)
		{
			m_devices_menu = CreatePopupMenu();
			for ( ; img != NULL; img = iter.next())
			{
				astring temp;
				temp.format("%s : %s", img->device().name(), img->exists() ? img->filename() : "[no image]");
				TCHAR *tc_buf = tstring_from_utf8(temp.c_str());
				if (tc_buf != NULL)
				{
					AppendMenu(m_devices_menu, MF_ENABLED, 0, tc_buf);
					osd_free(tc_buf);
				}
			}
			AppendMenu(GetMenu(window()), MF_ENABLED | MF_POPUP, (UINT_PTR)m_devices_menu, TEXT("Images"));
		}

		// get the work bounds
		RECT work_bounds, bounds;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &work_bounds, 0);

		// adjust the min/max sizes for the window style
		bounds.top = bounds.left = 0;
		bounds.right = bounds.bottom = EDGE_WIDTH + m_views[1]->maxwidth() + (2 * EDGE_WIDTH) + 100 + EDGE_WIDTH;
		AdjustWindowRectEx(&bounds, DEBUG_WINDOW_STYLE, FALSE, DEBUG_WINDOW_STYLE_EX);
		set_minwidth(bounds.right - bounds.left);

		bounds.top = bounds.left = 0;
		bounds.right = bounds.bottom = EDGE_WIDTH + m_views[1]->maxwidth() + (2 * EDGE_WIDTH) + MAX(m_views[0]->maxwidth(), m_views[2]->maxwidth()) + EDGE_WIDTH;
		AdjustWindowRectEx(&bounds, DEBUG_WINDOW_STYLE, FALSE, DEBUG_WINDOW_STYLE_EX);
		set_maxwidth(bounds.right - bounds.left);

		// position the window at the bottom-right
		int const bestwidth = MIN(maxwidth(), work_bounds.right - work_bounds.left);
		int const bestheight = MIN(500, work_bounds.bottom - work_bounds.top);
		SetWindowPos(window(), HWND_TOP,
					work_bounds.right - bestwidth, work_bounds.bottom - bestheight,
					bestwidth, bestheight,
					SWP_SHOWWINDOW);
	}

	// recompute the children
	set_cpu(*debug_cpu_get_visible_cpu(machine()));

	// mark the edit box as the default focus and set it
	set_default_focus();
	return;

cleanup:
	m_views[2].reset();
	m_views[1].reset();
	m_views[0].reset();
}