int
Airplane_Server_i::init (int argc, ACE_TCHAR** argv)
{
  try
    {
      // Initialize the ORB
      this->orb_ = CORBA::ORB_init (argc, argv);

      // Save pointers to the command line arguments
      this->argc_ = argc;
      this->argv_ = argv;

      // Now check the arguments for our options
      int retval = this->parse_args ();

      if (retval != 0)
        return retval;

      // Get the POA from the ORB.
      CORBA::Object_var obj =
        this->orb_->resolve_initial_references ("RootPOA");
      ACE_ASSERT(! CORBA::is_nil (obj.in ()));

      // Narrow the object to a POA.
      root_poa_ = PortableServer::POA::_narrow (obj.in ());

      // Get the POA_Manager.
      this->poa_manager_ = this->root_poa_->the_POAManager ();

      // We now need to create a POA with the persistent and user_id policies,
      // since they are need for use with the Implementation Repository.

      CORBA::PolicyList policies (2);
      policies.length (2);

      policies[0] =
        this->root_poa_->create_id_assignment_policy (PortableServer::USER_ID);

      policies[1] =
        this->root_poa_->create_lifespan_policy (PortableServer::PERSISTENT);

      // Since the Implementation Repository keys off of the POA name, we need
      // to use the server_name_ as the POA's name.
      this->airplane_poa_ =
        this->root_poa_->create_POA (this->server_name_.c_str(),
                                     this->poa_manager_.in (),
                                     policies);

      // Creation of the new POA is over, so destroy the Policy_ptr's.
      for (CORBA::ULong i = 0; i < policies.length (); ++i)
        {
          CORBA::Policy_ptr policy = policies[i];
          policy->destroy ();
        }

      ACE_NEW_RETURN (this->server_impl_, Airplane_i, -1);

      PortableServer::ObjectId_var server_id =
        PortableServer::string_to_ObjectId ("server");

      this->airplane_poa_->activate_object_with_id (server_id.in (),
                                                    this->server_impl_);

      obj = this->airplane_poa_->id_to_reference (server_id.in ());
      CORBA::String_var ior =
        this->orb_->object_to_string (obj.in ());
      if (TAO_debug_level > 0)
        ACE_DEBUG ((LM_DEBUG, "The ImRified IOR is: <%C>\n", ior.in ()));

      TAO_Root_POA* tmp_poa = dynamic_cast<TAO_Root_POA*>(airplane_poa_.in());
      obj = tmp_poa->id_to_reference_i (server_id.in (), false);
      CORBA::String_var plain_ior =
        this->orb_->object_to_string (obj.in ());
      if (TAO_debug_level > 0)
        ACE_DEBUG ((LM_DEBUG, "The plain IOR is: <%C>\n", plain_ior.in ()));

      // Note : The IORTable will only be used for those clients who try to
      // invoke indirectly using a simple object_key reference
      // like "corbaloc::localhost:8888/airplane_server".
      obj = this->orb_->resolve_initial_references ("IORTable");

      IORTable::Table_var adapter =
        IORTable::Table::_narrow (obj.in ());
      ACE_ASSERT(! CORBA::is_nil (adapter.in ()));
      adapter->bind (this->server_name_.c_str(), plain_ior.in ());

      this->poa_manager_->activate ();

      if (this->ior_output_file_)
        {
          ACE_OS::fprintf (this->ior_output_file_, "%s", ior.in ());
          ACE_OS::fclose (this->ior_output_file_);
        }

      if (this->pid_output_file_)
        {
          int pid = static_cast<int> (ACE_OS::getpid ());
          ACE_OS::fprintf (this->pid_output_file_, "%d\n", pid);
          ACE_OS::fclose (this->pid_output_file_);
        }
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("Airplane_Server_i::init");
      throw;
    }

  return 0;
}