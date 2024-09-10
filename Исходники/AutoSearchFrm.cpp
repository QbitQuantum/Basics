LRESULT AutoSearchFrame::onChange(WORD , WORD , HWND , BOOL& ) {
	if(ctrlAutoSearch.GetSelectedCount() == 1) {
		int sel = ctrlAutoSearch.GetSelectedIndex();
		AutoSearchPtr as = AutoSearchManager::getInstance()->getAutoSearch(sel);

		SearchPageDlg dlg;
		dlg.searchString = as->getSearchString();
		dlg.fileType = as->getFileType();
		dlg.action = as->getAction();
		dlg.remove = as->getRemove();
		dlg.target = as->getTarget();
		dlg.userMatch = as->getNickPattern();
		dlg.matcherString = as->getPattern();
		dlg.matcherType = as->getMatcherType();
		dlg.expireTime = as->getExpireTime();
		dlg.searchDays = as->searchDays;
		dlg.startTime = as->startTime;
		dlg.endTime = as->endTime;
		dlg.targetType = as->getTargetType();
		dlg.checkQueued = as->getCheckAlreadyQueued();
		dlg.checkShared = as->getCheckAlreadyShared();

		if(dlg.DoModal() == IDOK) {
			AutoSearchPtr asNew = AutoSearchPtr(new AutoSearch(as->getEnabled(), dlg.searchString, (SearchManager::TypeModes)dlg.fileType, (AutoSearch::ActionType)dlg.action, 
				dlg.remove, dlg.target, (TargetUtil::TargetType)dlg.targetType, (StringMatcher::Type)dlg.matcherType, dlg.matcherString, dlg.userMatch, dlg.searchInterval, 
				dlg.expireTime, dlg.checkQueued, dlg.checkShared));
			asNew->startTime = dlg.startTime;
			asNew->endTime = dlg.endTime;
			asNew->searchDays = dlg.searchDays;

			if (AutoSearchManager::getInstance()->updateAutoSearch(sel, asNew)) {

				ctrlAutoSearch.SetCheckState(sel, asNew->getEnabled());
				ctrlAutoSearch.SetItemText(sel, COLUMN_VALUE, Text::toT(dlg.searchString).c_str());
				ctrlAutoSearch.SetItemText(sel, COLUMN_TYPE, Text::toT(getType(dlg.fileType)).c_str());
				if(dlg.action == 0){
					ctrlAutoSearch.SetItemText(sel, COLUMN_ACTION, Text::toT(STRING(DOWNLOAD)).c_str());
				} else if(dlg.action == 1){
					ctrlAutoSearch.SetItemText(sel, COLUMN_ACTION, Text::toT(STRING(ADD_TO_QUEUE)).c_str());
				} else if(dlg.action == 2){
					ctrlAutoSearch.SetItemText(sel, COLUMN_ACTION, Text::toT(STRING(AS_REPORT)).c_str());
				}
				ctrlAutoSearch.SetItemText(sel, COLUMN_REMOVE, Text::toT(dlg.target).c_str());
				ctrlAutoSearch.SetItemText(sel, COLUMN_PATH, dlg.remove ? _T("Yes") : _T("No"));
				ctrlAutoSearch.SetItemText(sel, COLUMN_MATCH, Text::toT(dlg.userMatch).c_str());
				ctrlAutoSearch.SetItemData(sel, (LPARAM)asNew.get());
			}
		}
	}
	return 0;
}