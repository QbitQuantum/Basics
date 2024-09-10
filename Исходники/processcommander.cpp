void ProcessCommander::Run(bool finishConnections)
{
	_errors.clear();
	_finishConnections = finishConnections;
	
	if(!_observation.GetItems().empty() && !_tasks.empty())
	{
		const std::string thisHostName = GetHostName();
		
		// make a list of the involved nodes
		_nodeCommands.Initialize(_observation);
		
		// recycle idle connections
		ConnectionVector list = _idleConnections;
		_idleConnections.clear();
		for(ConnectionVector::iterator i=list.begin();i!=list.end();++i)
		{
			onConnectionAwaitingCommand(*i);
		}
		
		if(_processes.empty())
		{
			//construct a process for each unique node name
			std::vector<std::string> list;
			_nodeCommands.NodeList(list);
			for(std::vector<std::string>::const_iterator i=list.begin();i!=list.end();++i)
			{
				RemoteProcess *process = new RemoteProcess(*i, thisHostName);
				process->SignalFinished() = boost::bind(&ProcessCommander::onProcessFinished, this, _1, _2, _3);
				process->Start();
				_processes.push_back(process);
			}
		}
		
		// We will now start accepting connections. The Run() method will not return until the server
		// stops listening and there are no more io operations pending. With asynchroneous
		// handles, the server and its connections will call onEvent...(). These handles
		// will push new tasks until all tasks in the ProcessCommander are finished.
		_server.Run();
	}
}