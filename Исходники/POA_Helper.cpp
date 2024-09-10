void
TAO_Notify_POA_Helper::set_policy (PortableServer::POA_ptr parent_poa, CORBA::PolicyList &policy_list)
{
  policy_list.length (2);

  policy_list[0] =
    parent_poa->create_id_uniqueness_policy (PortableServer::UNIQUE_ID);

  policy_list[1] =
    parent_poa->create_id_assignment_policy (PortableServer::USER_ID);
}