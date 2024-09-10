void CtrlBreakpointList::showBreakpointMenu(int itemIndex, const POINT &pt)
{
	POINT screenPt(pt);
	ClientToScreen(wnd, &screenPt);

	bool isMemory;
	int index = getBreakpointIndex(itemIndex, isMemory);
	if (index == -1)
	{
		HMENU subMenu = GetSubMenu(g_hPopupMenus, POPUP_SUBMENU_ID_NEWBREAKPOINT);
		
		switch (TrackPopupMenuEx(subMenu, TPM_RIGHTBUTTON | TPM_RETURNCMD, screenPt.x, screenPt.y, wnd, 0))
		{
		case ID_DISASM_ADDNEWBREAKPOINT:
			{		
				BreakpointWindow bpw(wnd,cpu);
				if (bpw.exec()) bpw.addBreakpoint();
			}
			break;
		}
	} else {
		MemCheck mcPrev;
		BreakPoint bpPrev;
		if (isMemory) {
			mcPrev = displayedMemChecks_[index];
		} else {
			bpPrev = displayedBreakPoints_[index];
		}

		HMENU subMenu = GetSubMenu(g_hPopupMenus, POPUP_SUBMENU_ID_BREAKPOINTLIST);
		if (isMemory) {
			CheckMenuItem(subMenu, ID_DISASM_DISABLEBREAKPOINT, MF_BYCOMMAND | (mcPrev.result & MEMCHECK_BREAK ? MF_CHECKED : MF_UNCHECKED));
		} else {
			CheckMenuItem(subMenu, ID_DISASM_DISABLEBREAKPOINT, MF_BYCOMMAND | (bpPrev.enabled ? MF_CHECKED : MF_UNCHECKED));
		}

		switch (TrackPopupMenuEx(subMenu, TPM_RIGHTBUTTON | TPM_RETURNCMD, screenPt.x, screenPt.y, wnd, 0))
		{
		case ID_DISASM_DISABLEBREAKPOINT:
			if (isMemory) {
				CBreakPoints::ChangeMemCheck(mcPrev.start, mcPrev.end, mcPrev.cond, MemCheckResult(mcPrev.result ^ MEMCHECK_BREAK));
			} else {
				CBreakPoints::ChangeBreakPoint(bpPrev.addr, !bpPrev.enabled);
			}
			break;
		case ID_DISASM_EDITBREAKPOINT:
			editBreakpoint(index);
			break;
		case ID_DISASM_ADDNEWBREAKPOINT:
			{		
				BreakpointWindow bpw(wnd,cpu);
				if (bpw.exec()) bpw.addBreakpoint();
			}
			break;
		}
	}
}