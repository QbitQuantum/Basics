void CUnitPane::OnPopupMenuAddUnitToTracking (wxCommandEvent& WXUNUSED(event))
{
    long         idx   = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    CUnit      * pUnit = GetUnit(idx);
    int          sectidx;
    CStr         S;
    const char * szName;
    const char * szValue;
    BOOL         found = FALSE;
    BOOL         ManyUnits = (GetSelectedItemCount() > 1);

    sectidx = gpApp->GetSectionFirst(SZ_SECT_UNIT_TRACKING, szName, szValue);
    while (sectidx >= 0)
    {
        if (!S.IsEmpty())
            S << ",";
        S << szName;
        sectidx = gpApp->GetSectionNext(sectidx, SZ_SECT_UNIT_TRACKING, szName, szValue);
    }
    if (S.IsEmpty())
        S = "Default";


    if (pUnit || ManyUnits)
    {
        CComboboxDlg dlg(this, "Add unit to a tracking group", "Select a group to add unit to.\nTo create a new group, just type in it's name.", S.GetData());
        if (wxID_OK == dlg.ShowModal())
        {

            idx   = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
            while (idx>=0)
            {
                pUnit = GetUnit(idx);
                found = FALSE;

                szValue = gpApp->GetConfig(SZ_SECT_UNIT_TRACKING, dlg.m_Choice.GetData());
                while (szValue && *szValue)
                {
                    szValue = S.GetToken(szValue, ',');
                    if (atol(S.GetData()) == pUnit->Id)
                    {
                        found = TRUE;
                        break;
                    }
                }
                if (found)
                    wxMessageBox(wxT("The unit is already in the group."));
                else
                {
                    S = gpApp->GetConfig(SZ_SECT_UNIT_TRACKING, dlg.m_Choice.GetData());
                    S.TrimRight(TRIM_ALL);
                    if (!S.IsEmpty())
                        S << ",";
                    S << pUnit->Id;
                    gpApp->SetConfig(SZ_SECT_UNIT_TRACKING, dlg.m_Choice.GetData(), S.GetData());
                }

                idx   = GetNextItem(idx, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
            }
        }
    }
}