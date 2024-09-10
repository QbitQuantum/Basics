void wxFormBuilder::OnShowFileContextMenu(clContextMenuEvent& event)
{
    event.Skip();
    wxFileName file(event.GetFileName());
    if(file.GetExt() == "fbp") {
        wxMenu* menu = event.GetMenu();
        menu->PrependSeparator();
        menu->Prepend(
            new wxMenuItem(menu, XRCID("wxfb_open"), _("Open with wxFormBuilder..."), wxEmptyString, wxITEM_NORMAL));
    }
}