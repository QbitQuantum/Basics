void
handle_sigint
( int signal )
{
	std::cout << "\nGot Crtl-C" << std::endl;
	std::cerr << "..... unbind in NameService" << std::endl;

	//
	// unbind in naming service
	//
    CORBA::Object_var obj;
	CosNaming::NamingContext_var nameService;
	char hostname[256];
	gethostname(hostname, 256);
	CosNaming::Name name;
    name.length(3);
    name[0].id = CORBA::string_dup("Qedo");
    name[0].kind = CORBA::string_dup("");
	name[1].id = CORBA::string_dup("ComponentInstallation");
    name[1].kind = CORBA::string_dup("");
	name[2].id = CORBA::string_dup(hostname);
    name[2].kind = CORBA::string_dup("");
    try
    {
        obj = orb->resolve_initial_references("NameService");
		nameService = CosNaming::NamingContext::_narrow(obj.in());
		nameService->unbind(name);
    }
	catch (const CORBA::Exception&)
	{
		std::cerr << "..... could not unbind" << std::endl;
	}
	
	exit(1);
}