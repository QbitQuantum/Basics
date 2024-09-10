LOCAL void
fb_copyarea(WINDISPLAY *mod, struct TVRequest *req)
{
	WINWINDOW *win = req->tvr_Op.CopyArea.Window;
	struct THook *exposehook = (struct THook *)
		TGetTag(req->tvr_Op.CopyArea.Tags, TVisual_ExposeHook, TNULL);
	TINT *sr = req->tvr_Op.CopyArea.Rect;
	TINT dx = req->tvr_Op.CopyArea.DestX - sr[0];
	TINT dy = req->tvr_Op.CopyArea.DestY - sr[1];
	RECT r;

	r.left = sr[4];
	r.top = sr[5];
	r.right = sr[4] + sr[2];
	r.bottom = sr[5] + sr[3];

	if (exposehook)
	{
		RGNDATAHEADER *rdh = (RGNDATAHEADER *) win->fbv_RegionData;
		RECT *rd = (RECT *) (rdh + 1);
		HRGN updateregion = CreateRectRgn(0, 0, 0, 0);
		ScrollDC(win->fbv_HDC, dx, dy, &r, &r, updateregion, NULL);
		if (GetRegionData(updateregion, 1024, (LPRGNDATA) rdh))
		{
			TUINT i;
			for (i = 0; i < rdh->nCount; ++i)
				TCallHookPkt(exposehook, win, (TTAG) (rd + i));
		}
		else
		{
			TDBPRINTF(TDB_WARN,("Regiondata buffer too small\n"));
			InvalidateRgn(win->fbv_HWnd, updateregion, FALSE);
		}
		DeleteObject(updateregion);
	}
	else
		ScrollDC(win->fbv_HDC, dx, dy, &r, &r, NULL, NULL);

	win->fbv_Dirty = TTRUE;
}