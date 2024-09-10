int
Event_Logging_Service::init (int argc, ACE_TCHAR *argv[])
{
  // initialize the ORB.
  this->init_ORB (argc, argv);

  if (this->parse_args (argc, argv) == -1)
    return -1;

  // Activate the event log factory
  ACE_NEW_THROW_EX (this->event_log_factory_,
                    TAO_EventLogFactory_i (),
                    CORBA::NO_MEMORY ());

  DsEventLogAdmin::EventLogFactory_var obj =
    this->event_log_factory_->activate (this->orb_.in (),
                                        this->poa_.in ());
  ACE_ASSERT (!CORBA::is_nil (obj.in ()));

  CORBA::String_var ior =
    this->orb_->object_to_string (obj.in ());

  if (true)
    {
      CORBA::Object_var table_object =
        this->orb_->resolve_initial_references ("IORTable");

      IORTable::Table_var adapter =
        IORTable::Table::_narrow (table_object.in ());

      adapter->bind("EventLogService", ior.in ());
    }

  if (this->ior_file_name_ != 0)
    {
      FILE* iorf = ACE_OS::fopen (this->ior_file_name_, ACE_TEXT("w"));
      if (iorf == 0)
        {
          ORBSVCS_ERROR_RETURN ((LM_ERROR,
                             "Cannot open output file for writing IOR: %s",
                             this->ior_file_name_),
                            -1);
        }
      ACE_OS::fprintf (iorf, "%s\n", ior.in ());
      ACE_OS::fclose (iorf);
    }

  if (this->pid_file_name_ != 0)
    {
      FILE* pidf = ACE_OS::fopen (this->pid_file_name_, ACE_TEXT("w"));
      if (pidf != 0)
        {
          ACE_OS::fprintf (pidf,
                           "%ld\n",
                           static_cast<long> (ACE_OS::getpid ()));
          ACE_OS::fclose (pidf);
        }
    }

  if (this->bind_to_naming_service_)
    {
      // Resolve the naming service.
      this->resolve_naming_service ();

      // Register the Event Log Factory.
      CosNaming::Name name (1);
      name.length (1);
      name[0].id = CORBA::string_dup (this->service_name_.c_str ());

      this->naming_->rebind (name, obj.in ());
    }

  return 0;
}