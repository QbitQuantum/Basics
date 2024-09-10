int
TAO_IFR_Server::create_poa (void)
{
  PortableServer::POAManager_var poa_manager =
    this->root_poa_->the_POAManager ();

  poa_manager->activate ();

  CORBA::PolicyList policies (5);
  policies.length (5);

  // ID Assignment Policy.
  policies[0] =
    this->root_poa_->create_id_assignment_policy (PortableServer::USER_ID);

  // Lifespan Policy.
  policies[1] =
    this->root_poa_->create_lifespan_policy (PortableServer::PERSISTENT);

  // Request Processing Policy.
  policies[2] =
    this->root_poa_->create_request_processing_policy (
        PortableServer::USE_DEFAULT_SERVANT
      );

  // Servant Retention Policy.
  policies[3] =
    this->root_poa_->create_servant_retention_policy (
        PortableServer::NON_RETAIN
      );

  // Id Uniqueness Policy.
  policies[4] =
    this->root_poa_->create_id_uniqueness_policy (
        PortableServer::MULTIPLE_ID
      );

  this->repo_poa_ =
    this->root_poa_->create_POA ("repoPOA",
                                 poa_manager.in (),
                                 policies);

  policies[0]->destroy ();

  return 0;
}