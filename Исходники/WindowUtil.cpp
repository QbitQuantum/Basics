static BOOL CALLBACK SnapWindowProc(HWND hwnd,LPARAM lParam)
{
	SnapWindowInfo *pInfo=reinterpret_cast<SnapWindowInfo*>(lParam);

	if (IsWindowVisible(hwnd) && hwnd!=pInfo->hwnd && hwnd!=pInfo->hwndExclude) {
		RECT rc,rcEdge;

		GetWindowRect(hwnd,&rc);
		if (rc.right>rc.left && rc.bottom>rc.top) {
			if (rc.top<pInfo->rcOriginal.bottom && rc.bottom>pInfo->rcOriginal.top) {
				if (abs(rc.left-pInfo->rcOriginal.right)<abs(pInfo->rcNearest.right)) {
					rcEdge.left=rc.left;
					rcEdge.right=rc.left;
					rcEdge.top=max(rc.top,pInfo->rcOriginal.top);
					rcEdge.bottom=min(rc.bottom,pInfo->rcOriginal.bottom);
					if (IsWindowEdgeVisible(hwnd,GetTopWindow(GetDesktopWindow()),&rcEdge,pInfo->hwnd))
						pInfo->rcNearest.right=rc.left-pInfo->rcOriginal.right;
				}
				if (abs(rc.right-pInfo->rcOriginal.left)<abs(pInfo->rcNearest.left)) {
					rcEdge.left=rc.right;
					rcEdge.right=rc.right;
					rcEdge.top=max(rc.top,pInfo->rcOriginal.top);
					rcEdge.bottom=min(rc.bottom,pInfo->rcOriginal.bottom);
					if (IsWindowEdgeVisible(hwnd,GetTopWindow(GetDesktopWindow()),&rcEdge,pInfo->hwnd))
						pInfo->rcNearest.left=rc.right-pInfo->rcOriginal.left;
				}
			}
			if (rc.left<pInfo->rcOriginal.right && rc.right>pInfo->rcOriginal.left) {
				if (abs(rc.top-pInfo->rcOriginal.bottom)<abs(pInfo->rcNearest.bottom)) {
					rcEdge.left=max(rc.left,pInfo->rcOriginal.left);
					rcEdge.right=min(rc.right,pInfo->rcOriginal.right);
					rcEdge.top=rc.top;
					rcEdge.bottom=rc.top;
					if (IsWindowEdgeVisible(hwnd,GetTopWindow(GetDesktopWindow()),&rcEdge,pInfo->hwnd))
						pInfo->rcNearest.bottom=rc.top-pInfo->rcOriginal.bottom;
				}
				if (abs(rc.bottom-pInfo->rcOriginal.top)<abs(pInfo->rcNearest.top)) {
					rcEdge.left=max(rc.left,pInfo->rcOriginal.left);
					rcEdge.right=min(rc.right,pInfo->rcOriginal.right);
					rcEdge.top=rc.bottom;
					rcEdge.bottom=rc.bottom;
					if (IsWindowEdgeVisible(hwnd,GetTopWindow(GetDesktopWindow()),&rcEdge,pInfo->hwnd))
						pInfo->rcNearest.top=rc.bottom-pInfo->rcOriginal.top;
				}
			}
		}
	}
	return TRUE;
}