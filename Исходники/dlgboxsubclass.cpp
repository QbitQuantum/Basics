// ChildWindowFromPoint() messes up with group boxes
static BOOL CALLBACK FindChildAtPointEnumProc(HWND hwnd, LPARAM lParam)
{
	if (IsWindowVisible(hwnd)) {
		struct FindChildAtPointData *fcap = (struct FindChildAtPointData*)lParam;
		RECT rcVisible, rc, rcParent;
		GetWindowRect(hwnd, &rc);
		GetWindowRect(GetParent(hwnd), &rcParent);
		IntersectRect(&rcVisible, &rcParent, &rc);
		if (PtInRect(&rcVisible, fcap->pt)) {
			int thisArea = (rc.bottom - rc.top)*(rc.right - rc.left);
			if (thisArea && (thisArea<fcap->bestArea || fcap->bestArea == 0)) {
				fcap->bestArea = thisArea;
				fcap->hwnd = hwnd;
			}
		}
	}
	return TRUE;
}