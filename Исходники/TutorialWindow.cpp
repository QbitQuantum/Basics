void CTutorialWindow::OnLButtonDown(UINT nFlags, CPoint point) {
	// Get currently playing track.
	static_api_ptr_t<play_control> pc;
	metadb_handle_ptr handle;

	// If some track is playing...
	if (pc->get_now_playing(handle)) {
		POINT pt;
		GetCursorPos(&pt);

		// ...detect a drag operation.
		if (DragDetect(m_hWnd, pt)) {
			metadb_handle_list items;
			items.add_item(handle);

			// Create an IDataObject that contains the dragged track.
			static_api_ptr_t<playlist_incoming_item_filter> piif;
			// create_dataobject_ex() returns a smart pointer unlike create_dataobject()
			// which returns a raw COM pointer. The less chance we have to accidentally
			// get the reference counting wrong, the better.
			pfc::com_ptr_t<IDataObject> pDataObject = piif->create_dataobject_ex(items);

			// Create an IDropSource.
			// The constructor of IDropSource_tutorial1 is hidden by design; we use the
			// provided factory method which returns a smart pointer.
			pfc::com_ptr_t<IDropSource> pDropSource = IDropSource_tutorial1::g_create(m_hWnd);

			DWORD effect;
			// Perform drag&drop operation.
			DoDragDrop(pDataObject.get_ptr(), pDropSource.get_ptr(), DROPEFFECT_COPY, &effect);
		}
	}
}