void wxNumValidatorBase::OnKillFocus(wxFocusEvent& event)
{
    wxTextEntry * const control = GetTextEntry();
    if ( !control )
        return;

    // When we change the control value below, its "modified" status is reset
    // so we need to explicitly keep it marked as modified if it was so in the
    // first place.
    //
    // Notice that only wxTextCtrl (and not wxTextEntry) has
    // IsModified()/MarkDirty() methods hence the need for dynamic cast.
    wxTextCtrl * const text = wxDynamicCast(m_validatorWindow, wxTextCtrl);
    const bool wasModified = text ? text->IsModified() : false;

    control->ChangeValue(NormalizeString(control->GetValue()));

    if ( wasModified )
        text->MarkDirty();

    event.Skip();
}