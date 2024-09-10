    RTT_CORBA_API bool ApplicationServer::InitOrb(int argc, char* argv[], Seconds timeout ) {
      
        if ( !CORBA::is_nil(orb) ){
	  return false;
	}
        try {
            // First initialize the ORB, that will remove some arguments...
            orb =
                CORBA::ORB_init (argc, const_cast<char**>(argv),
                                 "omniORB4");
            if(timeout >= 0.1e-7)
            {
#if defined( CORBA_IS_TAO ) && defined( CORBA_TAO_HAS_MESSAGING )
                // Set the timeout value as a TimeBase::TimeT (100 nanosecond units)
                // and insert it into a CORBA::Any.
                TimeBase::TimeT relative_rt_timeout = timeout * 1.0e7;
                CORBA::Any relative_rt_timeout_as_any;
                relative_rt_timeout_as_any <<= relative_rt_timeout;

                // Create the policy and put it in a policy list.
                CORBA::PolicyList policies;
                policies.length(1);
                policies[0] = 
                orb->create_policy (Messaging::RELATIVE_RT_TIMEOUT_POLICY_TYPE,
                                    relative_rt_timeout_as_any);

                // Apply the policy at the ORB level using the ORBPolicyManager.
                CORBA::Object_var obj = orb->resolve_initial_references ("ORBPolicyManager");
                CORBA::PolicyManager_var policy_manager = CORBA::PolicyManager::_narrow (obj.in());
                policy_manager->set_policy_overrides (policies, CORBA::SET_OVERRIDE);
#else
                log(Error) << "Ignoring ORB timeout setting in non-TAO/Messaging build." <<endlog();
#endif // CORBA_IS_TAO
            }
            // Also activate the POA Manager, since we may get call-backs !
            CORBA::Object_var poa_object =
                orb->resolve_initial_references ("RootPOA");
            rootPOA =
                PortableServer::POA::_narrow (poa_object.in ());
            PortableServer::POAManager_var poa_manager =
                rootPOA->the_POAManager ();
            poa_manager->activate ();
            return true;
        }
        catch (CORBA::Exception &e) {
            log(Error) << "Orb Init : CORBA exception raised!" << Logger::nl;
            Logger::log() << CORBA_EXCEPTION_INFO(e) << endlog();
	    std::cout << "ApplicationServer::InitOrb return false: ORBA exception raised\n";
        }
        return false;
    }