void EDA_DRAW_FRAME::OnMenuOpen( wxMenuEvent& event )
{
    // On wxWidgets 3.0.x Windows, EVT_MENU_OPEN ( and other EVT_MENU_xx) events are not
    // captured by the ACTON_MENU menus.  While it is fixed in wxWidgets 3.1.x, we still
    // need a solution for the earlier verions.
    //
    // This could be made conditional, but for now I'm going to use the same strategy
    // everywhere so it gets wider testing.
    // Note that if the conditional compilation is reactivated, the Connect() lines in
    // ACTION_MENU::setupEvents() will need to be re-enabled.
//#if defined( __WINDOWS__ ) && wxCHECK_VERSION( 3, 0, 0 ) && !wxCHECK_VERSION( 3, 1, 0 )

    // As if things weren't bad enough, wxWidgets doesn't pass the menu pointer when the
    // event is a wxEVT_MENU_HIGHLIGHT, so we store the menu from the EVT_MENU_OPEN call.
    static ACTION_MENU* currentMenu;

    if( event.GetEventType() == wxEVT_MENU_OPEN )
    {
        currentMenu = dynamic_cast<ACTION_MENU*>( event.GetMenu() );

        if( currentMenu )
            currentMenu->OnMenuEvent( event );
    }
    else if( event.GetEventType() == wxEVT_MENU_HIGHLIGHT )
    {
        if( currentMenu )
            currentMenu->OnMenuEvent( event );
    }
    else    // if( event.GetEventType() == wxEVT_MENU_CLOSE )
    {
        currentMenu = nullptr;
    }
//#endif

    event.Skip();
}