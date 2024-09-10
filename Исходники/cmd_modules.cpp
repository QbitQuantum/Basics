/** Handle /MODULES
 */
CmdResult CommandModules::Handle(User* user, const Params& parameters)
{
	// Don't ask remote servers about their modules unless the local user asking is an oper
	// 2.0 asks anyway, so let's handle that the same way
	bool for_us = (parameters.empty() || irc::equals(parameters[0], ServerInstance->Config->ServerName));
	if ((!for_us) || (!IS_LOCAL(user)))
	{
		if (!user->IsOper())
		{
			user->WriteNotice("*** You cannot check what modules other servers have loaded.");
			return CMD_FAILURE;
		}

		// From an oper and not for us, forward
		if (!for_us)
			return CMD_SUCCESS;
	}

	const ModuleManager::ModuleMap& mods = ServerInstance->Modules.GetModules();

  	for (ModuleManager::ModuleMap::const_iterator i = mods.begin(); i != mods.end(); ++i)
	{
		Module* m = i->second;
		Version V = m->GetVersion();

		if (IS_LOCAL(user) && user->HasPrivPermission("servers/auspex"))
		{
			std::string flags("VCO");
			size_t pos = 0;
			for (int mult = 2; mult <= VF_OPTCOMMON; mult *= 2, ++pos)
				if (!(V.Flags & mult))
					flags[pos] = '-';

			std::string srcrev = m->ModuleDLLManager->GetVersion();
			user->WriteRemoteNumeric(RPL_MODLIST, m->ModuleSourceFile, srcrev.empty() ? "*" : srcrev, flags, V.description);
		}
		else
		{
			user->WriteRemoteNumeric(RPL_MODLIST, m->ModuleSourceFile, '*', '*', V.description);
		}
	}
	user->WriteRemoteNumeric(RPL_ENDOFMODLIST, "End of MODULES list");

	return CMD_SUCCESS;
}