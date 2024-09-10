HWND container_window::create_in_dialog_units(HWND wnd_dialog, const ui_helpers::window_position_t & p_window_position, LPVOID create_param)
{
	RECT rc;
	p_window_position.convert_to_rect(rc);
	MapDialogRect(wnd_dialog, &rc);
	return create(wnd_dialog, create_param, ui_helpers::window_position_t(rc));
}