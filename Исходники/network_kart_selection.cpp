void NetworkKartSelectionScreen::init()
{
    m_multiplayer = false;
    KartSelectionScreen::init();

    RibbonWidget* tabs = getWidget<RibbonWidget>("kartgroups");
    assert( tabs != NULL );
    tabs->select( "standard", PLAYER_ID_GAME_MASTER); // select standard kart group
    tabs->setDeactivated();
    tabs->setVisible(false);

    // change the back button image (because it makes the game quit)
    IconButtonWidget* back_button = getWidget<IconButtonWidget>("back");
    back_button->setImage("gui/main_quit.png");

    m_multiplayer = false;

    // add a widget for each player except self (already exists):
    GameSetup* setup = NetworkManager::getInstance()->getGameSetup();
    if (!setup)
    {
        Log::error("NetworkKartSelectionScreen", "No network game setup registered.");
        return;
    }
    std::vector<NetworkPlayerProfile*> players = setup->getPlayers();

    Log::info("NKSS", "There are %d players", players.size());
    // ---- Get available area for karts
    // make a copy of the area, ands move it to be outside the screen
    Widget* kartsAreaWidget = getWidget("playerskarts");
    // start at the rightmost of the screen
    const int shift = irr_driver->getFrameSize().Width;
    core::recti kartsArea(kartsAreaWidget->m_x + shift,
                            kartsAreaWidget->m_y,
                            kartsAreaWidget->m_x + shift + kartsAreaWidget->m_w,
                            kartsAreaWidget->m_y + kartsAreaWidget->m_h);

    for (unsigned int i = 0; i < players.size(); i++)
    {
        if (players[i]->user_profile == PlayerManager::getCurrentOnlineProfile())
        {
            m_id_mapping.insert(m_id_mapping.begin(),players[i]->race_id); //!< first kart widget always me
            Log::info("NKSS", "Insert %d at pos 0", players[i]->race_id);
            continue; // it is me, don't add again
        }

        Log::info("NKSS", "Adding %d at pos %d", players[i]->race_id, i);
        m_id_mapping.push_back(players[i]->race_id);

        StateManager::ActivePlayer* aplayer = NULL; // player is remote

        std::string selected_kart_group = "standard"; // standard group

        PlayerKartWidget* newPlayerWidget =
            new PlayerKartWidget(this, aplayer, players[i]->user_profile, kartsArea, m_kart_widgets.size(),
                                 selected_kart_group);

        manualAddWidget(newPlayerWidget);
        m_kart_widgets.push_back(newPlayerWidget);

        newPlayerWidget->add();
    }

    const int amount = m_kart_widgets.size();
    Widget* fullarea = getWidget("playerskarts");

    const int splitWidth = fullarea->m_w / amount;

    for (int n=0; n<amount; n++)
    {
        m_kart_widgets[n].move( fullarea->m_x + splitWidth*n,
                                fullarea->m_y, splitWidth, fullarea->m_h);
    }

}