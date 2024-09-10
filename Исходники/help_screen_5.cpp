void HelpScreen5::init()
{
    Screen::init();
    RibbonWidget* w = this->getWidget<RibbonWidget>("category");

    if (w != NULL)
    {
        w->setFocusForPlayer(PLAYER_ID_GAME_MASTER);
        w->select( "page5", PLAYER_ID_GAME_MASTER );
    }
}   // init