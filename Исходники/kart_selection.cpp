void KartSelectionScreen::init()
{
    m_instance_ptr = this;
    Screen::init();
    m_must_delete_on_back = false;

    RibbonWidget* tabs = getWidget<RibbonWidget>("kartgroups");
    assert( tabs != NULL );
    tabs->select(UserConfigParams::m_last_used_kart_group,
                 PLAYER_ID_GAME_MASTER);

    Widget* placeholder = getWidget("playerskarts");
    assert(placeholder != NULL);

    // FIXME : The reserved id value is -1 when we switch from KSS to NKSS and vice-versa

    m_dispatcher->setRootID(placeholder->m_reserved_id);

    g_root_id = placeholder->m_reserved_id;
    if (!m_widgets.contains(m_dispatcher))
    {
        m_widgets.push_back(m_dispatcher);

        // this is only needed if the dispatcher wasn't already in
        // the list of widgets. If it already was, it was added along
        // other widgets.
        m_dispatcher->add();
    }

    m_game_master_confirmed = false;

    tabs->setActive(true);

    m_kart_widgets.clearAndDeleteAll();
    StateManager::get()->resetActivePlayers();
    input_manager->getDeviceManager()->setAssignMode(DETECT_NEW);

    DynamicRibbonWidget* w = getWidget<DynamicRibbonWidget>("karts");
    assert( w != NULL );


    KartHoverListener* karthoverListener = new KartHoverListener(this);
    w->registerHoverListener(karthoverListener);


    // Build kart list (it is built everytime, to account for .g. locking)
    setKartsFromCurrentGroup();

    /*

     TODO: Ultimately, it'd be nice to *not* clear m_kart_widgets so that
     when players return to the kart selection screen, it will appear as
     it did when they left (at least when returning from the track menu).
     Rebuilding the screen is a little tricky.

     */

    /*
    if (m_kart_widgets.size() > 0)
    {
        // trying to rebuild the screen
        for (int n = 0; n < m_kart_widgets.size(); n++)
        {
            PlayerKartWidget *pkw;
            pkw = m_kart_widgets.get(n);
            manualAddWidget(pkw);
            pkw->add();
        }

    }
    else */
    // For now this is what will happen
    if (!m_multiplayer)
    {
        joinPlayer(input_manager->getDeviceManager()->getLatestUsedDevice());
        w->updateItemDisplay();

        // Player 0 select default kart
        if (!w->setSelection(UserConfigParams::m_default_kart, 0, true))
        {
            // if kart from config not found, select the first instead
            w->setSelection(0, 0, true);
        }
    } else
        // Add multiplayer message
        addMultiplayerMessage();

    // This flag will cause that a 'fire' event will be mapped to 'select' (if
    // 'fire' is not assigned to a GUI event). This is done to support the old
    // way of player joining by pressing 'fire' instead of 'select'.
    input_manager->getDeviceManager()->mapFireToSelect(true);

}   // init