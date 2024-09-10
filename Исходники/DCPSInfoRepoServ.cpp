void
InfoRepo::init()
{
  ACE_Argv_Type_Converter cvt(this->federatorConfig_.argc(),
                              this->federatorConfig_.argv());
  this->orb_ = CORBA::ORB_init(cvt.get_argc(), cvt.get_ASCII_argv(), "");

  this->info_servant_ =
    new TAO_DDS_DCPSInfo_i(this->orb_, this->resurrect_, this,
                           this->federatorConfig_.federationId());

  // Install the DCPSInfo_i into the Federator::Manager.
  this->federator_.info() = this->info_servant_.in();

  CORBA::Object_var obj =
    this->orb_->resolve_initial_references("RootPOA");
  PortableServer::POA_var root_poa = PortableServer::POA::_narrow(obj);

  PortableServer::POAManager_var poa_manager = root_poa->the_POAManager();

  // Use persistent and user id POA policies so the Info Repo's
  // object references are consistent.
  CORBA::PolicyList policies(2);
  policies.length(2);
  policies[0] = root_poa->create_id_assignment_policy(PortableServer::USER_ID);
  policies[1] = root_poa->create_lifespan_policy(PortableServer::PERSISTENT);
  PortableServer::POA_var info_poa = root_poa->create_POA("InfoRepo",
                                                          poa_manager,
                                                          policies);

  // Creation of the new POAs over, so destroy the Policy_ptr's.
  for (CORBA::ULong i = 0; i < policies.length(); ++i) {
    policies[i]->destroy();
  }

  PortableServer::ObjectId_var oid =
    PortableServer::string_to_ObjectId("InfoRepo");
  info_poa->activate_object_with_id(oid, this->info_servant_.in());
  obj = info_poa->id_to_reference(oid);
  // the object is created locally, so it is safe to do an
  // _unchecked_narrow, this was needed to prevent an exception
  // when dealing with ImR-ified objects
  OpenDDS::DCPS::DCPSInfo_var info_repo =
    OpenDDS::DCPS::DCPSInfo::_unchecked_narrow(obj);

  CORBA::String_var objref_str =
    orb_->object_to_string(info_repo);

  // Initialize the DomainParticipantFactory
  DDS::DomainParticipantFactory_var dpf =
    TheParticipantFactoryWithArgs(cvt.get_argc(),
                                  cvt.get_TCHAR_argv());

  // We need parse the command line options for DCPSInfoRepo after parsing DCPS specific
  // command line options.

  // Check the non-ORB arguments.
  this->parse_args(cvt.get_argc(), cvt.get_TCHAR_argv());

  // Activate the POA manager before initialize built-in-topics
  // so invocations can be processed.
  poa_manager->activate();

  if (this->use_bits_) {
    if (this->info_servant_->init_transport(this->listen_address_given_,
        this->listen_address_str_.c_str())
        != 0 /* init_transport returns 0 for success */) {
      ACE_ERROR((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: DCPSInfoRepo::init: ")
                 ACE_TEXT("Unable to initialize transport.\n")));
      throw InitError("Unable to initialize transport.");
    }

  } else {
    TheServiceParticipant->set_BIT(false);
  }

  // This needs to be done after initialization since we create the reference
  // to ourselves in the service here.
  OpenDDS::DCPS::Service_Participant* serv_part = TheServiceParticipant;
  serv_part->set_repo_ior(objref_str, OpenDDS::DCPS::Discovery::DEFAULT_REPO);

  OpenDDS::DCPS::Discovery_rch disc = serv_part->get_discovery(0 /*domainId*/);
  OpenDDS::DCPS::InfoRepoDiscovery_rch ird =
    OpenDDS::DCPS::static_rchandle_cast<OpenDDS::DCPS::InfoRepoDiscovery>(disc);
  if (!ird->set_ORB(orb_)) {
    ACE_ERROR((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: DCPSInfoRepo::init: ")
               ACE_TEXT("Unable to set the ORB in InfoRepoDiscovery.\n")));
    throw InitError("Unable to set the ORB in InfoRepoDiscovery.");
  }

  // Initialize persistence _after_ initializing the participant factory
  // and intializing the transport.
  if (!this->info_servant_->init_persistence()) {
    ACE_ERROR((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: DCPSInfoRepo::init: ")
               ACE_TEXT("Unable to initialize persistence.\n")));
    throw InitError("Unable to initialize persistence.");
  }

  // Initialize reassociation.
  if (this->reassociate_delay_ != ACE_Time_Value::zero &&
     !this->info_servant_->init_reassociation(this->reassociate_delay_)) {
    ACE_ERROR((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: DCPSInfoRepo::init: ")
               ACE_TEXT("Unable to initialize reassociation.\n")));
    throw InitError("Unable to initialize reassociation.");
  }

  // Initialize dispatch checking
  if (this->dispatch_cleanup_delay_ != ACE_Time_Value::zero &&
     !this->info_servant_->init_dispatchChecking(this->dispatch_cleanup_delay_)) {
    ACE_ERROR((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: DCPSInfoRepo::init: ")
               ACE_TEXT("Unable to initialize Dispatch checking.\n")));
    throw InitError("Unable to initialize dispatch checking.");
  }

  // Fire up the federator.
  OpenDDS::Federator::Manager_var federator;
  CORBA::String_var               federator_ior;

  if (federator_.id().overridden()) {
    oid = PortableServer::string_to_ObjectId("Federator");
    info_poa->activate_object_with_id(oid, &federator_);
    obj = info_poa->id_to_reference(oid);
    federator = OpenDDS::Federator::Manager::_narrow(obj);

    federator_ior = orb_->object_to_string(federator);

    // Add a local repository reference that can be returned via a
    // remote call to a peer.
    this->federator_.localRepo(info_repo);

    // It should be safe to initialize the federation mechanism at this
    // point.  What we really needed to wait for is the initialization of
    // the service components - like the DomainParticipantFactory and the
    // repository bindings.
    // N.B. This is done *before* being added to the IOR table to avoid any
    //      races with an eager client.
    this->federator_.orb(this->orb_);

    //
    // Add the federator to the info_servant update manager as an
    // additional updater interface to be called.
    // N.B. This needs to be done *after* the call to load_domains()
    //      since that is where the update manager is initialized in the
    //      info startup sequencing.
    this->info_servant_->add(&this->federator_);
  }

  // Grab the IOR table.
  CORBA::Object_var table_object =
    this->orb_->resolve_initial_references("IORTable");

  IORTable::Table_var adapter = IORTable::Table::_narrow(table_object);

  if (CORBA::is_nil(adapter)) {
    ACE_ERROR((LM_ERROR, ACE_TEXT("Nil IORTable\n")));

  } else {
    adapter->bind(OpenDDS::Federator::REPOSITORY_IORTABLE_KEY, objref_str);

    if (this->federator_.id().overridden()) {
      // Bind to '/Federator'
      adapter->bind(OpenDDS::Federator::FEDERATOR_IORTABLE_KEY, federator_ior);

      // Bind to '/Federator/1382379631'
      std::stringstream buffer(OpenDDS::Federator::FEDERATOR_IORTABLE_KEY);
      buffer << "/" << std::dec << this->federatorConfig_.federationDomain();
      adapter->bind(buffer.str().c_str(), federator_ior);
    }
  }

  FILE* output_file = ACE_OS::fopen(this->ior_file_.c_str(), ACE_TEXT("w"));

  if (output_file == 0) {
    ACE_ERROR((LM_ERROR, ACE_TEXT("ERROR: Unable to open IOR file: %s\n"),
               ior_file_.c_str()));
    throw InitError("Unable to open IOR file.");
  }

  ACE_OS::fprintf(output_file, "%s", objref_str.in());
  ACE_OS::fclose(output_file);

  // Initial federation join if specified on command line.
  if (this->federator_.id().overridden()
       && !this->federatorConfig_.federateIor().empty()) {
    if (OpenDDS::DCPS::DCPS_debug_level > 0) {
      ACE_DEBUG((LM_DEBUG,
                 ACE_TEXT("(%P|%t) INFO: DCPSInfoRepo::init() - ")
                 ACE_TEXT("joining federation with repository %s\n"),
                 this->federatorConfig_.federateIor().c_str()));
    }

    obj = this->orb_->string_to_object(
          this->federatorConfig_.federateIor().c_str());

    if (CORBA::is_nil(obj)) {
      ACE_ERROR((LM_ERROR,
                 ACE_TEXT("(%P|%t) ERROR: could not resolve %s for initial federation.\n"),
                 this->federatorConfig_.federateIor().c_str()));
      throw InitError("Unable to resolve IOR for initial federation.");
    }

    OpenDDS::Federator::Manager_var peer =
      OpenDDS::Federator::Manager::_narrow(obj);

    if (CORBA::is_nil(peer)) {
      ACE_ERROR((LM_ERROR,
                 ACE_TEXT("(%P|%t) ERROR: could not narrow %s.\n"),
                 this->federatorConfig_.federateIor().c_str()));
      throw InitError("Unable to narrow peer for initial federation.");
    }

    // Actually join.
    peer->join_federation(federator,
                          this->federatorConfig_.federationDomain());
  }
}