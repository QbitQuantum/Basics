void wxSTEditorFindReplacePanel::UpdateButtons()
{
    // Can't search backwards when using regexp
    if (m_regexpFindCheckBox->GetValue() && m_backwardsCheckBox->IsEnabled())
    {
        m_backwardsCheckBox->SetValue(false);
        m_backwardsCheckBox->Enable(false);
    }
    else if (!m_regexpFindCheckBox->GetValue() && !m_backwardsCheckBox->IsEnabled())
    {
        m_backwardsCheckBox->Enable(true);
    }

    // update the find/replace button state
    const wxString findStr = m_findCombo->GetValue();
    bool enable = findStr.Length() > 0u;

    wxSTEditor *edit = GetEditor();

    int flags = GetFindFlags();

    if (enable)
    {
        bool changed = edit ? ((edit->GetFindString() != findStr)||(edit->GetFindFlags() != flags)) : true;
        enable &= ((edit && edit->CanFind()) ? true : changed);
    }

    if (m_findButton->IsEnabled() != enable)
        m_findButton->Enable(enable);

    if (HasFlag(wxFR_REPLACEDIALOG))
    {
        // Don't want recursive find
        if (m_findReplaceData->StringCmp(findStr, m_replaceCombo->GetValue(), flags))
            enable = false;

        if (m_replaceAllButton && (m_replaceAllButton->IsEnabled() != enable))
            m_replaceAllButton->Enable(enable);

        wxString selText = edit ? edit->GetSelectedText() : wxString(wxEmptyString);

        // can only replace if already selecting the "find" text
        if (enable && edit && !edit->SelectionIsFindString(findStr, flags))
            enable = false;
        else if (!m_regexpFindCheckBox->IsChecked() && !m_findReplaceData->StringCmp(findStr, selText, flags))
            enable = false;

        if (m_replaceButton->IsEnabled() != enable)
            m_replaceButton->Enable(enable);
        if (m_replaceFindButton->IsEnabled() != enable)
            m_replaceFindButton->Enable(enable);
    }
}