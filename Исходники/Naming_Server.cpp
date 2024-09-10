int
TAO_Naming_Server::init_new_naming (CORBA::ORB_ptr orb,
                                    PortableServer::POA_ptr poa,
                                    const ACE_TCHAR *persistence_location,
                                    void *base_addr,
                                    size_t context_size,
                                    int enable_multicast,
                                    int use_storable_context,
                                    int round_trip_timeout,
                                    int use_round_trip_timeout)
{
  try
    {
#if defined (CORBA_E_MICRO)
      ACE_UNUSED_ARG (persistence_location);
      ACE_UNUSED_ARG (base_addr);
      ACE_UNUSED_ARG (use_storable_context);
#else
      if (use_storable_context)
        {
          // In lieu of a fully implemented service configurator version
          // of this Reader and Writer, let's just take something off the
          // command line for now.
          TAO::Storable_Factory* pf = 0;
          ACE_CString directory (ACE_TEXT_ALWAYS_CHAR (persistence_location));
          ACE_NEW_RETURN (pf, TAO::Storable_FlatFileFactory (directory), -1);
          auto_ptr<TAO::Storable_Factory> persFactory(pf);

          // Use an auto_ptr to ensure that we clean up the factory in the case
          // of a failure in creating and registering the Activator.
          TAO_Storable_Naming_Context_Factory* cf =
            this->storable_naming_context_factory (context_size);
          // Make sure we got a factory
          if (cf == 0) return -1;
          auto_ptr<TAO_Storable_Naming_Context_Factory> contextFactory (cf);

          // This instance will either get deleted after recreate all or,
          // in the case of a servant activator's use, on destruction of the
          // activator.

          // Was a location specified?
          if (persistence_location == 0)
            {
              // No, assign the default location "NameService"
              persistence_location = ACE_TEXT ("NameService");
            }

          // Now make sure this directory exists
          if (ACE_OS::access (persistence_location, W_OK|X_OK))
            {
              ORBSVCS_ERROR_RETURN ((LM_ERROR, "Invalid persistence directory\n"), -1);
            }

#if (TAO_HAS_MINIMUM_POA == 0) && !defined (CORBA_E_COMPACT)
          if (this->use_servant_activator_)
            {
              ACE_NEW_THROW_EX (this->servant_activator_,
                                TAO_Storable_Naming_Context_Activator (orb,
                                                                       persFactory.get(),
                                                                       contextFactory.get (),
                                                                       persistence_location),
                                CORBA::NO_MEMORY ());
              this->ns_poa_->set_servant_manager(this->servant_activator_);
            }
#endif /* TAO_HAS_MINIMUM_POA */
          try {  // The following might throw an exception.
            this->naming_context_ =
              TAO_Storable_Naming_Context::recreate_all (orb,
              poa,
              TAO_ROOT_NAMING_CONTEXT,
              context_size,
              0,
              contextFactory.get (),
              persFactory.get (),
              use_redundancy_);
          }
          catch (const CORBA::Exception& ex)
          {
            // The activator already took over the factories so we need to release the auto_ptr
            if (this->use_servant_activator_)
            {
              // The context factory is now owned by the activator
              // so we should release it
              contextFactory.release ();
              // If using a servant activator, the activator now owns the
              // factory, so we should release it
              persFactory.release ();
            }
            // Print out the exception and return failure
            ex._tao_print_exception (
              "TAO_Naming_Server::init_new_naming");
            return -1;
          }

        // Kind of a duplicate of the above here, but we must also release the
        // factory autoptrs in the good case as well.
        if (this->use_servant_activator_)
            {
              // The context factory is now owned by the activator
              // so we should release it
              contextFactory.release ();
              // If using a servant activator, the activator now owns the
              // factory, so we should release it
              persFactory.release ();
            }

      }
      else if (persistence_location != 0)
        //
        // Initialize Persistent Naming Service.
        //
        {

          // Create Naming Context Implementation Factory to be used for the creation of
          // naming contexts by the TAO_Persistent_Context_Index
          TAO_Persistent_Naming_Context_Factory *naming_context_factory =
            this->persistent_naming_context_factory ();
          // Make sure we got a factory.
          if (naming_context_factory == 0) return -1;

          // Allocate and initialize Persistent Context Index.
          ACE_NEW_RETURN (this->context_index_,
                          TAO_Persistent_Context_Index (orb, poa, naming_context_factory),
                          -1);

          if (this->context_index_->open (persistence_location,
                                          base_addr) == -1
              || this->context_index_->init (context_size) == -1)
            {
              if (TAO_debug_level >0)
                ORBSVCS_DEBUG ((LM_DEBUG,
                            "TAO_Naming_Server: context_index initialization failed\n"));
              return -1;
            }

          // Set the root Naming Context reference.
          this->naming_context_ =
            this->context_index_->root_context ();
        }
      else
#endif /* CORBA_E_MICRO */
        {
          //
          // Initialize Transient Naming Service.
          //
          this->naming_context_ =
            TAO_Transient_Naming_Context::make_new_context (poa,
                                                            TAO_ROOT_NAMING_CONTEXT,
                                                            context_size);

        }

#if !defined (CORBA_E_MICRO)
      // Register with the ORB's resolve_initial_references()
      // mechanism.  Primarily useful for dynamically loaded Name
      // Services.
      orb->register_initial_reference ("NameService",
                                       this->naming_context_.in ());
#endif /* CORBA_E_MICRO */

      // Set the ior of the root Naming Context.
      this->naming_service_ior_=
        orb->object_to_string (this->naming_context_.in ());

      CORBA::Object_var table_object =
        orb->resolve_initial_references ("IORTable");

      IORTable::Table_var adapter =
        IORTable::Table::_narrow (table_object.in ());
      if (CORBA::is_nil (adapter.in ()))
        {
          ORBSVCS_ERROR ((LM_ERROR, "Nil IORTable\n"));
        }
      else
        {
          CORBA::String_var ior =
            orb->object_to_string (this->naming_context_.in ());
          adapter->bind ("NameService", ior.in ());
        }

#if defined (ACE_HAS_IP_MULTICAST)
      if (enable_multicast)
        {
          // @@ Marina: is there anyway to implement this stuff
          // without using ORB_Core_instance()? For example can you
          // pass the ORB as an argument?

          //
          // Install ior multicast handler.
          //
          // Get reactor instance from TAO.
          ACE_Reactor *reactor = orb->orb_core()->reactor ();

          // See if the -ORBMulticastDiscoveryEndpoint option was specified.
          ACE_CString mde (orb->orb_core ()->orb_params ()->mcast_discovery_endpoint ());

          // First, see if the user has given us a multicast port number
          // on the command-line;
          u_short port =
            orb->orb_core ()->orb_params ()->service_port (TAO::MCAST_NAMESERVICE);

          if (port == 0)
            {
              // Check environment var. for multicast port.
              const char *port_number =
                ACE_OS::getenv ("NameServicePort");

              if (port_number != 0)
                port = static_cast<u_short> (ACE_OS::atoi (port_number));
            }

          // Port wasn't specified on the command-line or in environment -
          // use the default.
          if (port == 0)
            port = TAO_DEFAULT_NAME_SERVER_REQUEST_PORT;

          // Instantiate a handler which will handle client requests for
          // the root Naming Context ior, received on the multicast port.
          ACE_NEW_RETURN (this->ior_multicast_,
                          TAO_IOR_Multicast (),
                          -1);

          if (mde.length () != 0)
            {
              if (this->ior_multicast_->init (this->naming_service_ior_.in (),
                                              mde.c_str (),
                                              TAO_SERVICEID_NAMESERVICE) == -1)
                return -1;
            }
          else
            {
              if (this->ior_multicast_->init (this->naming_service_ior_.in (),
                                              port,
#if defined (ACE_HAS_IPV6)
                                              ACE_DEFAULT_MULTICASTV6_ADDR,
#else
                                              ACE_DEFAULT_MULTICAST_ADDR,
#endif /* ACE_HAS_IPV6 */
                                              TAO_SERVICEID_NAMESERVICE) == -1)
                return -1;
            }

          // Register event handler for the ior multicast.
          if (reactor->register_handler (this->ior_multicast_,
                                         ACE_Event_Handler::READ_MASK) == -1)
            {
              if (TAO_debug_level > 0)
                ORBSVCS_DEBUG ((LM_DEBUG,
                            "TAO_Naming_Server: cannot register Event handler\n"));
              return -1;
            }

          if (TAO_debug_level > 0)
            ORBSVCS_DEBUG ((LM_DEBUG,
                        "TAO_Naming_Server: The multicast server setup is done.\n"));
        }
#else
  ACE_UNUSED_ARG (enable_multicast);
#endif /* ACE_HAS_IP_MULTICAST */

#if defined (TAO_HAS_CORBA_MESSAGING) && TAO_HAS_CORBA_MESSAGING != 0
      if (use_round_trip_timeout == 1)
      {
        TimeBase::TimeT roundTripTimeoutVal = round_trip_timeout;
        CORBA::Any anyObjectVal;
        anyObjectVal <<= roundTripTimeoutVal;
        CORBA::PolicyList polList (1);
        polList.length (1);
        polList[0] = orb->create_policy (Messaging::RELATIVE_RT_TIMEOUT_POLICY_TYPE,
                                         anyObjectVal);

        // set a timeout on the orb
        //
        CORBA::Object_var orbPolicyManagerObj =
          orb->resolve_initial_references ("ORBPolicyManager");

        CORBA::PolicyManager_var orbPolicyManager =
          CORBA::PolicyManager::_narrow (orbPolicyManagerObj.in ());
        orbPolicyManager->set_policy_overrides (polList, CORBA::SET_OVERRIDE);

        polList[0]->destroy ();
        polList[0] = CORBA::Policy::_nil ();
      }
#else
  ACE_UNUSED_ARG (use_round_trip_timeout);
  ACE_UNUSED_ARG (round_trip_timeout);
#endif /* TAO_HAS_CORBA_MESSAGING */
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception (
        "TAO_Naming_Server::init_new_naming");
      return -1;
    }

  return 0;
}