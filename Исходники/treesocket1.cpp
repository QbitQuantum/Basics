CmdResult CommandSQuit::HandleServer(TreeServer* server, std::vector<std::string>& params)
{
	TreeServer* quitting = Utils->FindServer(params[0]);
	if (!quitting)
	{
		ServerInstance->Logs->Log(MODNAME, LOG_DEFAULT, "Squit from unknown server");
		return CMD_FAILURE;
	}

	CmdResult ret = CMD_SUCCESS;
	if (quitting == server)
	{
		ret = CMD_FAILURE;
		server = server->GetParent();
	}
	else if (quitting->GetParent() != server)
		throw ProtocolException("Attempted to SQUIT a non-directly connected server or the parent");

	server->SQuitChild(quitting, params[1]);

	// XXX: Return CMD_FAILURE when servers SQUIT themselves (i.e. :00S SQUIT 00S :Shutting down)
	// to stop this message from being forwarded.
	// The squit logic generates a SQUIT message with our sid as the source and sends it to the
	// remaining servers.
	return ret;
}