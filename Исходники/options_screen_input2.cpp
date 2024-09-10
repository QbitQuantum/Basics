void OptionsScreenInput2::init()
{
    Screen::init();
    RibbonWidget* tabBar = getWidget<RibbonWidget>("options_choice");
    if (tabBar != NULL)  tabBar->select( "tab_controls",
                                        PLAYER_ID_GAME_MASTER );

    tabBar->getRibbonChildren()[0].setTooltip( _("Graphics") );
    tabBar->getRibbonChildren()[1].setTooltip( _("Audio") );
    tabBar->getRibbonChildren()[2].setTooltip( _("User Interface") );
    tabBar->getRibbonChildren()[3].setTooltip( _("Players") );


    ButtonWidget* deleteBtn = getWidget<ButtonWidget>("delete");
    if (m_config->getType() != DEVICE_CONFIG_TYPE_KEYBOARD)
    {
        core::stringw label = (m_config->isEnabled()
                            ? //I18N: button to disable a gamepad configuration
                              _("Disable Device")
                            : //I18N: button to enable a gamepad configuration
                              _("Enable Device"));

        // Make sure button is wide enough as the text is being changed away
        // from the original value
        core::dimension2d<u32> size =
            GUIEngine::getFont()->getDimension(label.c_str());
        const int needed = size.Width + deleteBtn->getWidthNeededAroundLabel();
        if (deleteBtn->m_w < needed) deleteBtn->m_w = needed;

        deleteBtn->setLabel(label);
    }
    else
    {
        deleteBtn->setLabel(_("Delete Configuration"));

        if (input_manager->getDeviceList()->getKeyboardAmount() < 2)
        {
            // don't allow deleting the last config
            deleteBtn->setDeactivated();
        }
        else
        {
            deleteBtn->setActivated();
        }
    }

    // Make the two buttons the same length, not strictly needed but will
    // look nicer...
    ButtonWidget* backBtn = getWidget<ButtonWidget>("back_to_device_list");
    if (backBtn->m_w < deleteBtn->m_w) backBtn->m_w   = deleteBtn->m_w;
    else                               deleteBtn->m_w = backBtn->m_w;

    backBtn->moveIrrlichtElement();
    deleteBtn->moveIrrlichtElement();

    LabelWidget* label = getWidget<LabelWidget>("title");
    label->setText( m_config->getName().c_str(), false );

    GUIEngine::ListWidget* actions =
        getWidget<GUIEngine::ListWidget>("actions");
    assert( actions != NULL );

    // ---- create list skeleton (right number of items, right internal names)
    //      their actualy contents will be adapted as needed after

    //I18N: Key binding section
    addListItemSubheader(actions, "game_keys_section", _("Game Keys"));
    addListItem(actions, PA_STEER_LEFT);
    addListItem(actions, PA_STEER_RIGHT);
    addListItem(actions, PA_ACCEL);
    addListItem(actions, PA_BRAKE);
    addListItem(actions, PA_FIRE);
    addListItem(actions, PA_NITRO);
    addListItem(actions, PA_DRIFT);
    addListItem(actions, PA_LOOK_BACK);
    addListItem(actions, PA_RESCUE);
    addListItem(actions, PA_PAUSE_RACE);


    //I18N: Key binding section
    addListItemSubheader(actions, "menu_keys_section", _("Menu Keys"));
    addListItem(actions, PA_MENU_UP);
    addListItem(actions, PA_MENU_DOWN);
    addListItem(actions, PA_MENU_LEFT);
    addListItem(actions, PA_MENU_RIGHT);
    addListItem(actions, PA_MENU_SELECT);
    addListItem(actions, PA_MENU_CANCEL);

    updateInputButtons();

    // Disable deletion keyboard configurations
    if (StateManager::get()->getGameState() == GUIEngine::INGAME_MENU)
    {
        getWidget<ButtonWidget>("delete")->setDeactivated();
    } else
    {
        getWidget<ButtonWidget>("delete")->setActivated();
    }
}   // init