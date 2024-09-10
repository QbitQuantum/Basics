void CodeLiteDiff::OnTabContextMenu(clContextMenuEvent& event)
{
    event.Skip();
    DoClear();
    IEditor* activeEditor = m_mgr->GetActiveEditor();
    CHECK_PTR_RET(activeEditor);

    m_leftFile = activeEditor->GetFileName();

    // Edit the context menu
    wxMenuItem* mi = new wxMenuItem(event.GetMenu(), XRCID("diff_compare_with"), _("Compare with..."), "");
    mi->SetBitmap(m_mgr->GetStdIcons()->LoadBitmap("diff"));
    event.GetMenu()->Append(mi);
    event.GetMenu()->Bind(wxEVT_MENU, &CodeLiteDiff::OnDiff, this, XRCID("diff_compare_with"));
}