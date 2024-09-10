POA_ptr createPersistPOA(const char* name, POA_ptr root_poa, POAManager_ptr poaman) {
  CORBA::PolicyList policies (2);
  policies.length (2);
  policies[0] = root_poa->create_id_assignment_policy(USER_ID);
  policies[1] = root_poa->create_lifespan_policy(PERSISTENT);
  POA_var poa = root_poa->create_POA(name, poaman, policies);
  policies[0]->destroy();
  policies[1]->destroy();
  return poa._retn();
}