void SpyFrame::handleSearch(const tstring& searchString) {
	if(Util::strnicmp(searchString.c_str(), _T("TTH:"), 4) == 0)
		SearchFrame::openWindow(getParent(), searchString.substr(4), 0, SearchManager::SIZE_DONTCARE, SearchManager::TYPE_TTH);
	else
		SearchFrame::openWindow(getParent(), searchString);
}