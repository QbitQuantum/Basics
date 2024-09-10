void LiveServer::HandleEvent(wxSocketEvent& evt)
{
	LivePeer* connection = reinterpret_cast<LivePeer*>(evt.GetClientData());
	try {
		switch(evt.GetSocketEvent()) {
			case wxSOCKET_CONNECTION:
			// A client tries to connect!
			{
				wxSocketBase* client = serv->Accept(false);
				if(!client) {
					log->Message(wxT("Network error: Could not accept incoming connection."));
				}
				LivePeer* connection = newd LivePeer(this, client);
				connection->parser = &LiveServer::OnParseLoginPackets;
				connecting_clients.push_back(connection);
				client->SetClientData(connection);

				client->SetEventHandler(*this, wxID_ANY);
				client->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_OUTPUT_FLAG | wxSOCKET_CONNECTION_FLAG | wxSOCKET_LOST_FLAG);
				client->Notify(true);
			} break;
			case wxSOCKET_LOST:
			// Connection was lost, either client disconnecting, or our socket breaking
			{
				if(connection->GetClientID() != 0)
				{
					client_mask &= ~(1 << connection->GetClientID());
					editor->map.clearVisible(client_mask);
				}

				bool client = false;
				PeerList::iterator iter = connected_clients.begin();
				while(iter != connected_clients.end())
				{
					if(*iter == connection)
					{
						client = true;
						connected_clients.erase(iter);
						break;
					}
					else
						++iter;
				}

				if(client)
				{
					// It was a client disconnecting.
					wxString str;
					str << wxT("Lost remote connection ") << connection->GetNick() << wxT(" (") << connection->GetHost() << wxT(")");
					log->Message(str);
					log->UpdateClientList(connected_clients);
					delete connection;
				}
				else
				{
					// Our socket broke!
					log->Message(wxT("Network connection was interrupted. Can no longer continue to host."));
					delete connection;
					Close();
				}
			} break;
			case wxSOCKET_OUTPUT:
			// We're ready to write to a socket
			{
				//log->Message(wxT("Socket is writeable!"));
				if(connection)
					connection->Send();
			} break;
			case wxSOCKET_INPUT:
			// We got some data to be read.
			{
				NetworkMessage* nmsg = connection->Receive();
				if(nmsg)
				{
					((this)->*(connection->parser))(connection, nmsg);
					FreeMessage(nmsg);
				}
			} break;
		}
	}
	catch(std::runtime_error& err)
	{
		connection->Close();
		log->Message(wxT("Invalid packet received, the reported error was: ") + wxString(err.what(), wxConvUTF8));
	}
}