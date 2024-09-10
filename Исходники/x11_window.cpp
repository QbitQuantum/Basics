	void X11Window::process_window_resize(const Rect &new_rect)
	{
		Rect old_client_area = client_area;
		client_area = new_rect;

		if (site)
		{
			if (old_client_area.left != client_area.left || old_client_area.top != client_area.top)
			{
				(site->sig_window_moved)();
			}

			if (old_client_area.get_width() != client_area.get_width() || old_client_area.get_height() != client_area.get_height())
			{
				Rectf rectf = client_area;
				rectf.left   /= pixel_ratio;
				rectf.top    /= pixel_ratio;
				rectf.right  /= pixel_ratio;
				rectf.bottom /= pixel_ratio;

				if (callback_on_resized)
					callback_on_resized(); // OpenGLWindowProvider::on_window_resized

				(site->sig_resize)(rectf.get_width(), rectf.get_height()); // TopLevelWindow_Impl::on_resize

				if (site->func_window_resize)
					(site->func_window_resize)(rectf);
			}
		}
	}