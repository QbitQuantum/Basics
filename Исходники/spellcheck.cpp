void SpellCheck::OnEditorContextMenuShowing(clContextMenuEvent& e)
{
    e.Skip();
    wxMenu* menu = CreateSubMenu();
    menu->Check(XRCID(s_contCheckID.ToUTF8()), m_checkContinuous);
    e.GetMenu()->Append(IDM_BASE, _("Spell Checker"), menu);
}