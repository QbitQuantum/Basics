void ToolbarManager::getFrom(CReBarCtrl& ReBar, const string& aName) {
	dcassert(ReBar.IsWindow());
	removeToolbarEntry(getToolbarEntry(aName));

	ToolbarEntry* t = new ToolbarEntry();
	string id, cx, bl,dl;
	t->setName(aName);
	t->setBandCount(ReBar.GetBandCount());

	for(int i = 0; i < t->getBandCount(); i++) {
		dl = ((i > 0) ? "," : "");
		REBARBANDINFO rbi;
		rbi.cbSize = sizeof(rbi);
		rbi.fMask = RBBIM_ID | RBBIM_SIZE | RBBIM_STYLE;
		ReBar.GetBandInfo(i, &rbi);
		id += dl + Util::toString(rbi.wID);
		cx += dl + Util::toString(rbi.cx);
		bl += dl + (((rbi.fStyle & RBBS_BREAK) != 0) ? "1" : "0");

	}

	t->setID(id);
	t->setCX(cx);
	t->setBreakLine(bl);
	toolbarEntries.push_back(t);
}