void OptionsScreenUI::init()
{
    Screen::init();
    RibbonWidget* ribbon = getWidget<RibbonWidget>("options_choice");
    if (ribbon != NULL)  ribbon->select( "tab_ui", PLAYER_ID_GAME_MASTER );
    
    ribbon->getRibbonChildren()[0].setTooltip( _("Graphics") );
    ribbon->getRibbonChildren()[1].setTooltip( _("Audio") );
    ribbon->getRibbonChildren()[3].setTooltip( _("Players") );
    ribbon->getRibbonChildren()[4].setTooltip( _("Controls") );
    
    GUIEngine::SpinnerWidget* skinSelector = getWidget<GUIEngine::SpinnerWidget>("skinchoice");
    assert( skinSelector != NULL );

    // ---- video modes

    CheckBoxWidget* fps = getWidget<CheckBoxWidget>("showfps");
    assert( fps != NULL );
    fps->setState( UserConfigParams::m_display_fps );
    CheckBoxWidget* news = getWidget<CheckBoxWidget>("enable-internet");
    assert( news != NULL );
    news->setState( UserConfigParams::m_internet_status
                                            ==INetworkHttp::IPERM_ALLOWED );
    CheckBoxWidget* min_gui = getWidget<CheckBoxWidget>("minimal-racegui");
    assert( min_gui != NULL );
    min_gui->setState( UserConfigParams::m_minimal_race_gui);
    if (StateManager::get()->getGameState() == GUIEngine::INGAME_MENU)
        min_gui->setDeactivated();
    else
        min_gui->setActivated();

    
    // --- select the right skin in the spinner
    bool currSkinFound = false;
    const int skinCount = m_skins.size();
    for (int n=0; n<skinCount; n++)
    {
        const std::string skinFileName = StringUtils::getBasename(m_skins[n]);
        
        if (UserConfigParams::m_skin_file.c_str() == skinFileName)
        {
            skinSelector->setValue(n);
            currSkinFound = true;
            break;
        }
    }
    if (!currSkinFound)
    {
        std::cerr << "WARNING: couldn't find current skin in the list of skins!!\n";
        skinSelector->setValue(0);
        GUIEngine::reloadSkin();
    }
    
    // --- language
    ListWidget* list_widget = getWidget<ListWidget>("language");
    
    // I18N: in the language choice, to select the same language as the OS
    list_widget->addItem("system", _("System Language"));
    
    const std::vector<std::string>* lang_list = translations->getLanguageList();
    const int amount = lang_list->size();
    for (int n=0; n<amount; n++)
    {
        std::string code_name = (*lang_list)[n];
        std::string nice_name = tinygettext::Language::from_name(code_name.c_str()).get_name();
        list_widget->addItem(code_name, core::stringw(code_name.c_str()) + " (" +
                             nice_name.c_str() + ")");
    }
        
    list_widget->setSelectionID( list_widget->getItemID(UserConfigParams::m_language) );
    
    // Forbid changing language while in-game, since this crashes (changing the language involves
    // tearing down and rebuilding the menu stack. not good when in-game)
    if (StateManager::get()->getGameState() == GUIEngine::INGAME_MENU)
    {
        list_widget->setDeactivated();
    }
    else
    {
        list_widget->setActivated();
    }
    
}   // init