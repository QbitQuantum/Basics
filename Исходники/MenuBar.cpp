bool MenuBar::HotKey(dword key)
{
	if(Ctrl::HotKey(key))
		return true;
	if(IsChild()) {
		if((key == (K_ALT_KEY|K_KEYUP) || key == K_F10) && (submenu || HasFocusDeep())) {
			LLOG("CloseMenu()");
			CloseMenu();
			if(restorefocus)
				restorefocus->SetFocus();
			s_doaltkey = false;
			return true;
		}
		if(key == K_ALT_KEY) {
			LLOG("K_ALT_KEY");
			s_doaltkey = true;
			return true;
		}
		if((key == K_F10 || key == (K_ALT_KEY|K_KEYUP) && s_doaltkey)
		   && !submenu && !HasFocusDeep() && GetTopWindow() && GetTopWindow()->IsForeground()) {
			LLOG("Open menu by F10 or ALT-UP");
			SetupRestoreFocus();
			for(Ctrl *q = pane.GetFirstChild(); q; q = q->GetNext())
				if(q->SetFocus()) return true;
		}
	}
	LLOG("MenuBar::HotKey");
	return (key == K_LEFT || key == K_RIGHT) && parentmenu ? parentmenu->Key(key, 1) : false;
}