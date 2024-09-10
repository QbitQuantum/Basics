// -----------------------------------------------------------------------------
void LoginScreen::init()
{
    Screen::init();
    // Make sure this tab is actually focused.
    RibbonWidget* tabs = this->getWidget<RibbonWidget>("login_tabs");
    if (tabs) tabs->select( "tab_login", PLAYER_ID_GAME_MASTER );

    TextBoxWidget *password_widget = getWidget<TextBoxWidget>("password");
    password_widget->setPasswordBox(true,L'*');
    
    m_options_widget = getWidget<RibbonWidget>("options");
    assert(m_options_widget);
    m_options_widget->setActivated();

    m_info_widget = getWidget<LabelWidget>("info");
    assert(m_info_widget != NULL);
    m_success = false;

    // As default don't select 'remember'
    getWidget<CheckBoxWidget>("remember")->setState(false);
}   // init