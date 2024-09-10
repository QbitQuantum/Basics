static void Docking_PosCommand(HWND hwnd, LPRECT rc, bool query)
{
	APPBARDATA abd = {0};

	abd.cbSize = sizeof(abd);
	abd.hWnd = hwnd;
	abd.uEdge = docked == DOCKED_LEFT ? ABE_LEFT : ABE_RIGHT;
	abd.rc = *rc;
	SHAppBarMessage(query ? ABM_QUERYPOS : ABM_SETPOS, &abd);
	*rc = abd.rc;
}