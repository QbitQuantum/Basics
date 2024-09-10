int
Manager::init (int argc, ACE_TCHAR *argv[])
{
  this->orb_ = CORBA::ORB_init (argc, argv);

  // Obtain the RootPOA.
  CORBA::Object_var obj_var =
    this->orb_->resolve_initial_references ("RootPOA");

  // Get the POA_var object from Object_var.
  PortableServer::POA_var root_poa_var =
    PortableServer::POA::_narrow (obj_var.in ());

  // Get the POAManager of the RootPOA.
  PortableServer::POAManager_var poa_manager_var =
    root_poa_var->the_POAManager ();

  poa_manager_var->activate ();

  // Policies for the childPOA to be created.
  CORBA::PolicyList policies (4);
  policies.length (4);

  // The next two policies are common to both
  // Id Assignment Policy
  policies[0] =
    root_poa_var->create_id_assignment_policy (PortableServer::USER_ID);

  // Lifespan policy
  policies[1] =
    root_poa_var->create_lifespan_policy (PortableServer::PERSISTENT);

  // Tell the POA to use a servant manager
  policies[2] =
    root_poa_var->create_request_processing_policy (PortableServer::USE_SERVANT_MANAGER);

  // Servant Retention Policy -> Use a locator
  policies[3] =
    root_poa_var->create_servant_retention_policy (PortableServer::NON_RETAIN);

  ACE_CString name = "newPOA";

  this->new_poa_var_ =
    root_poa_var->create_POA (name.c_str (),
                              poa_manager_var.in (),
                              policies);

  // Creation of childPOAs is over. Destroy the Policy objects.
  for (CORBA::ULong i = 0;
       i < policies.length ();
       ++i)
    {
      CORBA::Policy_ptr policy = policies[i];
      policy->destroy ();
    }

  return 0;
}