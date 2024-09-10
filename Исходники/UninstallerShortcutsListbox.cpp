void UninstallerShortcutsListbox::connect(HWND hwndParent, HWND hwndListbox)
{
	if (m_listbox == 0)
	{
		m_dialogbox = hwndParent;
		m_listbox = hwndListbox;
		m_tooltip.init(hwndParent, hwndListbox);
		SetWindowSubclass(hwndListbox, listboxSubclassProc, 0, (DWORD_PTR) this);
		SetWindowSubclass(hwndListbox,
			GdiUtils::subclassProcForListboxWithEmptyText,
			0, (DWORD_PTR) m_emptyText);
		RegisterDragDrop(hwndListbox, this);
		try {
			append(ShortcutsDisconnector::findShortcuts());
		}
		catch (AutoSaveException& exc) {
			m_lastException = exc;
			PostMessage(m_dialogbox, LB_EXCEPTIONTHROWN, 0, 0);
		}
	}
}