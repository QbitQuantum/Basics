consolewin_info::consolewin_info(debugger_windows_interface &debugger) :
	disasmbasewin_info(debugger, true, "Debug", nullptr),
	m_devices_menu(nullptr)
{
	if ((window() == nullptr) || (m_views[0] == nullptr))
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
		if (iter.first() != nullptr)
		{
			m_devices_menu = CreatePopupMenu();
			for (device_image_interface &img : iter)
			{
				osd::text::tstring tc_buf = osd::text::to_tstring(string_format("%s : %s", img.device().name(), img.exists() ? img.filename() : "[no image]"));
				AppendMenu(m_devices_menu, MF_ENABLED, 0, tc_buf.c_str());
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
		bounds.right = bounds.bottom = EDGE_WIDTH + m_views[1]->maxwidth() + (2 * EDGE_WIDTH) + std::max(m_views[0]->maxwidth(), m_views[2]->maxwidth()) + EDGE_WIDTH;
		AdjustWindowRectEx(&bounds, DEBUG_WINDOW_STYLE, FALSE, DEBUG_WINDOW_STYLE_EX);
		set_maxwidth(bounds.right - bounds.left);

		// position the window at the bottom-right
		int const bestwidth = (std::min<uint32_t>)(maxwidth(), work_bounds.right - work_bounds.left);
		int const bestheight = (std::min<uint32_t>)(500, work_bounds.bottom - work_bounds.top);
		SetWindowPos(window(), HWND_TOP,
					work_bounds.right - bestwidth, work_bounds.bottom - bestheight,
					bestwidth, bestheight,
					SWP_SHOWWINDOW);
	}

	// recompute the children
	set_cpu(*machine().debugger().cpu().get_visible_cpu());

	// mark the edit box as the default focus and set it
	editwin_info::set_default_focus();
	return;

cleanup:
	m_views[2].reset();
	m_views[1].reset();
	m_views[0].reset();
}