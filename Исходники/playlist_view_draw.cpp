bool playlist_view::draw_items(HDC dc, int start_item, int count)
{
	//	profiler(draw_items);

	if (!drawing_enabled) return false;

	static_api_ptr_t<playlist_manager> playlist_api;

	HDC hdc_mem = 0;
	RECT rect, item, item_area, bk, draw/*,text*/;
	GetClientRect(wnd_playlist, &rect);
	rect.top += get_header_height();

	int item_height = get_item_height();

	HBRUSH br = 0;
	HBITMAP hbm_mem = 0, hbm_old = 0;

	pfc::array_t<int, pfc::alloc_fast_aggressive> widths;
	int total_width = get_column_widths(widths);
	int t = columns.get_count();

	const bit_array & p_mask = g_cache.active_get_columns_mask();

	item_area.left = rect.left;
	item_area.right = rect.right;
	item_area.top = rect.top + (item_height*start_item);
	item_area.bottom = item_area.top + (item_height*count);

	item.left = 0 - horizontal_offset;
	item.right = item.left + total_width;
	item.top = 0;
	item.bottom = item.top + item_height;

	bk.top = 0;
	bk.left = 0;
	bk.bottom = item_height*count;
	bk.right = rect.right - rect.left;

	/*static */pfc::string8_fast_aggressive temp;
	temp.prealloc(512);

	/* edit01 */

	hdc_mem = CreateCompatibleDC(dc);

	COLORREF colourfore = 0xff;

	hbm_mem = CreateCompatibleBitmap(dc, rect.right - rect.left, item_height*count);

	hbm_old = (HBITMAP)SelectObject(hdc_mem, hbm_mem);

	HGDIOBJ font_old = SelectObject(hdc_mem, g_font);

	cui::colours::helper p_helper(appearance_client_pv_impl::g_guid);

	//fill entire area with back colour
	br = CreateSolidBrush(p_helper.get_colour(cui::colours::colour_background));
	FillRect(hdc_mem, &bk, br);
	DeleteObject(br);

	//need checks here because of filling background

	{
		int total = playlist_api->activeplaylist_get_item_count();

		if (start_item + count + scroll_item_offset > total) //end item is NOT inclusive
		{
			count -= (start_item + count + scroll_item_offset) - total;
		}

	}

	int end_item = start_item + count;



	//draw each item

	int n,
		focus = playlist_api->activeplaylist_get_focus_item();

	//	static int pcount;



	t_size playing_index, playing_playlist;
	playlist_api->get_playing_item_location(&playing_playlist, &playing_index);
	bool b_playback = static_api_ptr_t<play_control>()->is_playing();
	if (g_cache.get_active_playlist() != playing_playlist) playing_index = pfc_infinite;
	for (n = start_item; n < end_item; n++)
	{
		bool sel = playlist_api->activeplaylist_is_item_selected(n + scroll_item_offset);
		bool b_focused = GetFocus() == wnd_playlist || IsChild(wnd_playlist, GetFocus());
		bool b_playing = b_playback && playing_index == (n + scroll_item_offset);
		//draw each column of each item
		int theme_state = NULL;
		if (sel)
			theme_state = (b_playing ? LISS_HOTSELECTED : (b_focused ? LISS_SELECTED : LISS_SELECTEDNOTFOCUS));
		else if (b_playing) theme_state = LISS_HOT;
		bool b_themed = m_theme && p_helper.get_themed() && IsThemePartDefined(m_theme, LVP_LISTITEM, theme_state);
		if (b_themed && theme_state)
		{
			if (IsThemeBackgroundPartiallyTransparent(m_theme, LVP_LISTITEM, theme_state))
				DrawThemeParentBackground(get_wnd(), hdc_mem, &item);
			DrawThemeBackground(m_theme, hdc_mem, LVP_LISTITEM, theme_state, &item, NULL);
		}

		//int total = playlist_api->activeplaylist_get_item_count();
		int c, offset = 0, i = 0;
		for (c = 0; c < t; c++)
		{
			if (p_mask[c])
			{

				draw.left = item.left + offset;
				draw.top = item.top;

				offset += widths[i];

				draw.right = item.left + offset;
				draw.bottom = item.bottom;

				{
					//					profiler_debug(draw_item_get_string);
					g_cache.active_get_display_name(n + scroll_item_offset, i, temp);
				}

				colourinfo colours(0x000000, 0x000000, 0xFF, 0xFF, 0, 0xFF);
				g_cache.active_get_colour(n + scroll_item_offset, i, colours);

				if (b_themed)
				{
					//COLORREF cr_back= get_default_colour(colours::COLOUR_BACK);
					//colourfore = get_default_colour(colours::COLOUR_TEXT);
					//GetThemeColor(m_theme, LVP_LISTITEM, sel ? (GetFocus() == wnd_playlist ? LIS_SELECTED : LIS_SELECTEDNOTFOCUS) : LIS_NORMAL, TMT_WINDOWTEXT, &colourfore);
					colourfore = GetThemeSysColor(m_theme, sel ? COLOR_BTNTEXT : COLOR_WINDOWTEXT);
					//GetThemeColor(m_theme, LVP_LISTITEM, sel ? (GetFocus() == wnd_playlist ? LIS_SELECTED : LIS_SELECTEDNOTFOCUS) : LIS_NORMAL, TMT_TEXTCOLOR, &colourfore);
					if (!theme_state)
					{
						//GetThemeColor(m_theme, LVP_LISTITEM, LIS_NORMAL, TMT_FILLCOLOR, &colourfore);
						br = CreateSolidBrush(colours.background_colour);
						FillRect(hdc_mem, &draw, br);
					}
				}
				else
				{
					if (sel)
					{
						/* TEST */

						if (GetFocus() == wnd_playlist)
						{
							colourfore = colours.selected_text_colour;
							br = CreateSolidBrush(colours.selected_background_colour);
						}
						else
						{
							colourfore = colours.selected_text_colour_non_focus;
							br = CreateSolidBrush(colours.selected_background_colour_non_focus);
						}
					}
					else
					{
						colourfore = colours.text_colour;
						br = CreateSolidBrush(colours.background_colour);
					}
					//draw cell background
					//if (!b_themed)
					FillRect(hdc_mem, &draw, br);
				}


				if (br) { DeleteObject(br); br = 0; }

				//render text
				//if (b_themed)
				//	DrawThemeText(m_theme, hdc_mem, LVP_LISTITEM, sel ? (GetFocus() == wnd_playlist ? LIS_SELECTED : LIS_SELECTEDNOTFOCUS) : LIS_NORMAL, L"test", 4, 0, 0, &draw);
				//else
				ui_helpers::text_out_colours_tab(hdc_mem, temp, temp.length(), 2, 1, &draw, sel, colourfore, TRUE, true, (cfg_ellipsis != 0), (ui_helpers::alignment)columns[c]->align);


				if (colours.use_frame_left)
				{
					HPEN pen = CreatePen(PS_SOLID, 1, colours.frame_left);
					HPEN pen_old = (HPEN)SelectObject(hdc_mem, pen);

					MoveToEx(hdc_mem, draw.left, draw.top, 0);
					LineTo(hdc_mem, draw.left, draw.bottom);
					SelectObject(hdc_mem, pen_old);
					DeleteObject(pen);
				}
				if (colours.use_frame_top)
				{
					HPEN pen = CreatePen(PS_SOLID, 1, colours.frame_top);
					HPEN pen_old = (HPEN)SelectObject(hdc_mem, pen);

					MoveToEx(hdc_mem, draw.left, draw.top, 0);
					LineTo(hdc_mem, draw.right, draw.top);
					SelectObject(hdc_mem, pen_old);
					DeleteObject(pen);
				}
				if (colours.use_frame_right)
				{
					HPEN pen = CreatePen(PS_SOLID, 1, colours.frame_right);
					HPEN pen_old = (HPEN)SelectObject(hdc_mem, pen);

					MoveToEx(hdc_mem, draw.right - 1, draw.top, 0);
					LineTo(hdc_mem, draw.right - 1, draw.bottom);
					SelectObject(hdc_mem, pen_old);
					DeleteObject(pen);
				}
				if (colours.use_frame_bottom)
				{
					HPEN pen = CreatePen(PS_SOLID, 1, colours.frame_bottom);
					HPEN pen_old = (HPEN)SelectObject(hdc_mem, pen);

					MoveToEx(hdc_mem, draw.right - 1, draw.bottom - 1, 0);
					LineTo(hdc_mem, draw.left - 1, draw.bottom - 1);
					SelectObject(hdc_mem, pen_old);
					DeleteObject(pen);
				}
				i++;
			}
		}



		//draw focus frame
		if ((n + scroll_item_offset) == focus)
		{
			if (m_always_show_focus || (!(SendMessage(get_wnd(), WM_QUERYUISTATE, NULL, NULL) & UISF_HIDEFOCUS) && b_focused))
			{
				RECT rc_focus = item;
				if (m_theme && p_helper.get_themed() && IsThemePartDefined(m_theme, LVP_LISTITEM, LISS_SELECTED))
					InflateRect(&rc_focus, -1, -1);
				if (!p_helper.get_bool(cui::colours::bool_use_custom_active_item_frame))
				{
					DrawFocusRect(hdc_mem, &rc_focus);
				}
				else
				{
					br = CreateSolidBrush(p_helper.get_colour(cui::colours::colour_active_item_frame));
					FrameRect(hdc_mem, &rc_focus, br);
					DeleteObject(br);
				}
			}
		}

		item.top += item_height;
		item.bottom += item_height;
	}


	BitBlt(dc, item_area.left, item_area.top, item_area.right - item_area.left, item_area.bottom - item_area.top,
		hdc_mem, 0, 0, SRCCOPY);

	if (font_old) SelectObject(hdc_mem, font_old);
	SelectObject(hdc_mem, hbm_old);
	DeleteObject(hbm_mem);
	DeleteDC(hdc_mem);

	return true;
}