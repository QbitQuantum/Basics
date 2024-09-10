	bool ng_playlist_view_t::do_drag_drop(WPARAM wp)
	{
		metadb_handle_list_t<pfc::alloc_fast_aggressive> data;
		m_playlist_api->activeplaylist_get_selected_items(data);
		if (data.get_count() > 0)
		{
			static_api_ptr_t<playlist_incoming_item_filter> incoming_api;
			IDataObject * pDataObject = incoming_api->create_dataobject(data);
			if (pDataObject)
			{
				//IDataObject * pDataObjectFixed = new CDataObject;
#if 0
				mmh::comptr_t<IEnumFORMATETC> pEnumFORMATETC;
				pDataObject->EnumFormatEtc(DATADIR_GET, pEnumFORMATETC.get_pp());

				FORMATETC fe;
				memset(&fe,0,sizeof(fe));
				while (S_OK == pEnumFORMATETC->Next(1, &fe, NULL))
				{
					STGMEDIUM stgm;
					memset(&stgm, 0, sizeof(0));
					if (SUCCEEDED(pDataObject->GetData(&fe, &stgm)))
					{
						//if (stgm.tymed != TYMED_ISTREAM)
						//	pDataObjectFixed->SetData(&fe, &stgm, FALSE);
						ReleaseStgMedium(&stgm);
					}
					memset(&fe,0,sizeof(fe));
				}

				pEnumFORMATETC.release();
#endif
				//pfc::com_ptr_t<IAsyncOperation> pAsyncOperation;
				//HRESULT hr = pDataObject->QueryInterface(IID_IAsyncOperation, (void**)pAsyncOperation.receive_ptr());
				DWORD blah = DROPEFFECT_NONE;
				{
					m_dragging = true;
					m_DataObject = pDataObject;
					m_dragging_initial_playlist = m_playlist_api->get_active_playlist();
					pfc::com_ptr_t<mmh::ole::IDropSource_Generic> p_IDropSource_playlist = new mmh::ole::IDropSource_Generic(get_wnd(), pDataObject, wp);
					HRESULT hr = DoDragDrop(pDataObject,p_IDropSource_playlist.get_ptr(),DROPEFFECT_COPY|DROPEFFECT_MOVE,&blah);
						//SHDoDragDrop(get_wnd(), pDataObject,NULL,DROPEFFECT_COPY|DROPEFFECT_MOVE,&blah);

					m_dragging=false;
					m_DataObject.release();
					m_dragging_initial_playlist = pfc_infinite;

					/*if (DRAGDROP_S_DROP == hr && blah == DROPEFFECT_MOVE)
					m_playlist_api->playlist_remove_selection(playlist);*/
				}
				//pDataObjectFixed->Release();
				pDataObject->Release();
			}
		}
		return true;
	}