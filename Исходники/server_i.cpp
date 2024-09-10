int
Server_i::init (int &argc,
                ACE_TCHAR **argv)
{
  this->argc_ = argc;
  this->argv_ = argv;

  try
    {
      // First initialize the ORB, that will remove some arguments...
      this->orb_ =
        CORBA::ORB_init (this->argc_, this->argv_);

      // Get a reference to the RootPOA.
      CORBA::Object_var poa_object =
        this->orb_->resolve_initial_references ("RootPOA");

      // Narrow down to the correct reference.
      PortableServer::POA_var poa =
        PortableServer::POA::_narrow (poa_object.in ());

      // Set a POA Manager.
      PortableServer::POAManager_var poa_manager =
        poa->the_POAManager ();

      // Activate the POA Manager.
      poa_manager->activate ();

      CORBA::String_var ior;

      // Create the servant
      MCast_Server_i server_i;

      // Activate it to obtain the reference
      MCast::Server_var mcast_server =
        server_i._this ();

      CORBA::Object_var table_object =
        this->orb_->resolve_initial_references ("IORTable");

      IORTable::Table_var adapter =
        IORTable::Table::_narrow (table_object.in ());

      if (CORBA::is_nil (adapter.in ()))
        {
          ACE_ERROR ((LM_ERROR, "Nil IORTable\n"));
        }
      else
        {
          ior =
            this->orb_->object_to_string (mcast_server.in ());
          adapter->bind ("MCASTServer", ior.in ());
        }

      // Enable such that the server can listen for multicast requests
      // at the specified address.
      if (this->enable_multicast (ior.in ()) != 0)
        {
          ACE_ERROR ((LM_ERROR,
                      "ERROR: Unable to enable multicast "
                      "on specified address.\n"));

          throw CORBA::INTERNAL ();
        }

      // Run the ORB
      this->orb_->run ();

      //Destroy the POA, waiting until the destruction terminates.
      poa->destroy (1, 1);
      this->orb_->destroy ();
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("client");
      return 1;
    }

  return 0;
}