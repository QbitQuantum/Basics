HRESULT STDMETHODCALLTYPE playlists_tabs_extension::playlists_tabs_drop_target::Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL ptl, DWORD *pdwEffect)
{
	POINT pt = { ptl.x, ptl.y };
	bool isAltDown = (grfKeyState & MK_ALT) != 0;
	if (m_DropTargetHelper.is_valid()) m_DropTargetHelper->Drop(pDataObj, &pt, *pdwEffect);

	p_list->kill_switch_timer();
	m_DataObject.release();
	last_over.x = 0;
	last_over.y = 0;

	if (!m_is_accepted_type)
	{
		mmh::ole::SetDropDescription(m_DataObject.get_ptr(), DROPIMAGE_INVALID, "", "");
		return S_OK;
	}

	static_api_ptr_t<playlist_manager> playlist_api;

	POINT pti, ptm;
	pti.y = pt.y;
	pti.x = pt.x;

	ptm = pti;
	ScreenToClient(p_list->get_wnd(), &ptm);

	HWND wnd = ChildWindowFromPointEx(p_list->get_wnd(), ptm, CWP_SKIPINVISIBLE);

	if (wnd)
	{

		bool process = !ui_drop_item_callback::g_on_drop(pDataObj);

		bool send_new_playlist = false;

		if (process && m_last_rmb)
		{
			process = false;
			enum { ID_DROP = 1, ID_NEW_PLAYLIST, ID_CANCEL };

			HMENU menu = CreatePopupMenu();

			uAppendMenu(menu, (MF_STRING), ID_DROP, "&Add files here");
			uAppendMenu(menu, (MF_STRING), ID_NEW_PLAYLIST, "&Add files to new playlist");
			uAppendMenu(menu, MF_SEPARATOR, 0, 0);
			uAppendMenu(menu, MF_STRING, ID_CANCEL, "&Cancel");

			int cmd = TrackPopupMenu(menu, TPM_RIGHTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD, pt.x, pt.y, 0, p_list->get_wnd(), 0);
			DestroyMenu(menu);

			if (cmd)
			{
				switch (cmd)
				{
				case ID_DROP:
					process = true;
					break;
				case ID_NEW_PLAYLIST:
					process = true;
					send_new_playlist = true;
					break;
				}
			}
		}

		if (process)
		{
			metadb_handle_list data;
			static_api_ptr_t<playlist_incoming_item_filter> incoming_api;
			incoming_api->process_dropped_files(pDataObj, data, true, p_list->get_wnd());

			POINT pttab, ptpl;
			pttab = pti;
			ptpl = pti;


			int idx = -1;
			t_size newPlaylistIndex = pfc_infinite;
			//	if ((g_tab && wnd == g_tab) || g_plist && wnd == g_plist)


			//	bool processed = false;
			t_size target_index = playlist_api->get_active_playlist();


			if (p_list->wnd_tabs && wnd == p_list->wnd_tabs)
			{
				RECT tabs;

				GetWindowRect(p_list->wnd_tabs, &tabs);
				if (ScreenToClient(p_list->wnd_tabs, &pttab))
				{
					TCHITTESTINFO hittest;
					hittest.pt.x = pttab.x;
					hittest.pt.y = pttab.y;
					int idx = TabCtrl_HitTest(p_list->wnd_tabs, &hittest);
					int old = playlist_api->get_active_playlist();
					if (send_new_playlist || idx < 0 || isAltDown)
					{
						send_new_playlist = true;
						if (idx >= 0)
							newPlaylistIndex = idx;
					}
					else target_index = idx;
				}

			}


			if (send_new_playlist)
			{
				pfc::string8 playlist_name("Untitled");

				bool named = false;

				if (1 || 1)
				{
					FORMATETC   fe;
					STGMEDIUM   sm;
					HRESULT     hr = E_FAIL;

					//					memset(&sm, 0, sizeof(0));

					fe.cfFormat = CF_HDROP;
					fe.ptd = NULL;
					fe.dwAspect = DVASPECT_CONTENT;
					fe.lindex = -1;
					fe.tymed = TYMED_HGLOBAL;

					// User has dropped on us. Get the data from drag source
					hr = pDataObj->GetData(&fe, &sm);
					if (SUCCEEDED(hr))
					{

						// Display the data and release it.
						pfc::string8 temp;

						unsigned int /*n,*/t = uDragQueryFileCount((HDROP)sm.hGlobal);
						if (t == 1)
						{
							{
								uDragQueryFile((HDROP)sm.hGlobal, 0, temp);
								if (uGetFileAttributes(temp) & FILE_ATTRIBUTE_DIRECTORY)
								{
									playlist_name.set_string(pfc::string_filename_ext(temp));
									named = true;
								}
								else
								{
									playlist_name.set_string(pfc::string_filename(temp));
									named = true;
#if 0
									pfc::string_extension ext(temp);

									service_enum_t<playlist_loader> e;
									service_ptr_t<playlist_loader> l;
									if (e.first(l))
										do
										{
											if (!strcmp(l->get_extension(), ext))
											{
												playlist_name.set_string(pfc::string_filename(temp));
												named = true;
												l.release();
												break;
											}
											l.release();
										} while (e.next(l));
#endif
								}

							}
						}

						ReleaseStgMedium(&sm);
					}
				}

				unsigned new_idx;
				if (newPlaylistIndex == pfc_infinite)
					newPlaylistIndex = playlist_api->get_playlist_count();

				if (named && cfg_replace_drop_underscores) playlist_name.replace_char('_', ' ', 0);
				if (!named && cfg_pgen_tf) new_idx = playlist_api->create_playlist(string_pn(data, cfg_pgenstring), pfc_infinite, newPlaylistIndex);

				else  new_idx = playlist_api->create_playlist(playlist_name, pfc_infinite, newPlaylistIndex);

				playlist_api->playlist_add_items(new_idx, data, bit_array_false());
				if (main_window::config_get_activate_target_playlist_on_dropped_items())
					playlist_api->set_active_playlist(new_idx);

			}
			else
			{
				playlist_api->playlist_clear_selection(target_index);
				playlist_api->playlist_insert_items(target_index, idx, data, bit_array_true());
				if (main_window::config_get_activate_target_playlist_on_dropped_items())
					playlist_api->set_active_playlist(target_index);
			}

			data.remove_all();
		}
	}

	return S_OK;
}