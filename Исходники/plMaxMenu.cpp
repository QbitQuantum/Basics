void plCreateMenu()
{
#if MAX_VERSION_MAJOR <= 11
    AddPlasmaExportMenu();
#endif

    IMenuManager* pMenuMan = GetCOREInterface()->GetMenuManager();
    bool newlyRegistered = pMenuMan->RegisterMenuBarContext(kMyMenuContextId, kMenuName);

    // Is the Max menu version the most recent?
    bool wrongVersion = GetPrivateProfileIntW(L"Menu", L"Version", 0, plMaxConfig::GetPluginIni().WideString().data()) < kMenuVersion;
    if (wrongVersion)
    {
        // Delete the old version of the menu
        IMenu *oldMenu = pMenuMan->FindMenu(kMenuName);
        if (oldMenu)
            pMenuMan->UnRegisterMenu(oldMenu);

        // Update the menu version
        wchar_t buf[12];
        snwprintf(buf, arrsize(buf), L"%d", kMenuVersion);
        WritePrivateProfileStringW(L"Menu", L"Version", buf, plMaxConfig::GetPluginIni().WideString().data());
    }
    
    if (wrongVersion || newlyRegistered)
    {
        IMenu *pMainMenu = pMenuMan->GetMainMenuBar();
        if (!pMainMenu)
        {
            hsAssert(0, "Main menu not found");
            return;
        }

        // Get our action table
        ActionTable* pActionTable = GetCOREInterface()->GetActionManager()->FindTable(kActionId);
        if (!pActionTable)
        {
            hsAssert(0, "Action table not found");
            return;
        }

        // Create the Plasma menu
        IMenu* pPlasmaMenu = GetIMenu();
        pPlasmaMenu->SetTitle(kMenuName);

        // Register the new menu with the system
        pMenuMan->RegisterMenu(pPlasmaMenu, 0);

        /////////////////////////////////////////////////
        // Add the menu items
        //
        IMenuItem* pMenuItem;
 
#if MAX_VERSION_MAJOR >= 12
        // Add the export action to the menu
        pMenuItem = GetIMenuItem();
        pMenuItem->SetActionItem(pActionTable->GetAction(kActionExport));
        pPlasmaMenu->AddItem(pMenuItem);
#endif

        // Add the save selected action to the menu
        pMenuItem = GetIMenuItem();
        pMenuItem->SetActionItem(pActionTable->GetAction(kActionSaveSel));
        pPlasmaMenu->AddItem(pMenuItem);

        // Add the merge action to the menu
        pMenuItem = GetIMenuItem();
        pMenuItem->SetActionItem(pActionTable->GetAction(kActionMerge));
        pPlasmaMenu->AddItem(pMenuItem);

        // Add the component copy action to the menu
        pMenuItem = GetIMenuItem();
        pMenuItem->SetActionItem(pActionTable->GetAction(kActionCompCopy));
        pPlasmaMenu->AddItem(pMenuItem);

        // Add a separator
        pMenuItem = GetIMenuItem();
        pMenuItem->ActAsSeparator();
        pPlasmaMenu->AddItem(pMenuItem);
    
        // Add the component manager to the menu
        pMenuItem = GetIMenuItem();
        pMenuItem->SetActionItem(pActionTable->GetAction(kActionComponent));
        pPlasmaMenu->AddItem(pMenuItem);

        // Add the resource collector to the menu
        pMenuItem = GetIMenuItem();
        pMenuItem->SetActionItem(pActionTable->GetAction(kActionResCollect));
        pPlasmaMenu->AddItem(pMenuItem);

        // Add the texture search to the menu
        pMenuItem = GetIMenuItem();
        pMenuItem->SetActionItem(pActionTable->GetAction(kActionTexSearch));
        pPlasmaMenu->AddItem(pMenuItem);

        // Add the age description to the menu
        pMenuItem = GetIMenuItem();
        pMenuItem->SetActionItem(pActionTable->GetAction(kActionAgeDesc));
        pPlasmaMenu->AddItem(pMenuItem);

        // Add a separator
        pMenuItem = GetIMenuItem();
        pMenuItem->ActAsSeparator();
        pPlasmaMenu->AddItem(pMenuItem);

        // Add the Lock Selected to the menu
        pMenuItem = GetIMenuItem();
        pMenuItem->SetActionItem(pActionTable->GetAction(kActionLock));
        pPlasmaMenu->AddItem(pMenuItem);

        // Add the Unlock Selected to the menu
        pMenuItem = GetIMenuItem();
        pMenuItem->SetActionItem(pActionTable->GetAction(kActionUnlock));
        pPlasmaMenu->AddItem(pMenuItem);

        // Add the Reset Selected to the menu
        pMenuItem = GetIMenuItem();
        pMenuItem->SetActionItem(pActionTable->GetAction(kActionReset));
        pPlasmaMenu->AddItem(pMenuItem);

        // Add the SelectNonRenderables to the menu
        pMenuItem = GetIMenuItem();
        pMenuItem->SetActionItem(pActionTable->GetAction(kActionSelectNonRenderables));
        pPlasmaMenu->AddItem(pMenuItem);

        // Create a new menu item to hold the sub-menu
        IMenuItem* pSubMenuItem1 = GetIMenuItem();   //menu in menu bar...
        pSubMenuItem1->SetSubMenu(pPlasmaMenu);
        pMainMenu->AddItem(pSubMenuItem1);

        pMenuMan->UpdateMenuBar();

        // Save the dang menu, in case Max crashes
        const char *uiDir = GetCOREInterface()->GetDir(APP_UI_DIR);
        char path[MAX_PATH];
        sprintf(path, "%s\\%s", uiDir, "MaxMenus.mnu");
        
        pMenuMan->SaveMenuFile(path);
    }

}