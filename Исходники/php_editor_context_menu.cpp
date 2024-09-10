int PHPEditorContextMenu::RemoveComment(wxStyledTextCtrl* sci, int posFrom, const wxString& value)
{
    sci->SetAnchor(posFrom);
    int posTo = posFrom;
    for(int i = 0; i < (int)value.Length(); i++) posTo = sci->PositionAfter(posTo);

    sci->SetSelection(posFrom, posTo);
    sci->DeleteBack();
    return posTo - posFrom;
}