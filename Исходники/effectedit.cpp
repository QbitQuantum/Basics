void SaveEffect(HWND dialog, EditEffect *data)
{
	Effect *e = &data->e;

    // CB_ERR is returned from no selection. this shows that CB_ERR == -1.
	//MessageBox(dialog, std::string("CB_ERR").append(toString<int>(CB_ERR)).c_str(), "Effect Editor", MB_OKCANCEL);
	// that means that when an item is not selected in a combobox,
	// CB_GETCURSEL saves -1. I think that this is the default value for
	// unused fields in AoK.  However, what about Azzzru's panel having no
	// value? That is different as what he does shortens the SCX file.
	// How does AoKTS load his scenarios then? This means that a -1
	// value for panel should not give error to aokts.
	int newtype = SendDlgItemMessage(dialog, IDC_E_TYPE, CB_GETCURSEL, 0, 0);
	if (newtype != CB_ERR)
	{
		e->type = newtype;
		GetWindowText(GetDlgItem(dialog, IDC_E_SOUND), e->sound);
		e->soundid = GetDlgItemInt(dialog, IDC_E_SOUNDID, NULL, TRUE);
		BOOL translated = NULL;
		int panel = GetDlgItemInt(dialog, IDC_E_PANEL, &translated, TRUE);
		if (!translated) {
		    SString panelname;

            GetWindowText(GetDlgItem(dialog, IDC_E_PANEL), panelname);
		    panel = SendDlgItemMessage(dialog, IDC_E_PANEL, CB_FINDSTRING, -1, (LPARAM) (LPCTSTR)panelname.c_str());

		    if (panel == CB_ERR)
		        panel = -1;
		}
		e->panel = panel;
		GetWindowText(GetDlgItem(dialog, IDC_E_TEXT), e->text);
		e->disp_time = GetDlgItemInt(dialog, IDC_E_DTIME, NULL, TRUE);
		e->pUnit = (UnitLink*)LCombo_GetSelPtr(dialog, IDC_E_UCNST);
		e->textid = GetDlgItemInt(dialog, IDC_E_TEXTID, NULL, TRUE);
		e->s_player = SendDlgItemMessage(dialog, IDC_E_SPLAY, CB_GETCURSEL, 0, 0);
		e->t_player = SendDlgItemMessage(dialog, IDC_E_TPLAY, CB_GETCURSEL, 0, 0);
		e->diplomacy = (enum Diplomacy)SendDlgItemMessage(dialog, IDC_E_DSTATE, CB_GETCURSEL, 0, 0);
		e->location.x = GetDlgItemInt(dialog, IDC_E_LOCX, NULL, TRUE);
		e->location.y = GetDlgItemInt(dialog, IDC_E_LOCY, NULL, TRUE);
		e->area.left = GetDlgItemInt(dialog, IDC_E_AREAX1, NULL, TRUE);
		e->area.bottom = GetDlgItemInt(dialog, IDC_E_AREAY1, NULL, TRUE);
		e->area.right = GetDlgItemInt(dialog, IDC_E_AREAX2, NULL, TRUE);
		e->area.top = GetDlgItemInt(dialog, IDC_E_AREAY2, NULL, TRUE);
		e->pTech = (TechLink*)LCombo_GetSelPtr(dialog, IDC_E_RESEARCH);
		e->ai_goal = GetDlgItemInt(dialog, IDC_E_AIGOAL, NULL, TRUE);
		e->amount = GetDlgItemInt(dialog, IDC_E_AMOUNT, NULL, TRUE);
		e->res_type = LCombo_GetSelId(dialog, IDC_E_RESTYPE);

		//get the data, not the index, for these
		e->trig_index = Combo_GetSelData(GetDlgItem(dialog, IDC_E_TRIG));
		e->group = Combo_GetSelData(GetDlgItem(dialog, IDC_E_GROUP));
		e->utype = Combo_GetSelData(GetDlgItem(dialog, IDC_E_UTYPE));
	}
}