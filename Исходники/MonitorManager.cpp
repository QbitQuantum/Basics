int
TAO_MonitorManager::ORBTask::svc (void)
{
  try
    {
      if (CORBA::is_nil (this->orb_.in ()))
        {
          ORBSVCS_ERROR_RETURN ((LM_ERROR,
                             "(%P|%t) TAO_MonitorManager: Unable to "
                             "initialize the ORB\n"),
                            1);
        }

      PortableServer::POA_var poa;

      {
        ACE_GUARD_RETURN (TAO_SYNCH_MUTEX, guard, this->mutex_, -1);

        CORBA::Object_var obj =
          this->orb_->resolve_initial_references ("RootPOA");

        poa = PortableServer::POA::_narrow (obj.in ());

        if (CORBA::is_nil (poa.in ()))
          {
            ORBSVCS_ERROR_RETURN ((LM_ERROR,
                               "(%P|%t) TAO_MonitorManager: Unable to "
                               "resolve the RootPOA\n"),
                              1);
          }

        PortableServer::POAManager_var poa_manager = poa->the_POAManager ();
        poa_manager->activate ();

        // Activate the object
        NotificationServiceMonitor_i* servant;
        ACE_NEW_RETURN (servant,
                        NotificationServiceMonitor_i (this->orb_.in ()), 1);
        PortableServer::ServantBase_var owner_transfer(servant);
        PortableServer::ObjectId_var id = poa->activate_object (servant);

        // Register the object with the IORTable
        obj = poa->id_to_reference (id.in ());
        CosNotification::NotificationServiceMonitorControl_var monitor =
          CosNotification::NotificationServiceMonitorControl::_narrow (obj.in ());
        CORBA::String_var ior = this->orb_->object_to_string (monitor.in ());
        obj = this->orb_->resolve_initial_references ("IORTable");
        IORTable::Table_var iortable = IORTable::Table::_narrow (obj.in ());

        if (CORBA::is_nil (iortable.in ()))
          {
            ORBSVCS_ERROR_RETURN ((LM_ERROR,
                               "(%P|%t) TAO_MonitorManager: Unable to "
                               "resolve the IORTable\n"),
                              1);
          }

        iortable->bind(ACE_TEXT_ALWAYS_CHAR(mc_orb_name_.c_str()), ior.in ());

        if (this->use_name_svc_)
          {
            TAO_Naming_Client nc;
            nc.init (this->orb_.in ());
            CosNaming::Name name (1);
            name.length (1);
            name[0].id = CORBA::string_dup (ACE_TEXT_ALWAYS_CHAR(mc_orb_name_.c_str()));
            nc->rebind (name, monitor.in ());
          }

        if (this->ior_output_.length () > 0)
          {
            FILE* fp = ACE_OS::fopen (this->ior_output_.c_str (), "w");

            if (fp == 0)
              {
                ORBSVCS_ERROR_RETURN ((LM_ERROR,
                                   ACE_TEXT ("(%P|%t) TAO_MonitorManager: "
                                   ACE_TEXT ("Unable to write to %s\n")),
                                   this->ior_output_.c_str ()),
                                  1);
              }
            else
              {
                ACE_OS::fprintf (fp, "%s", ior.in ());
                ACE_OS::fclose (fp);
              }
          }
      }

      // R1: race condition (partially fixed):
      // TAO_MonitorManager::fini() is called directly after
      // TAO_MonitorManager::run(), the shutdown call on the ORB could
      // happen but the ORB::run() loop won't exit.
      startup_barrier_.wait ();
      this->orb_->run ();

      ACE_GUARD_RETURN (TAO_SYNCH_MUTEX, guard, this->mutex_, -1);

      // Destroy the POA and ORB
      if (!CORBA::is_nil (poa.in ()))
        {
          poa->destroy (true, true);
        }

      this->orb_->destroy ();

      // Set to nil to avoid double shutdown in TAO_MonitorManager::fini()
      this->orb_ = CORBA::ORB::_nil ();
    }
  catch (const CORBA::Exception& ex)
    {
      if (!CORBA::is_nil (this->orb_.in ()))
        {
          try
            {
              this->orb_->shutdown ();
            }
          catch (...)
            {
            }

          this->orb_ = CORBA::ORB::_nil ();
        }

      ex._tao_print_exception ("Caught in "
                               "TAO_MonitorManager::ORBTask::svc");
    }
  catch (...)
    {
      if (!CORBA::is_nil (this->orb_.in ()))
        {
          try
            {
              this->orb_->shutdown ();
            }
          catch (...)
            {
            }
          this->orb_ = CORBA::ORB::_nil ();
        }

      ORBSVCS_ERROR ((LM_ERROR,
                  "Unexpected exception type caught "
                  "in TAO_MonitorManager::ORBTask::svc"));
    }

  return 0;
}