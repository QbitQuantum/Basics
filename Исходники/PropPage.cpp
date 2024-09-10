void PropPage::read(HWND page, Item const* items, ListItem* listItems /* = NULL */, HWND list /* = 0 */)
{
#if DIM_EDIT_EXPERIMENT
	CDimEdit *tempCtrl;
#endif
	dcassert(page != NULL);

	bool const useDef = true;
	for(Item const* i = items; i->type != T_END; i++)
	{
		switch(i->type)
		{
		case T_STR:
#if DIM_EDIT_EXPERIMENT
			tempCtrl = new CDimEdit;
			if (tempCtrl) {
				tempCtrl->SubclassWindow(GetDlgItem(page, i->itemID));
				tempCtrl->SetDimText(settings->get((SettingsManager::StrSetting)i->setting, true));
				tempCtrl->SetDimColor(RGB(192, 192, 192));
				ctrlMap[i->itemID] = tempCtrl;
			}
#endif
				if (GetDlgItem(page, i->itemID) == NULL) {
					// Control not exist ? Why ??
					throw;
				}
				::SetDlgItemText(page, i->itemID,
				Text::toT(settings->get((SettingsManager::StrSetting)i->setting, useDef)).c_str());
			break;
		case T_INT:

				if (GetDlgItem(page, i->itemID) == NULL) {
					// Control not exist ? Why ??
					throw;
				}
				::SetDlgItemInt(page, i->itemID,
					settings->get((SettingsManager::IntSetting)i->setting, useDef), FALSE);
			break;
		case T_INT64:
			if(!SettingsManager::getInstance()->isDefault(i->setting)) {
				tstring s = Util::toStringW(settings->get((SettingsManager::Int64Setting)i->setting, useDef));
				::SetDlgItemText(page, i->itemID, s.c_str());
			}
			break;
		case T_BOOL:
			if (GetDlgItem(page, i->itemID) == NULL) {
				// Control not exist ? Why ??
				throw;
			}
			if(settings->getBool((SettingsManager::IntSetting)i->setting, useDef))
				::CheckDlgButton(page, i->itemID, BST_CHECKED);
			else
				::CheckDlgButton(page, i->itemID, BST_UNCHECKED);
		}
	}

	if(listItems != NULL) {
		CListViewCtrl ctrl;

		ctrl.Attach(list);
		CRect rc;
		ctrl.GetClientRect(rc);
		ctrl.SetExtendedListViewStyle(LVS_EX_LABELTIP | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
		ctrl.InsertColumn(0, _T("Dummy"), LVCFMT_LEFT, rc.Width(), 0);

		LVITEM lvi = {0};
		lvi.mask = LVIF_TEXT;
		lvi.iSubItem = 0;

		for(int i = 0; listItems[i].setting != 0; i++) {
			lvi.iItem = i;
			lvi.pszText = const_cast<TCHAR*>(CTSTRING_I(listItems[i].desc));
			ctrl.InsertItem(&lvi);
			ctrl.SetCheckState(i, SettingsManager::getInstance()->getBool(SettingsManager::IntSetting(listItems[i].setting), true));
		}
		ctrl.SetColumnWidth(0, LVSCW_AUTOSIZE);
		ctrl.Detach();
	}
}