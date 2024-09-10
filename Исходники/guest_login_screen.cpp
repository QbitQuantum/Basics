/** Make sure this tab is actually selected.
 */
void GuestLoginScreen::init()
{
    Screen::init();
    RibbonWidget* tabs = this->getWidget<RibbonWidget>("login_tabs");
    if (tabs) tabs->select( "tab_guest_login", PLAYER_ID_GAME_MASTER );
}   // init