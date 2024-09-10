ClientManager::ClientManager()
{
	int titanium_port = atoi(server.config->GetVariable("Titanium", "port").c_str());
	EQ::Net::EQStreamManagerOptions titanium_opts(titanium_port, false, false);
	titanium_stream = new EQ::Net::EQStreamManager(titanium_opts);
	titanium_ops = new RegularOpcodeManager;
	if (!titanium_ops->LoadOpcodes(server.config->GetVariable("Titanium", "opcodes").c_str()))
	{
		Log(Logs::General, Logs::Error, "ClientManager fatal error: couldn't load opcodes for Titanium file %s.",
			server.config->GetVariable("Titanium", "opcodes").c_str());
		run_server = false;
	}

	titanium_stream->OnNewConnection([this](std::shared_ptr<EQ::Net::EQStream> stream) {
		LogF(Logs::General, Logs::Login_Server, "New Titanium client connection from {0}:{1}", stream->RemoteEndpoint(), stream->GetRemotePort());
		stream->SetOpcodeManager(&titanium_ops);
		Client *c = new Client(stream, cv_titanium);
		clients.push_back(c);
	});

	int sod_port = atoi(server.config->GetVariable("SoD", "port").c_str());
	EQ::Net::EQStreamManagerOptions sod_opts(sod_port, false, false);
	sod_stream = new EQ::Net::EQStreamManager(sod_opts);
	sod_ops = new RegularOpcodeManager;
	if (!sod_ops->LoadOpcodes(server.config->GetVariable("SoD", "opcodes").c_str()))
	{
		Log(Logs::General, Logs::Error, "ClientManager fatal error: couldn't load opcodes for SoD file %s.",
			server.config->GetVariable("SoD", "opcodes").c_str());
		run_server = false;
	}

	sod_stream->OnNewConnection([this](std::shared_ptr<EQ::Net::EQStream> stream) {
		LogF(Logs::General, Logs::Login_Server, "New SoD client connection from {0}:{1}", stream->RemoteEndpoint(), stream->GetRemotePort());
		stream->SetOpcodeManager(&sod_ops);
		Client *c = new Client(stream, cv_sod);
		clients.push_back(c);
	});
}