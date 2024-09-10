int main()
{
    try
    {
      
    ListeningManager<BetterTelnet, TelnetLogon> telnetlistener;
    ConnectionManager<BetterTelnet, TelnetLogon> telnetconnectionmanager( 128, 60, 65536 );

    telnetlistener.SetConnectionManager( &telnetconnectionmanager );
    telnetlistener.AddPort( 5110 );

    g_game.LoadAll();


    while( g_game.Running() )
    {
        telnetlistener.Listen();
        telnetconnectionmanager.Manage();
        g_game.ExecuteLoop();
        ThreadLib::YieldThread();

        
    }

    }

    catch( BetterMUD::Exception& e )
    {
        PyErr_Print();          // print python errors
        std::cout << e.GetError();
    }
    catch( std::exception& e )
    {
        // catch standard errors
    }
    catch( ... )
    {
        // catch all other errors
    }

    g_game.SaveAll();

    CharacterDB.Purge();
    ItemDB.Purge();
    AccountDB.Purge();
    RoomDB.Purge();
    PortalDB.Purge();
    RegionDB.Purge();

    return 0;
}