LRESULT FavHubProperties::OnInitDialog(UINT, WPARAM, LPARAM, BOOL&)
{
	// Translate dialog
	SetWindowText(CTSTRING(FAVORITE_HUB_PROPERTIES));
	SetDlgItemText(IDOK, CTSTRING(OK));
	SetDlgItemText(IDCANCEL, CTSTRING(CANCEL));
	SetDlgItemText(IDC_FH_HUB, CTSTRING(HUB));
	SetDlgItemText(IDC_FH_IDENT, CTSTRING(FAVORITE_HUB_IDENTITY));
	SetDlgItemText(IDC_FH_NAME, CTSTRING(HUB_NAME));
	SetDlgItemText(IDC_FH_ADDRESS, CTSTRING(HUB_ADDRESS));
	SetDlgItemText(IDC_FH_HUB_DESC, CTSTRING(DESCRIPTION));
	SetDlgItemText(IDC_FH_NICK, CTSTRING(NICK));
	SetDlgItemText(IDC_FH_PASSWORD, CTSTRING(PASSWORD));
	SetDlgItemText(IDC_FH_USER_DESC, CTSTRING(DESCRIPTION));
	SetDlgItemText(IDC_DEFAULT, CTSTRING(DEFAULT));
	SetDlgItemText(IDC_ACTIVE, CTSTRING(SETTINGS_DIRECT));
	SetDlgItemText(IDC_PASSIVE, CTSTRING(SETTINGS_FIREWALL_PASSIVE));
	SetDlgItemText(IDC_STEALTH, CTSTRING(STEALTH_MODE));
	SetDlgItemText(IDC_FAV_SEARCH_INTERVAL, CTSTRING(MINIMUM_SEARCH_INTERVAL));
	SetDlgItemText(IDC_FAVGROUP, CTSTRING(GROUP));

	// Fill in values
	SetDlgItemText(IDC_HUBNAME, Text::toT(entry->getName()).c_str());
	SetDlgItemText(IDC_HUBDESCR, Text::toT(entry->getDescription()).c_str());
	SetDlgItemText(IDC_HUBADDR, Text::toT(entry->getServer()).c_str());
	SetDlgItemText(IDC_HUBNICK, Text::toT(entry->getNick(false)).c_str());
	SetDlgItemText(IDC_HUBPASS, Text::toT(entry->getPassword()).c_str());
	SetDlgItemText(IDC_HUBUSERDESCR, Text::toT(entry->getUserDescription()).c_str());
	CheckDlgButton(IDC_STEALTH, entry->getStealth() ? BST_CHECKED : BST_UNCHECKED);
	SetDlgItemText(IDC_RAW_ONE, Text::toT(entry->getRawOne()).c_str());
	SetDlgItemText(IDC_RAW_TWO, Text::toT(entry->getRawTwo()).c_str());
	SetDlgItemText(IDC_RAW_THREE, Text::toT(entry->getRawThree()).c_str());
	SetDlgItemText(IDC_RAW_FOUR, Text::toT(entry->getRawFour()).c_str());
	SetDlgItemText(IDC_RAW_FIVE, Text::toT(entry->getRawFive()).c_str());
	SetDlgItemText(IDC_SERVER, Text::toT(entry->getIP()).c_str());
	SetDlgItemText(IDC_FAV_SEARCH_INTERVAL_BOX, Util::toStringW(entry->getSearchInterval()).c_str());

	CComboBox combo;
	combo.Attach(GetDlgItem(IDC_FAVGROUP_BOX));
	combo.AddString(_T("---"));
	combo.SetCurSel(0);

	const FavHubGroups& favHubGroups = FavoriteManager::getInstance()->getFavHubGroups();
	for(FavHubGroups::const_iterator i = favHubGroups.begin(); i != favHubGroups.end(); ++i) {
		const string& name = i->first;
		int pos = combo.AddString(Text::toT(name).c_str());
		
		if(name == entry->getGroup())
			combo.SetCurSel(pos);
	}

	combo.Detach();

	// TODO: add more encoding into wxWidgets version, this is enough now
	// FIXME: following names are Windows only!
	combo.Attach(GetDlgItem(IDC_ENCODING));
	combo.AddString(_T("System default"));
	combo.AddString(_T("English_United Kingdom.1252"));
	combo.AddString(_T("Czech_Czech Republic.1250"));
	combo.AddString(_T("Russian_Russia.1251"));
	combo.AddString(Text::toT(Text::utf8).c_str());

	if(strnicmp("adc://", entry->getServer().c_str(), 6) == 0 || strnicmp("adcs://", entry->getServer().c_str(), 7) == 0)
	{
		combo.SetCurSel(4); // select UTF-8 for ADC hubs
		combo.EnableWindow(false);
	}
	else
	{
		if(entry->getEncoding().empty())
			combo.SetCurSel(0);
		else
			combo.SetWindowText(Text::toT(entry->getEncoding()).c_str());
	}

	combo.Detach();

	if(entry->getMode() == 0)
		CheckRadioButton(IDC_ACTIVE, IDC_DEFAULT, IDC_DEFAULT);
	else if(entry->getMode() == 1)
		CheckRadioButton(IDC_ACTIVE, IDC_DEFAULT, IDC_ACTIVE);
	else if(entry->getMode() == 2)
		CheckRadioButton(IDC_ACTIVE, IDC_DEFAULT, IDC_PASSIVE);

	CEdit tmp;
	tmp.Attach(GetDlgItem(IDC_HUBNAME));
	tmp.SetFocus();
	tmp.SetSel(0,-1);
	tmp.Detach();
	tmp.Attach(GetDlgItem(IDC_HUBNICK));
	tmp.LimitText(35);
	tmp.Detach();
	tmp.Attach(GetDlgItem(IDC_HUBUSERDESCR));
	tmp.LimitText(50);
	tmp.Detach();
	tmp.Attach(GetDlgItem(IDC_HUBPASS));
	tmp.SetPasswordChar('*');
	tmp.Detach();
	
	CUpDownCtrl updown;
	updown.Attach(GetDlgItem(IDC_FAV_SEARCH_INTERVAL_SPIN));
	updown.SetRange32(10, 9999);
	updown.Detach();
	
	CenterWindow(GetParent());
	return FALSE;
}