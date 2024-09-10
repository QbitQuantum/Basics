void
handle_sigint
( int sig )
{
#ifdef HAVE_SIGACTION
	 struct sigaction act;

    /* Assign sig_chld as our SIGINT handler */
    act.sa_handler = SIG_IGN;

    /* We don't want to block any other signals in this example */
    sigemptyset(&act.sa_mask);

	 sigaction(SIGINT,&act,0);
#else
	signal(sig, SIG_IGN);
#endif
	std::cout << "\nGot Crtl-C" << std::endl;
	std::cerr << "..... unbind in NameService" << std::endl;

	//
	// build name for name service
	//
    CORBA::Object_var obj;
	CosNaming::NamingContext_var nameService;
	CosNaming::Name name;
    name.length(2);
    name[0].id = CORBA::string_dup("Qedo");
    name[0].kind = CORBA::string_dup("");
	name[1].id = CORBA::string_dup("HomeFinder");
    name[1].kind = CORBA::string_dup("");
    
	//
	// unbind name in name service
	//
	try
	{
		//
		// try to get name service from config values
		//
		std::string ns = Qedo::ConfigurationReader::instance()->lookup_config_value( "/General/NameService" );
		if( !ns.empty() )
		{
			try
			{
				obj = orb->string_to_object( ns.c_str() );
			}
			catch(...)
			{
				NORMAL_ERR2( "qassf: can't resolve NameService ", ns );
			}

			NORMAL_OUT2( "qassf: NameService is ", ns );
		}
		//
		// try to get naming service from orb
		//
		else
		{
			try
			{
				obj = orb->resolve_initial_references( "NameService" );
			}
			catch (const CORBA::ORB::InvalidName&)
			{
				NORMAL_ERR( "qassf: can't resolve NameService from ORB" );
			}

			if (CORBA::is_nil(obj.in()))
			{
				NORMAL_ERR( "qassf: NameService is a nil object reference" );
			}
		}

		try
		{
			nameService = CosNaming::NamingContext::_narrow( obj.in() );
		}
		catch (const CORBA::Exception&)
		{
			NORMAL_ERR( "qassf: NameService is not running" );
		}

		if( CORBA::is_nil(nameService.in()) )
		{
			NORMAL_ERR( "qassf: NameService is not a NamingContext object reference" );
		}

		if (!CORBA::is_nil(nameService.in()))
		{
 			nameService->unbind(name);
		}
	}
	catch (const CORBA::Exception&)
	{
		std::cerr << "..... could not unbind" << std::endl;
	}
	catch(...)
	{
		std::cerr << "..... error in signal handler" << std::endl;
	}

	orb->shutdown(false);
}