void Copyright::OnEditorContextMenu(clContextMenuEvent& event)
{
    event.Skip();
    event.GetMenu()->Append(XRCID("CR_insert_copyrights"), _("Insert Copyrights Block"));
}