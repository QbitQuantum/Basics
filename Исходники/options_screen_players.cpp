void OptionsScreenPlayers::init()
{
    Screen::init();

    RibbonWidget* tabBar = this->getWidget<RibbonWidget>("options_choice");
    if (tabBar != NULL) tabBar->select( "tab_players", PLAYER_ID_GAME_MASTER );

    tabBar->getRibbonChildren()[0].setTooltip( _("Graphics") );
    tabBar->getRibbonChildren()[1].setTooltip( _("Audio") );
    tabBar->getRibbonChildren()[2].setTooltip( _("User Interface") );
    tabBar->getRibbonChildren()[4].setTooltip( _("Controls") );

    ListWidget* players = this->getWidget<ListWidget>("players");
    assert(players != NULL);

    refreshPlayerList();

    ButtonWidget* you = getWidget<ButtonWidget>("playername");
    unsigned int playerID = PlayerManager::get()->getCurrentPlayer()->getUniqueID();
    core::stringw player_name = L"-";
    const PlayerProfile* curr = PlayerManager::get()->getPlayerById(playerID);
    if(curr)
        player_name = curr->getName();

    you->setText( player_name );
    ((gui::IGUIButton*)you->getIrrlichtElement())->setOverrideFont( GUIEngine::getSmallFont() );

    if (StateManager::get()->getGameState() == GUIEngine::INGAME_MENU)
    {
        players->setDeactivated();
        you->setDeactivated();
    }
    else
    {
        players->setActivated();
        you->setActivated();
    }
}   // init