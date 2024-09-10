void SnipWiz::OnEditorContextMenu(clContextMenuEvent& event)
{
    event.Skip();
    IEditor* editor = m_mgr->GetActiveEditor();
    CHECK_PTR_RET(editor);

    if(FileExtManager::IsCxxFile(editor->GetFileName())) {
        wxMenu* newMenu = CreateSubMenu();
        event.GetMenu()->Append(wxID_ANY, _("Snippets"), newMenu);
    }
}