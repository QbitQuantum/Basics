void CMakePlugin::OnProjectContextMenu(clContextMenuEvent& event)
{
    event.Skip();
    CHECK_COND_RET(clCxxWorkspaceST::Get()->IsOpen());

    ProjectPtr p = GetSelectedProject();
    CHECK_COND_RET(p);

    BuildConfigPtr buildConf = p->GetBuildConfiguration();
    CHECK_COND_RET(buildConf);

    CHECK_COND_RET(buildConf->GetBuilder()->GetName() == "CMake");

    // The selected project is using CMake builder
    // Add our context menu
    wxMenu* menu = event.GetMenu()->GetParent(); // We want to attach this action to the main menu, not the subclass
    CHECK_PTR_RET(menu);

    const wxMenuItemList& items = menu->GetMenuItems();

    size_t buildPos = 0;
    size_t settingsPos = 0;
    size_t curpos = 0;
    wxMenuItemList::const_iterator iter = items.begin();
    for(; iter != items.end(); ++iter) {
        if((*iter)->GetId() == XRCID("build_project")) {
            buildPos = curpos;
        }
        if((*iter)->GetId() == XRCID("project_properties")) {
            settingsPos = curpos;
        }
        ++curpos;
    }

    wxFileName projectFile = p->GetFileName();
    projectFile.SetFullName(CMAKELISTS_FILE);
    if(projectFile.FileExists()) {
        wxMenuItem* item = new wxMenuItem(NULL, XRCID("cmake_open_cmake"), _("Open CMakeLists.txt"));
        item->SetBitmap(m_mgr->GetStdIcons()->LoadBitmap("cmake"));
        menu->Insert(settingsPos, item);
    }

    menu->Insert(buildPos, XRCID("cmake_run_cmake"), _("Run CMake"));
    menu->InsertSeparator(buildPos);
    menu->Insert(buildPos, XRCID("cmake_export_cmakelists"), _("Export CMakeLists.txt"));
    menu->Bind(wxEVT_MENU, &CMakePlugin::OnRunCMake, this, XRCID("cmake_run_cmake"));
    menu->Bind(wxEVT_MENU, &CMakePlugin::OnOpenCMakeLists, this, XRCID("cmake_open_cmake"));
    menu->Bind(wxEVT_MENU, &CMakePlugin::OnExportCMakeLists, this, XRCID("cmake_export_cmakelists"));
}