bool
SimpleAuthorizer2::checkAccess(const String& opType, const String& ns,
	const ServiceEnvironmentIFCRef& env, OperationContext& context)
{
	OW_ASSERT(opType == ACCESS_READ || opType == ACCESS_WRITE
		|| opType == ACCESS_READWRITE);

	UserInfo userInfo = context.getUserInfo();
	if (userInfo.getInternal())
	{
		return true;
	}

	CIMOMHandleIFCRef lch = env->getCIMOMHandle(context,
		ServiceEnvironmentIFC::E_USE_PROVIDERS);

	LoggerRef lgr = env->getLogger(COMPONENT_NAME);

	if (!userInfo.getUserName().empty())
	{
		String superUser =
			env->getConfigItem(ConfigOpts::ACL_SUPERUSER_opt);
		if (superUser.equalsIgnoreCase(userInfo.getUserName()))
		{
			OW_LOG_DEBUG(lgr, "User is SuperUser: checkAccess returning.");
			return true;
		}
	}

	String lns(ns);
	while (lns.startsWith('/'))
	{
		lns = lns.substring(1);
	}
	lns.toLowerCase();
	for (;;)
	{
		if (!userInfo.getUserName().empty())
		{
			try
			{
				CIMClass cc = lch->getClass("root/security",
					"OpenWBEM_UserACL", E_NOT_LOCAL_ONLY, E_INCLUDE_QUALIFIERS,
					E_INCLUDE_CLASS_ORIGIN, NULL);
			}
			catch(CIMException&)
			{
				OW_LOG_DEBUG(lgr, "OpenWBEM_UserACL class non-existent in"
					" /root/security. ACLs disabled");
				return true;
			}
			
			CIMObjectPath cop("OpenWBEM_UserACL");
			cop.setKeyValue("username", CIMValue(userInfo.getUserName()));
			cop.setKeyValue("nspace", CIMValue(lns));
			CIMInstance ci(CIMNULL);
			try
			{
				ci = lch->getInstance("root/security", cop,
					E_NOT_LOCAL_ONLY, E_INCLUDE_QUALIFIERS,
					E_INCLUDE_CLASS_ORIGIN, NULL);
			}
			catch(const CIMException&)
			{
				ci.setNull();
			}
			if (ci)
			{
				String capability;
				CIMProperty capabilityProp = ci.getProperty("capability");
				if (capabilityProp)
				{
					CIMValue cv = capabilityProp.getValue();
					if (cv)
					{
						capability = cv.toString();
					}
				}

				capability.toLowerCase();
				if (opType.length() == 1)
				{
					if (capability.indexOf(opType) == String::npos)
					{
					    // Access to namespace denied for user
						OW_THROWCIM(CIMException::ACCESS_DENIED);
					}
				}
				else
				{
					if (!capability.equals("rw") && !capability.equals("wr"))
					{
						// Access to namespace denied for user
						OW_THROWCIM(CIMException::ACCESS_DENIED);
					}
				}

				// Access to namespace granted for user
				return true;
			}
		}

		// use default policy for namespace
		try
		{
			CIMClass cc = lch->getClass("root/security",
				"OpenWBEM_NamespaceACL", E_NOT_LOCAL_ONLY, E_INCLUDE_QUALIFIERS,
				E_INCLUDE_CLASS_ORIGIN, NULL);
		}
		catch(CIMException&)
		{
			// OpenWBEM_NamespaceACL class non-existent in /root/security.
			// namespace ACLs disabled
			return true;
		}
		CIMObjectPath cop("OpenWBEM_NamespaceACL");
		cop.setKeyValue("nspace", CIMValue(lns));
		CIMInstance ci(CIMNULL);
		try
		{
			ci = lch->getInstance("root/security", cop, E_NOT_LOCAL_ONLY,
				E_INCLUDE_QUALIFIERS, E_INCLUDE_CLASS_ORIGIN, NULL);
		}
		catch(const CIMException& ce)
		{
			OW_LOG_DEBUG(lgr, Format("Caught exception: %1 in"
				" AccessMgr::checkAccess. line=%2", ce, __LINE__));
			ci.setNull();
		}
	
		if (ci)
		{
			String capability;
			CIMProperty capabilityProp = ci.getProperty("capability");
			if (capabilityProp)
			{
				CIMValue v = capabilityProp.getValue();
				if (v)
				{
					capability = v.toString();
				}
			}

			capability.toLowerCase();
			if (opType.length() == 1)
			{
				if (capability.indexOf(opType) == String::npos)
				{
					// Access namespace denied for user
				   	OW_THROWCIM(CIMException::ACCESS_DENIED);
				}
			}
			else
			{
				if (!capability.equals("rw") && !capability.equals("wr"))
				{
					// Access to namespace denied for user
				   	OW_THROWCIM(CIMException::ACCESS_DENIED);
				}
			}

			// Access to namespace granted for user
			return true;
		}
		size_t idx = lns.lastIndexOf('/');
		if (idx == 0 || idx == String::npos)
		{
			break;
		}
		lns = lns.substring(0, idx);
	}

	// Access to namespace denied for user
   	OW_THROWCIM(CIMException::ACCESS_DENIED);
	return false;
}