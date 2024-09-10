void DockWindow::FloatAnimate(DockCont &dc, Rect target)
{
	int max = dockpane[0].GetAnimMaxTicks();
	dc.IgnoreMinSize(true);
	Rect dr = dc.GetRect();
	target -= dr;
	target.top += 16; // Fudge for titlebar. Should get from OS?
	target.left /= max;
	target.right /= max;
	target.top /= max;
	target.bottom /= max;
	for (int i = 0; i < max; i++) {
		dr += target;
		dc.SetRect(dr);
		ProcessEvents();
		Sleep(dockpane[0].GetAnimInterval());
	}
	dc.IgnoreMinSize(false);
}