void PauseState::init()
{
    sf::Vector2f window( mGame->getTarget()->getSize().x, mGame->getTarget()->getSize().y );
    sf::Vector2f boxSize( 500.0f, 230.f );
    sf::Vector2f boxPosition( window.x / 2.f - boxSize.x / 2.f, window.y / 2.f - boxSize.y / 2.f );

    TextButton* bg = new TextButton();
    bg->setSize( boxSize );
    bg->setPosition( boxPosition );
    bg->setBackgroundColor( sf::Color::Black );
    bg->setVisible( true );
    mMenu.addItem( "1_BG", bg );

    TextButton* resume = new TextButton();
    resume->setFont( DEFAULT_FONT );
    resume->setText( "Resume" );
    resume->setTextColor( sf::Color::White );
    resume->setHighlightTextColor( sf::Color::Green );
    resume->setPosition( sf::Vector2f( boxPosition.x + 20.f, boxPosition.y + 20.f ) );
    resume->setSize( sf::Vector2f( boxSize.x - 40.f, 50.f ) );
    resume->setBackgroundColor( sf::Color( 50.f, 50.f, 50.f, 200.f ) );
    resume->setVisible( true );
    resume->setClickFunction( []( Menu* menu, Game* game )
    {
        game->popState();
    } );
    mMenu.addItem( "2_Resume", resume );

//    TextButton* restart = new TextButton();
//    restart->setFont( DEFAULT_FONT );
//    restart->setText( "Restart" );
//    restart->setTextColor( sf::Color::White );
//    restart->setHighlightTextColor( sf::Color::Green );
//    restart->setPosition( sf::Vector2f( boxPosition.x + 20.f, boxPosition.y + 90.f ) );
//    restart->setSize( sf::Vector2f( boxSize.x - 40.f, 50.f ) );
//    restart->setBackgroundColor( sf::Color( 50.f, 50.f, 50.f, 200.f ) );
//    restart->setVisible( true );
//    std::string map = mMap;
//    restart->setClickFunction( [map]( Menu* menu, Game* game )
//    {
//        std::cout << map << std::endl;
//        game->popState();
//        game->popState();
//        game->pushState( new PlayState( map ) );
//    } );
//    mMenu.addItem( "3_Restart", restart );

    TextButton* menu = new TextButton();
    menu->setFont( DEFAULT_FONT );
    menu->setText( "Return to menu" );
    menu->setTextColor( sf::Color::White );
    menu->setHighlightTextColor( sf::Color::Green );
    menu->setPosition( sf::Vector2f( boxPosition.x + 20.f, boxPosition.y + 90.f ) );
    menu->setSize( sf::Vector2f( boxSize.x - 40.f, 50.f ) );
    menu->setBackgroundColor( sf::Color( 50.f, 50.f, 50.f, 200.f ) );
    menu->setVisible( true );
    menu->setClickFunction( []( Menu* menu, Game* game )
    {
        game->popState();
        game->popState();
    } );
    mMenu.addItem( "4_Menu", menu );

    TextButton* quit = new TextButton();
    quit->setFont( DEFAULT_FONT );
    quit->setText( "Quit" );
    quit->setTextColor( sf::Color::White );
    quit->setHighlightTextColor( sf::Color::Green );
    quit->setPosition( sf::Vector2f( boxPosition.x + 20.f, boxPosition.y + 160.f ) );
    quit->setSize( sf::Vector2f( boxSize.x - 40.f, 50.f ) );
    quit->setBackgroundColor( sf::Color( 50.f, 50.f, 50.f, 200.f ) );
    quit->setVisible( true );
    quit->setClickFunction( []( Menu* menu, Game* game )
    {
        game->quit();
    } );
    mMenu.addItem( "5_Quit", quit );
}