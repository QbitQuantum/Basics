void CDiasStatusBar::OnRButtonUp (UINT nFlags, CPoint point) {
	if (GetCapture() != this) {
		ReleaseCapture ();
		return;
	}
	ReleaseCapture ();

	CRect rect1, rect2;
	GetItemRect (2, rect1);
	GetItemRect (3, rect2);

	uvar32_64 n, count = 0;
	CaImMenu menu;
	CaImMenuItem** ppItems;
	menu.CreatePopupMenu ();

	GetItemRect (2, rect1);
	GetItemRect (3, rect2);
	if (rect1.PtInRect (point) || rect2.PtInRect (point)) {
		count = theApp.GeomScales.GetCount ();
		ppItems = new CaImMenuItem*[count];
		for (n = 0; n < count; ++n) {
			ppItems[n] = new CaImMenuItem (theApp.GeomScales[n].GetName() + "\t(" + theApp.GeomScales[n].GetUnits () + ")",
				(theApp.GeomScales[aimActive].GetPos () == n) ? AMIS_CHECKED : 0);
			menu.AppendMenu (MF_STRING | MF_ENABLED | MF_OWNERDRAW, ID_TOOLS_GEOMSCALE_1 + n, (LPCTSTR)ppItems[n]);
		}
		menu.CheckMenuRadioItem (0, n, theApp.GeomScales[aimActive].GetPos (), MF_BYPOSITION);
	}
	GetItemRect (4, rect1);
	GetItemRect (5, rect2);
	if (rect1.PtInRect (point) || rect2.PtInRect (point)) {
		count = theApp.DensScales.GetCount ();
		ppItems = new CaImMenuItem*[count];
		for (n = 0; n < count; ++n) {
			ppItems[n] = new CaImMenuItem (theApp.DensScales[n].GetName() + "\t(" + theApp.DensScales[n].GetUnits () + ")",
				(theApp.DensScales[aimActive].GetPos () == n) ? AMIS_CHECKED : 0);
			menu.AppendMenu (MF_STRING | MF_ENABLED | MF_OWNERDRAW, ID_TOOLS_GEOMSCALE_1 + n, (LPCTSTR)ppItems[n]);
		}
		menu.CheckMenuRadioItem (0, n, theApp.DensScales[aimActive].GetPos (), MF_BYPOSITION);
	}

	GetWindowRect (rect2);
	menu.TrackPopupMenu (TPM_LEFTALIGN, point.x + rect2.left, point.y + rect2.top, this);

	for (n = 0; n < count; ++n)
		delete ppItems[n];
	if (count > 0)
		delete [] ppItems;
}