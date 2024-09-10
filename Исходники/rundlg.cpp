LRESULT CRunDlg::OnContextMenu(UINT , WPARAM , LPARAM lp, BOOL &)
{
	cfg::config *c = cfg::config::instance();
	CMenu menu;
	menu.LoadMenuW(IDR_MENU_POPUP);
	CMenu mu = (HMENU)menu.GetSubMenu(0);

	POINT pt = {-1, -1};
	if (lp == 0xFFFFFFFF) // 菜单不是右键激活的而是按键激活的
	{
		hlp::track_mouse_event(TME_CANCEL|TME_LEAVE, m_hWnd);
		if (m_curr_prog_pos != pp_null)
		{
			lyt::icon_layout *il = dynamic_cast<lyt::icon_layout *>(m_lyt);
			if (il != NULL)
			{
				RECT rc = il->get_prog_rect(m_curr_prog_pos);
				m_menu_point.x = (rc.left + rc.right) / 2;
				m_menu_point.y = (rc.top + rc.bottom) / 2;
				pt = m_menu_point;
				ClientToScreen(&pt);
			}
		}
	}
	if (pt.x == -1)
	{
		::GetCursorPos(&pt);
		m_menu_point = pt;
		ScreenToClient(&m_menu_point);
	}

	if (c->gm.layout != cfg::ul_group)
	{
		mu.DeleteMenu(ID_INSERT_GROUP, MF_BYCOMMAND);
		mu.DeleteMenu(ID_EDIT_GROUP, MF_BYCOMMAND);
		mu.DeleteMenu(ID_DEL_GROUP, MF_BYCOMMAND);
	}
	if (c->gm.layout == cfg::ul_simple)
	{
		mu.DeleteMenu(ID_INSERT_PROG, MF_BYCOMMAND);
		mu.DeleteMenu(ID_EDIT_PROG, MF_BYCOMMAND);
		mu.DeleteMenu(ID_DEL_PROG, MF_BYCOMMAND);
	}

	if (m_lyt->get_insert_pos(m_menu_point) == pp_null)
	{
		mu.EnableMenuItem(ID_INSERT_PROG, MF_BYCOMMAND | MF_GRAYED);
//		mu.EnableMenuItem(ID_INSERT_GROUP, MF_BYCOMMAND | MF_GRAYED);
		mu.EnableMenuItem(ID_EDIT_GROUP, MF_BYCOMMAND | MF_GRAYED);
		mu.EnableMenuItem(ID_DEL_GROUP, MF_BYCOMMAND | MF_GRAYED);
	}
	if (m_lyt->get_prog_from_point(m_menu_point) == pp_null)
	{
		mu.EnableMenuItem(ID_EDIT_PROG, MF_BYCOMMAND | MF_GRAYED);
		mu.EnableMenuItem(ID_DEL_PROG, MF_BYCOMMAND | MF_GRAYED);
	}
	// 显示样式前面的对勾
	UINT lyt_id;
	switch (c->gm.layout)
	{
	case cfg::ul_simple: lyt_id = ID_CHLYT_SIMPLE; break;
	case cfg::ul_plain:  lyt_id = ID_CHLYT_PLAIN; break;
	default:             lyt_id = ID_CHLYT_GROUP; break;
	}
	mu.CheckMenuItem(lyt_id, MF_BYCOMMAND|MF_CHECKED);
	UINT style_id;
	switch (c->gm.style)
	{
	case cfg::ws_edge:  style_id = ID_CHSTYLE_EDGE; break;
	default:            style_id = ID_CHSTYLE_CENTER; break;
	}
	mu.CheckMenuItem(style_id, MF_BYCOMMAND|MF_CHECKED);

	// 删除多余的分隔线
	for (int i = mu.GetMenuItemCount() - 1; i > 0; i--)
	{
		if (mu.GetMenuStringLen(i,   MF_BYPOSITION) == 0 &&
			mu.GetMenuStringLen(i-1, MF_BYPOSITION) == 0)
		{
			mu.DeleteMenu(i, MF_BYPOSITION);
		}
	}

	KillTimer(IDT_AUTO_FOLD); // 菜单消失前不能让窗口自动隐藏
	mu.TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, m_hWnd);
	change_op_state(os_hover);
	return TRUE;
}