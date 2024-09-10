static void IterateThroughItems(HWND WND, HMENU menu, POINT *p)
{
	int count = GetMenuItemCount(menu);
	RECT rec;
	MENUITEMINFO info;
	int i;
	TCHAR buf[MATCHED_WORD_BUF_SIZE];
	for (i=0; i<count; i++) {
		if (GetMenuItemRect(WND, menu, i, &rec) && (rec.left<=p->x) 
			&& (p->x<=rec.right) && (rec.top<=p->y) && (p->y<=rec.bottom)) {
			ZeroMemory(&info, sizeof(info));
			info.cbSize = sizeof(info);
			info.fMask = MIIM_TYPE | MIIM_SUBMENU;
			info.cch = MATCHED_WORD_BUF_SIZE;
			info.dwTypeData = buf;
			GetMenuItemInfo(menu, i, TRUE, &info);
			if (info.cch>0) {
				if (info.cch >= MATCHED_WORD_BUF_SIZE)
					CurParams->WordLen = MATCHED_WORD_BUF_SIZE-1;
				else
					CurParams->WordLen = info.cch;
#ifdef UNICODE
				CurParams->Unicode = TRUE;
				CurParams->WordLen = MyCopyMemory(CurParams->MatchedWordW, info.dwTypeData, CurParams->WordLen);
#else
				CurParams->Unicode = FALSE;
				CurParams->WordLen = MyCopyMemory(CurParams->MatchedWordA, info.dwTypeData, CurParams->WordLen);
#endif
				CurParams->BeginPos = 0;
			}
			break;
		}
	}
}