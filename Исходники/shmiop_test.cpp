int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  try
    {
      CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

      ACE_Get_Opt opts (argc, argv, ACE_TEXT ("s:c:"));
      const ACE_TCHAR *server = 0, *client = 0;
      for (int o; (o = opts ()) != -1;)
        {
          switch (o)
            {
            case 's':
              server = opts.opt_arg ();
              break;
            case 'c':
              client = opts.opt_arg ();
              break;
            }
        }

      Servant srv (orb);
      ORBTask task (orb);

      if (server)
        {
          CORBA::Object_var obj = orb->resolve_initial_references ("RootPOA");
          PortableServer::POA_var poa = PortableServer::POA::_narrow (obj);
          PortableServer::POAManager_var pm = poa->the_POAManager ();
          pm->activate ();
          Test::Hello_var srv_obj = srv._this ();
          CORBA::String_var srv_str = orb->object_to_string (srv_obj);
          FILE *f = ACE_OS::fopen (server, "w");
          ACE_OS::fputs (srv_str, f);
          ACE_OS::fclose (f);
          if (!client)
            task.activate();
        }

      if (client)
        {
          ACE_CString ior ("file://");
          ior += ACE_TEXT_ALWAYS_CHAR (client);
          CORBA::Object_var obj = orb->string_to_object (ior.c_str ());
          Test::Hello_var hello = Test::Hello::_narrow (obj);
          CORBA::String_var str = hello->get_string ();
          ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%P|%t) - returned <%C>\n"),
                      str.in ()));
          hello->shutdown ();
        }
      else if (server)
        {
          task.wait ();
        }

      orb->destroy ();
      return 0;
    }
  catch (const CORBA::Exception &e)
    {
      e._tao_print_exception ("Exception caught:");
    }
  catch (...)
    {
      ACE_ERROR ((LM_ERROR, ACE_TEXT ("ERROR unknown exception ")
                            ACE_TEXT ("caught in main\n")));
    }
  return 1;
}