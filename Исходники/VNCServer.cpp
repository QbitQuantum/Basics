int VNCServer::Connect(int partId,const std::wstring &name,WebSocket *socket,const std::string &to)
{
	Log(">VNCServer connecting participant viewer [id:%d,to:%s]\n",partId,to.c_str());

	//Lock
	use.WaitUnusedAndLock();

	//Create new client
	Client *client = new Client(partId,name,this);
	//Set client as as user data
	socket->SetUserData(client);

	//Check if there was one already ws connected for that user
	Clients::iterator it = clients.find(partId);
	//If it was
	if (it!=clients.end())
	{
		//Get old client
		Client *old = it->second;
		//End it
		old->Close();
		//Delete it
		delete(old);
		//Set new one
		it->second = client;
	} else {
		//Append to client list
		clients[partId] = client;
	}

	//If it was editor
	if (partId==editorId)
		//Set client editor
		client->SetViewOnly(false);

	//Check if it is freezed
	if (to.rfind("vnc-freeze")!=std::string::npos)
		//Freeze
		client->FreezeUpdate(true);

	//Unlock clients list
	use.Unlock();

	//Accept incoming connection and add us as listeners
	socket->Accept(this);

	//Connect to socket
	return client->Connect(socket);
}