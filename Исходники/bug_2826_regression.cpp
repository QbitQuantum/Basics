int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  CORBA::ORB_var orb;
  try
  {
    orb = CORBA::ORB_init (argc, argv);

    CORBA::Object_var root_poa_o =
      orb->resolve_initial_references ("RootPOA");

    PortableServer::POA_var rootPOA =
      PortableServer::POA::_narrow (root_poa_o.in ());

    if (CORBA::is_nil (rootPOA.in ()))
      {
        ACE_ERROR_RETURN ((LM_ERROR,
        " (%P|%t) Panic: nil RootPOA\n"), 1);
      }

    PortableServer::POAManager_var poaMgr = rootPOA->the_POAManager ();

    poaMgr->activate ();

    CORBA::PolicyList policies;
    policies.length (3);
    policies[0] = rootPOA->create_id_assignment_policy (
      PortableServer::SYSTEM_ID);
    policies[1] = rootPOA->create_implicit_activation_policy (
      PortableServer::NO_IMPLICIT_ACTIVATION);
    policies[2] = rootPOA->create_lifespan_policy (
      PortableServer::TRANSIENT);

    PortableServer::POA_var fooPoa = rootPOA->create_POA (
      "FOO_POA", poaMgr.in (), policies );

    for (CORBA::ULong i = 0; i < policies.length (); ++i)
    {
      policies[i]->destroy ();
    }

    Foo_i servant;
    PortableServer::ObjectId_var oid = fooPoa->activate_object( &servant );

    CORBA::Object_var obj = fooPoa->id_to_reference (oid.in ());

    foo_var client = foo::_narrow (obj.in());

    client->check();

    if (vc_check(client.in()))
    {
      orb->destroy();
      return 1;
    }

    fooPoa->deactivate_object (oid.in () );  //servant is gone

    if (vc_check(client.in(), false))  //exception expected
    {
      orb->destroy();
      return 2;
    }
  }
  catch(...)
  {
    return 3;
  }
  return 0;
}