	void playlist_switcher_t::notify_on_destroy()
	{
		m_selection_holder.release();

		g_windows.remove_item(this);

		RevokeDragDrop(get_wnd());

		standard_api_create_t<play_callback_manager>()->unregister_callback(this);
		m_playlist_api->unregister_callback(this);
		m_playlist_api.release();
		m_playback_api.release();
	}