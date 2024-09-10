void Divine::onBeginEvent(Geoscape* geoscape)
{
    castBoogieEvent();
    castFestivalEvent();
    castClimbingEvent();
    castSmokeballEvent();
    castCommunityEvent();

    // if player isn't in home location and isn't travelling
    if( geoscape->getPlayerLocation() && geoscape->getPlayerLocation()->getDatabaseId() != 0 )
    {
        // location info
        database::LocationInfo* info = database::LocationInfo::getRecord( geoscape->getPlayerLocation()->getDatabaseId() );

        // home location travelling cost
        Vector2f currentCoords = geoscape->getPlayerLocation()->getLocationCoords();
        Vector2f targetCoords = geoscape->getHomeLocation()->getLocationCoords();
        float targetDistance = ( targetCoords - currentCoords ).length();
        targetDistance = targetDistance * 40075.696f / geoscape->getWindow()->getPanel()->getRect().getWidth();
        float referenceCost = 0.05f;
        float targetCost = targetDistance * referenceCost;
        float referenceTime = 0.1f;
        float targetTime = targetDistance * referenceTime;

        // check we have enought money to stay in location
        if( targetCost + info->stayFee < _career->getVirtues()->evolution.funds )
        {
            // pay fee
            _career->getVirtues()->evolution.funds -= info->stayFee;
        }
        else
        {
            // travel to home location
            // remove player from location
            unsigned int departureId = geoscape->getPlayerLocation()->getDatabaseId();
            geoscape->getPlayerLocation()->setPlayer( false );
            // decrease funds
            _career->getVirtues()->evolution.funds -= targetCost;
            // add event
            _career->addEvent( new Travel( _career, departureId, 0, targetTime ) );
            // message
            geoscape->addHistory( Gameplay::iLanguage->getUnicodeString(293), Vector4f( 1,0.25,0.25,1 ) );
        }
    }

    // simulate market dynamics
    unsigned int maxTransactions = 10;
    // simulate buying
    unsigned int numTransactions = getCore()->getRandToolkit()->getUniformInt() % maxTransactions;
    while( numTransactions && geoscape->getMarketSize() )
    {
        // buy random gear
        geoscape->removeGearFromMarket( 
            getCore()->getRandToolkit()->getUniformInt() % geoscape->getMarketSize()
        );
        numTransactions--;
    }
    // simulate selling
    numTransactions = getCore()->getRandToolkit()->getUniformInt() % maxTransactions;
    while( numTransactions )
    {
        // sell random gear
        Gear gear = geoscape->generateGear( getCore()->getRandToolkit()->getUniform( 0, 1 ) > 0.75f );
        if( gear.isTradeable() ) geoscape->addGearToMarket( gear );
        numTransactions--;
    }
}