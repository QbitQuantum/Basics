static void checkLogging(ACSDaemonContext * context, short instance)
{
	if (!loggingSystemInitialized)
	{
		// we need msg_callback to get LoggingProxy
		if (ACE_LOG_MSG->msg_callback () != 0 &&
				context->hasConfigurationReference(instance, acsServices[NAMING_SERVICE].xmltag))
		{
			try
			{
				// we get via NS and not a manager (to support logging when manager is not running)
				std::string nsReference = context->getConfigurationReference(instance, acsServices[NAMING_SERVICE].xmltag);
				CORBA::Object_var nc_obj = context->getORB()->string_to_object(nsReference.c_str());
				if (nc_obj.ptr() != CORBA::Object::_nil())
				{
					CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow(nc_obj.in());
					if (nc.ptr() != CosNaming::NamingContext::_nil())
					{
						CosNaming::Name name;
						name.length(1);
						name[0].id = CORBA::string_dup("Log");

						CORBA::Object_var obj = nc->resolve(name);
						if (!CORBA::is_nil(obj.in()))
                    	{
							Logging::AcsLogService_var logger = Logging::AcsLogService::_narrow(obj.in());

							LoggingProxy* lp = static_cast<LoggingProxy*>(ACE_LOG_MSG->msg_callback());
							lp->setCentralizedLogger(logger.in());
							lp->setNamingContext(nc.in());
                            loggingSystemInitialized = true;
                            ACS_SHORT_LOG((LM_DEBUG, "Remote logging system initialized."));
                        }
						else
						{
							ACS_SHORT_LOG((LM_DEBUG, "Unable to resolve Log from the naming service."));
						}
					}
					else
					{
						ACS_SHORT_LOG((LM_DEBUG, "Unable to narrow NamingContext."));
					}
				}
				else
				{
					ACS_SHORT_LOG((LM_ERROR, "Unable to resolve naming service, invalid corbaloc reference: '%s'.", nsReference.c_str()));
				}
			}
			catch (...)
			{
				ACS_SHORT_LOG((LM_DEBUG, "Unable to initialize logging sytem, unexpected exception caught."));
			}
		}
	}
}