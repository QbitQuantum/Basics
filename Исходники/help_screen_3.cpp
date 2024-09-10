void HelpScreen3::init()
{
    Screen::init();
    RibbonWidget* w = this->getWidget<RibbonWidget>("category");
    
    if (w != NULL) w->select( "page3", PLAYER_ID_GAME_MASTER );
}   // init