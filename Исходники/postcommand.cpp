void SpanningTreeUtilities::RouteCommand(TreeServer* origin, CommandBase* thiscmd, const CommandBase::Params& parameters, User* user)
{
	const std::string& command = thiscmd->name;
	RouteDescriptor routing = thiscmd->GetRouting(user, parameters);
	if (routing.type == ROUTE_TYPE_LOCALONLY)
		return;

	const bool encap = ((routing.type == ROUTE_TYPE_OPT_BCAST) || (routing.type == ROUTE_TYPE_OPT_UCAST));
	CmdBuilder params(user, encap ? "ENCAP" : command.c_str());
	params.push_tags(parameters.GetTags());
	TreeServer* sdest = NULL;

	if (routing.type == ROUTE_TYPE_OPT_BCAST)
	{
		params.push('*');
		params.push_back(command);
	}
	else if (routing.type == ROUTE_TYPE_UNICAST || routing.type == ROUTE_TYPE_OPT_UCAST)
	{
		sdest = static_cast<TreeServer*>(routing.server);
		if (!sdest)
		{
			// Assume the command handler already validated routing.serverdest and have only returned success if the target is something that the
			// user executing the command is allowed to look up e.g. target is not an uuid if user is local.
			sdest = FindRouteTarget(routing.serverdest);
			if (!sdest)
			{
				ServerInstance->Logs.Log(MODNAME, LOG_DEFAULT, "Trying to route %s%s to nonexistent server %s", (encap ? "ENCAP " : ""), command.c_str(), routing.serverdest.c_str());
				return;
			}
		}

		if (encap)
		{
			params.push_back(sdest->GetID());
			params.push_back(command);
		}
	}
	else
	{
		Module* srcmodule = thiscmd->creator;
		Version ver = srcmodule->GetVersion();

		if (!(ver.Flags & (VF_COMMON | VF_CORE)) && srcmodule != Creator)
		{
			ServerInstance->Logs.Log(MODNAME, LOG_DEFAULT, "Routed command %s from non-VF_COMMON module %s",
				command.c_str(), srcmodule->ModuleSourceFile.c_str());
			return;
		}
	}

	std::string output_text = CommandParser::TranslateUIDs(thiscmd->translation, parameters, true, thiscmd);

	params.push_back(output_text);

	if (routing.type == ROUTE_TYPE_MESSAGE)
	{
		char pfx = 0;
		std::string dest = routing.serverdest;
		if (ServerInstance->Modes.FindPrefix(dest[0]))
		{
			pfx = dest[0];
			dest.erase(dest.begin());
		}
		if (dest[0] == '#')
		{
			Channel* c = ServerInstance->FindChan(dest);
			if (!c)
				return;
			// TODO OnBuildExemptList hook was here
			CUList exempts;
			std::string message;
			if (parameters.size() >= 2)
				message.assign(parameters[1]);
			SendChannelMessage(user->uuid, c, message, pfx, parameters.GetTags(), exempts, command.c_str(), origin ? origin->GetSocket() : NULL);
		}
		else if (dest[0] == '$')
		{
			params.Forward(origin);
		}
		else
		{
			// user target?
			User* d = ServerInstance->FindNick(dest);
			if (!d || IS_LOCAL(d))
				return;
			TreeServer* tsd = TreeServer::Get(d)->GetRoute();
			if (tsd == origin)
				// huh? no routing stuff around in a circle, please.
				return;
			params.Unicast(d);
		}
	}
	else if (routing.type == ROUTE_TYPE_BROADCAST || routing.type == ROUTE_TYPE_OPT_BCAST)
	{
		params.Forward(origin);
	}
	else if (routing.type == ROUTE_TYPE_UNICAST || routing.type == ROUTE_TYPE_OPT_UCAST)
	{
		params.Unicast(sdest->ServerUser);
	}
}