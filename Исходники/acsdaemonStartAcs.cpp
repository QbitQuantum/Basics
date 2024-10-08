int main(int argc, char *argv[])
{
    int c, instance = -1;
    ACE_CString daemonRef;
    ACE_CString hostName;
    ACE_CString additional;
    for (;;) {
	int option_index = 0;
	c = getopt_long(argc, argv, "hi:d:H:a:",
			long_options, &option_index);
	if (c == -1)
	    break;
	switch (c) {
	case 'h':
	    usage(argv[0]);
	    return 0;
	case 'i':
	    instance = ACE_OS::atoi(optarg);
	    break;
	case 'd':
	    daemonRef = optarg;
	    break;
	case 'H':
	    hostName = optarg;
	    break;
	case 'a':
	    additional = optarg;
	    break;
	}
    }
    if (instance == -1) {
	ACE_OS::printf("Error: instance is a mandatory option try %s -h\n",
		       argv[0]);
	return -1;
    }

	#define DEFAULT_LOG_FILE_NAME "acs_local_log"
	ACE_CString daemonsLogFileName = getTempFileName(0, DEFAULT_LOG_FILE_NAME);

	// replace "ACS_INSTANCE.x" with "acsdaemonStartAcs_" + <timestamp>
	ACE_CString daemonsDir = "acsdaemonStartAcs_" + getStringifiedTimeStamp();

	ACE_CString instancePart("ACS_INSTANCE.");
	ACE_CString::size_type pos = daemonsLogFileName.find(instancePart);
	daemonsLogFileName =
			daemonsLogFileName.substring(0, pos) +
			daemonsDir +
			daemonsLogFileName.substring(pos + instancePart.length() + 1);	// +1 for skipping instance number

	ACE_OS::setenv("ACS_LOG_FILE", daemonsLogFileName.c_str(), 1);

	LoggingProxy *logger = new LoggingProxy(0, 0, 31);
    if (logger) {
	LoggingProxy::init(logger);
	LoggingProxy::ProcessName(argv[0]);
	LoggingProxy::ThreadName("main");
    } else
	ACS_SHORT_LOG((LM_INFO, "Failed to initialize logging."));

    StartCallback* sc = new StartCallback();

    try {
	// Initialize the ORB.
	CORBA::ORB_var orb = CORBA::ORB_init(argc, argv, "TAO");

	// get a reference to the RootPOA
	CORBA::Object_var pobj = orb->resolve_initial_references("RootPOA");
	PortableServer::POA_var root_poa = PortableServer::POA::_narrow(pobj.in());
	PortableServer::POAManager_var poa_manager = root_poa->the_POAManager();
      
	// create policies
	CORBA::PolicyList policy_list;
	policy_list.length(5);
	policy_list[0] = root_poa->create_request_processing_policy(PortableServer::USE_DEFAULT_SERVANT);
	policy_list[1] = root_poa->create_id_uniqueness_policy(PortableServer::MULTIPLE_ID);
	policy_list[2] = root_poa->create_id_assignment_policy(PortableServer::USER_ID); 
	policy_list[3] = root_poa->create_servant_retention_policy(PortableServer::NON_RETAIN); 
	policy_list[4] = root_poa->create_lifespan_policy(PortableServer::PERSISTENT);
      
	// create a ACSDaemon POA with policies 
	PortableServer::POA_var poa = root_poa->create_POA("DaemonCallback", poa_manager.in(), policy_list);

	// destroy policies
	for (CORBA::ULong i = 0; i < policy_list.length(); ++i)
	    {
	    CORBA::Policy_ptr policy = policy_list[i];
	    policy->destroy();
	    }

	// set as default servant
	poa->set_servant(sc);

	// create reference
	PortableServer::ObjectId_var oid = PortableServer::string_to_ObjectId("DaemonCallback");
	pobj = poa->create_reference_with_id (oid.in(), sc->_interface_repository_id());
	CORBA::String_var m_ior = orb->object_to_string(pobj.in());

	// bind to IOR table
      	CORBA::Object_var table_object = orb->resolve_initial_references("IORTable");
	IORTable::Table_var adapter = IORTable::Table::_narrow(table_object.in());
      
	if (CORBA::is_nil(adapter.in()))
	    {
	    ACS_SHORT_LOG ((LM_ERROR, "Nil IORTable"));
	    return -1;
	    }
	else
	    {
	    adapter->bind("DaemonCallback", m_ior.in());
	    }

	// activate POA
	poa_manager->activate();

	ACS_SHORT_LOG((LM_INFO, "%s is waiting for incoming requests.", "DaemonCallback"));


	// construct default one
	if (daemonRef.length() == 0) {
	    if (hostName.length() == 0) {
		hostName = ACSPorts::getIP();
	    }
	    daemonRef = "corbaloc::";
	    daemonRef =
		daemonRef + hostName + ":" +
		ACSPorts::getServicesDaemonPort().c_str() +
		"/" + ::acsdaemon::servicesDaemonServiceName;
	    ACS_SHORT_LOG((LM_INFO,
			   "Using local ACS Services Daemon reference: '%s'",
			   daemonRef.c_str()));

	} else {
	    ACS_SHORT_LOG((LM_INFO,
			   "ACS Services Daemon reference obtained via command line: '%s'",
			   daemonRef.c_str()));
	}

	CORBA::Object_var obj = orb->string_to_object(daemonRef.c_str());
	if (CORBA::is_nil(obj.in())) {
	    ACS_SHORT_LOG((LM_INFO, "Failed to resolve reference '%s'.",
			   daemonRef.c_str()));
	    return -1;
	}

	acsdaemon::ServicesDaemon_var daemon =
	    acsdaemon::ServicesDaemon::_narrow(obj.in());
	if (CORBA::is_nil(daemon.in())) {
	    ACS_SHORT_LOG((LM_INFO, "Failed to narrow reference '%s'.",
			   daemonRef.c_str()));
	    return -1;
	}

	// @todo implement support for callback and wait for completion call
	acsdaemon::DaemonSequenceCallback_var dummyCallback = sc->_this();
	ACS_SHORT_LOG((LM_INFO, "Calling start_acs(%d, %s, dummyCallback).", instance,
		       additional.c_str()));
	daemon->start_acs(dummyCallback.in(), instance, additional.c_str());
	ACS_SHORT_LOG((LM_INFO, "ACS start message issued."));

	while(!sc->isComplete())
	{
	    if (orb->work_pending())
	        orb->perform_work();
	}
    }
    catch(ACSErrTypeCommon::BadParameterEx & ex) {
	ACSErrTypeCommon::BadParameterExImpl exImpl(ex);
	exImpl.log();
	return -1;
    }
    catch(CORBA::Exception & ex) {

	ACS_SHORT_LOG((LM_INFO, "Failed."));
	ex._tao_print_exception("Caught unexpected exception:");
	return -1;
    }

    return 0;
}