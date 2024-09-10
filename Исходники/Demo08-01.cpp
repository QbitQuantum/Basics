int main()
{
    try
    {
		ItemDatabase::Load();
		PlayerDatabase::Load();


		ListeningManager<Telnet, Logon> lm;
		ConnectionManager<Telnet, Logon> cm( 128, 60, 65536 );

		lm.SetConnectionManager( &cm );
		lm.AddPort( 5100 );

		Game::GetTimer().Reset();
		Game::Running() = true;

		while( Game::Running() )
		{
			lm.Listen();
			cm.Manage();
			ThreadLib::YieldThread();
		}
    
    }

    catch( SocketLib::Exception& e )
    {
        ERRORLOG.Log( "Fatal Socket Error: " + e.PrintError() );
    }

    catch( ThreadLib::Exception& )
    {
        ERRORLOG.Log( "Fatal Thread Error" );
    }

    catch( std::exception& e )
    {
        ERRORLOG.Log( "Standard Error: " + std::string( e.what() ) );
    }

    catch( ... )
    {
        ERRORLOG.Log( "Unspecified Error" );
    }

    // save the whole database.
    SimpleMUD::PlayerDatabase::Save();
}