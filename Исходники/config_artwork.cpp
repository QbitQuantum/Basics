	BOOL CALLBACK on_message(HWND wnd,UINT msg,WPARAM wp,LPARAM lp)
	{

		switch(msg)
		{
		case WM_INITDIALOG:
			{
				HWND wnd_fields = m_source_list.create_in_dialog_units(wnd, ui_helpers::window_position_t(20,44,276,80));
				SetWindowPos(wnd_fields, HWND_TOP, 0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);

				refresh_me(wnd);

				ShowWindow(wnd_fields, SW_SHOWNORMAL);
			}
			break;
		case WM_DESTROY:
			{
				on_scripts_change();
			}
			break;
		case WM_COMMAND:
			switch(wp)
			{
#if 0
			case (EN_CHANGE<<16)|IDC_FRONT:
				artwork_panel::cfg_front = string_utf8_from_window((HWND)lp);
				m_changed = true;
				break;
			case (EN_CHANGE<<16)|IDC_BACK:
				artwork_panel::cfg_back = string_utf8_from_window((HWND)lp);
				m_changed = true;
				break;
			case (EN_CHANGE<<16)|IDC_DISC:
				artwork_panel::cfg_disc = string_utf8_from_window((HWND)lp);
				m_changed = true;
				break;
			case (EN_KILLFOCUS<<16)|IDC_FRONT:
			case (EN_KILLFOCUS<<16)|IDC_BACK:
			case (EN_KILLFOCUS<<16)|IDC_DISC:
				on_scripts_change();
				break;
#endif
			/*case (EN_CHANGE<<16)|IDC_ICON:
				artwork_panel::cfg_icon = string_utf8_from_window((HWND)lp);
				m_changed = true;
				break;*/
			case IDC_FB2KARTWORK|(CBN_SELCHANGE<<16):
				artwork_panel::cfg_fb2k_artwork_mode = ComboBox_GetCurSel((HWND)lp);
				break;
			case IDC_EDGESTYLE|(CBN_SELCHANGE<<16):
				artwork_panel::cfg_edge_style = ComboBox_GetCurSel((HWND)lp);
				artwork_panel::artwork_panel_t::g_on_edge_style_change();
				break;
			case IDC_ADD:
				{
					RECT rc;
					GetWindowRect((HWND)lp, &rc);
					HMENU menu = CreatePopupMenu();

					enum {IDM_FRONT = 1};

					t_size index, indexcount = tabsize(g_artwork_sources);
					for (index = 0; index < indexcount; index++)
					{
						AppendMenuW(menu,(MF_STRING),index+1,pfc::stringcvt::string_wide_from_utf8(g_artwork_sources[index].m_name));
					}
								
					int cmd = TrackPopupMenu(menu,TPM_LEFTBUTTON|TPM_NONOTIFY|TPM_RETURNCMD,rc.left,rc.bottom,0,wnd,0);
					DestroyMenu(menu);
					if (cmd>0 && (t_size)cmd <= indexcount)
					{
						index = cmd-1;
						t_size subindex = g_artwork_sources[index].m_scripts->add_item("<enter script>");

						t_size combined_index = get_combined_index(index, subindex);

						t_list_view::t_item_insert item;
						item.m_groups.add_item(g_artwork_sources[index].m_name);
						item.m_subitems.add_item("<enter script>");
						m_source_list.insert_items(combined_index, 1, &item);
						SetFocus(m_source_list.get_wnd());
						m_source_list.set_item_selected_single(combined_index);
						m_source_list.activate_inline_editing();
						m_source_list.m_changed = true;
					}
				}
				break;
			case IDC_REMOVE:
				{
					if (m_source_list.get_selection_count(2) == 1)
					{
						bit_array_bittable mask(m_source_list.get_item_count());
						m_source_list.get_selection_state(mask);
						//bool b_found = false;
						t_size combined_index=0, count=m_source_list.get_item_count();
						while (combined_index < count)
						{
							if (mask[combined_index]) break;
							combined_index++;
						}
						t_size index, subindex;
						if (combined_index < count && get_separated_index(combined_index, index, subindex))
						{
							g_artwork_sources[index].m_scripts->remove_by_idx(subindex);
							m_source_list.remove_item(combined_index);
							m_source_list.m_changed = true;
							t_size new_count = m_source_list.get_item_count();
							if (new_count)
							{
								if (combined_index < new_count)
									m_source_list.set_item_selected_single(combined_index);
								else if (combined_index)
									m_source_list.set_item_selected_single(combined_index-1);
							}
						}
					}
				}
				break;
			case IDC_UP:
				{
					if (m_source_list.get_selection_count(2) == 1)
					{
						t_size combined_index = 0;
						{
							t_size count = m_source_list.get_item_count();
							while (!m_source_list.get_item_selected(combined_index) && combined_index < count) combined_index++;
						}

						t_size index, subindex, combined_index_start, count;

						get_group_from_combined_index(combined_index, index, subindex, combined_index_start, count);

						if (subindex && count)
						{
							g_artwork_sources[index].m_scripts->swap_items(subindex, subindex-1);

							pfc::list_t<t_list_view::t_item_insert> items;
							items.set_count(2);

							items[0].m_groups.add_item(g_artwork_sources[index].m_name);
							items[1].m_groups.add_item(g_artwork_sources[index].m_name);
							items[0].m_subitems.add_item((*g_artwork_sources[index].m_scripts)[subindex-1]);
							items[1].m_subitems.add_item((*g_artwork_sources[index].m_scripts)[subindex]);
							m_source_list.replace_items(combined_index-1, items);
							m_source_list.set_item_selected_single(combined_index-1);
							m_source_list.m_changed = true;
						}
					}
				}
				break;
			case IDC_DOWN:
				{
					if (m_source_list.get_selection_count(2) == 1)
					{
						t_size combined_index = 0;
						{
							t_size count = m_source_list.get_item_count();
							while (!m_source_list.get_item_selected(combined_index) && combined_index < count) combined_index++;
						}

						t_size index, subindex, combined_index_start, count;

						get_group_from_combined_index(combined_index, index, subindex, combined_index_start, count);

						if (subindex + 1 < count)
						{
							g_artwork_sources[index].m_scripts->swap_items(subindex, subindex+1);
							pfc::list_t<t_list_view::t_item_insert> items;
							items.set_count(2);

							items[0].m_groups.add_item(g_artwork_sources[index].m_name);
							items[1].m_groups.add_item(g_artwork_sources[index].m_name);
							items[0].m_subitems.add_item((*g_artwork_sources[index].m_scripts)[subindex]);
							items[1].m_subitems.add_item((*g_artwork_sources[index].m_scripts)[subindex+1]);

							m_source_list.replace_items(combined_index, items);
							m_source_list.set_item_selected_single(combined_index+1);
							m_source_list.m_changed = true;
						}
					}
				}
				break;
			}
		}
		return 0;
	}