void Cscope::OnEditorContentMenu(clContextMenuEvent& event)
{
    event.Skip();
    IEditor* editor = m_mgr->GetActiveEditor();
    CHECK_PTR_RET(editor);
    if(FileExtManager::IsCxxFile(editor->GetFileName())) {
        event.GetMenu()->Append(wxID_ANY, _("CScope"), CreateEditorPopMenu());
    }
}