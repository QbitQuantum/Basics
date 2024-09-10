CORBA::Object_ptr
DAnCE_TargetManager_Module::init (CORBA::ORB_ptr orb,
                                  int argc,
                                  ACE_TCHAR *argv[])
{
  DANCE_TRACE ("DAnCE_TargetManager_Module::init");

  try
    {
      if (CORBA::is_nil(orb))
        {
          DANCE_ERROR (DANCE_LOG_TERMINAL_ERROR, (LM_ERROR, DLINFO ACE_TEXT ("DAnCE_TargetManager_Module::init - ")
                       ACE_TEXT ("Attempted to create Target Manager with a nil orb.\n")));
          return CORBA::Object::_nil();
        }
      else
        {
          this->orb_ = CORBA::ORB::_duplicate (orb);
        }

      if (ACE_OS::strcmp(orb->id(), this->orb_->id()) != 0)
        {
          DANCE_TRACE_LOG (DANCE_LOG_TRACE, (LM_TRACE, DLINFO ACE_TEXT ("DAnCE_TargetManager_Module::init - ")
                                             ACE_TEXT ("Resetting TM's orb.\n")));
          this->orb_ = CORBA::ORB::_duplicate (orb);
          this->domain_nc_ = CosNaming::NamingContext::_nil();
        }

      if (!this->parse_args (argc, argv))
        {
          return CORBA::Object::_nil ();
        }

      this->create_poas ();

      if (this->options_.domain_nc_)
        {
          try
            {
              DANCE_TRACE_LOG (DANCE_LOG_TRACE, (LM_TRACE, DLINFO ACE_TEXT ("DAnCE_TargetManager_Module::init - ")
                           ACE_TEXT ("Resolving DomainNC.\n")));
              CORBA::Object_var domain_obj = this->orb_->string_to_object (this->options_.domain_nc_);
              if (!CORBA::is_nil (domain_obj.in ()))
                {
                  this->domain_nc_ = CosNaming::NamingContext::_narrow (domain_obj.in());
                  if (CORBA::is_nil (this->domain_nc_.in ()))
                    {
                      DANCE_ERROR (DANCE_LOG_TERMINAL_ERROR, (LM_ERROR,DLINFO ACE_TEXT ("DAnCE_TargetManager_Module::init - ")
                                    ACE_TEXT ("Narrow to NamingContext return nil for DomainNC.\n")));
                      return CORBA::Object::_nil ();
                    }
                }
            }
          catch (CORBA::Exception&)
            {
              DANCE_DEBUG (DANCE_LOG_ERROR,
                           (LM_WARNING, DLINFO ACE_TEXT ("DAnCE_TargetManager_Module::init - ")
                             ACE_TEXT ("DomainNC context not found!\n")));
            }
        }


      DANCE_TRACE_LOG (DANCE_LOG_TRACE, (LM_TRACE, DLINFO ACE_TEXT ("DAnCE_TargetManager_Module::init - ")
                    ACE_TEXT ("Initializing the IOR Table\n")));
      // Initialize IOR table
      CORBA::Object_var table_object = orb->resolve_initial_references ("IORTable");

      IORTable::Table_var adapter = IORTable::Table::_narrow (table_object.in ());

      if (CORBA::is_nil (adapter.in ()))
        {
          DANCE_ERROR (DANCE_LOG_TERMINAL_ERROR, (LM_ERROR, DLINFO ACE_TEXT ("DAnCE_TargetManager_Module::init - ")
                         ACE_TEXT ("Unable to RIR the IORTable.\n")));
          return CORBA::Object::_nil ();
        }


      //Creating repository manager servant
      DAnCE::TargetManagerDaemon_i * rm = new DAnCE::TargetManagerDaemon_i (orb);

      PortableServer::ServantBase_var safe_svt (rm);

      ACE_CString repository_manager_oid;

      if (this->options_.name_ == 0)
        {
          repository_manager_oid = "TargetManager";
        }
      else
        {
          repository_manager_oid = ACE_TEXT_ALWAYS_CHAR (this->options_.name_);
          repository_manager_oid += ".TargetManager";
        }

      // Registering servant in poa
      PortableServer::ObjectId_var oid =
        PortableServer::string_to_ObjectId (repository_manager_oid.c_str());
      this->rm_poa_->activate_object_with_id (oid, rm);

      // Getting repository manager ior
      CORBA::Object_var nm_obj = this->rm_poa_->id_to_reference (oid.in ());
      CORBA::String_var ior = orb->object_to_string (nm_obj.in ());

      // Binding ior to IOR Table
      adapter->bind (repository_manager_oid.c_str (), ior.in ());

      // Binding repository manager to DomainNC
      if (!CORBA::is_nil (this->domain_nc_.in ()))
        {
          ACE_CString ns_name;
          if (this->options_.name_ == 0)
            {
              ns_name = "TargetManager";
            }
          else
            {
              ns_name = ACE_TEXT_ALWAYS_CHAR (this->options_.name_);
            }

          DANCE_DEBUG (DANCE_LOG_MINOR_EVENT,
                       (LM_TRACE, DLINFO ACE_TEXT ("DAnCE_TargetManager_Module::init - ")
                       ACE_TEXT ("Registering NM in NC as \"%C\".\n"), ns_name.c_str ()));
          CosNaming::Name name (1);
          name.length (1);
          name[0].id = CORBA::string_dup (ns_name.c_str ());
          name[0].kind = CORBA::string_dup ("TargetManager");
          this->domain_nc_->rebind (name, nm_obj.in ());
        }

      // Writing ior to file
      if (0 != this->options_.ior_file_)
        {
          DANCE_DEBUG (DANCE_LOG_MINOR_EVENT, (LM_TRACE,  DLINFO ACE_TEXT ("DAnCE_TargetManager_Module::init - ")
                        ACE_TEXT ("Writing RM IOR %C to file %C.\n"), this->options_.ior_file_, ior.in ()));
          if (!DAnCE::Target_Manager::write_IOR (this->options_.ior_file_, ior.in ()))
            DANCE_ERROR (DANCE_LOG_ERROR, (LM_ERROR, DLINFO ACE_TEXT ("DAnCE_TargetManager_Module::init - ")
                          ACE_TEXT ("Error: Unable to write IOR to file %C\n"),
                          this->options_.ior_file_));
        }

      // Activate POA manager
      PortableServer::POAManager_var mgr = this->root_poa_->the_POAManager ();
      mgr->activate ();

      // Finishing Deployment part
      DANCE_DEBUG (DANCE_LOG_MAJOR_EVENT, (LM_NOTICE, DLINFO ACE_TEXT ("DAnCE_TargetManager_Module::init - ")
                    ACE_TEXT ("DAnCE_TargetManager is running...\n")));

      DANCE_DEBUG (DANCE_LOG_MAJOR_DEBUG_INFO, (LM_DEBUG, DLINFO ACE_TEXT ("DAnCE_TargetManager_Module::init - ")
                    ACE_TEXT ("TargetManager IOR: %s\n"), ior.in ()));

      return nm_obj._retn ();
    }
  catch (const CORBA::Exception& ex)
    {
      DANCE_ERROR (DANCE_LOG_TERMINAL_ERROR,
                   (LM_EMERGENCY,
                    ACE_TEXT ("Caught CORBA Exception: %C\n"),
                    ex._info ().c_str ()));
      return CORBA::Object::_nil ();
    }
}