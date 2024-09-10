void RMENet::HandleEvent(wxSocketEvent& evt)
{
	NetworkConnection* connection = reinterpret_cast<NetworkConnection*>(evt.GetClientData());
	switch(evt.GetSocketEvent())
	{
		case wxSOCKET_LOST:
		// Connection was lost, either client disconnecting, or our socket breaking
		{
			// Generate event
			wxCommandEvent event(EVT_RMENET_CONNECTION_LOST);
			event.SetInt(0);
			event.SetString("GOOOFU");
			event_dump->AddPendingEvent(event);
		} break;
		case wxSOCKET_OUTPUT:
		// We're ready to write to a socket
		{
			// Send waiting data
			connection->Send();
		} break;
		case wxSOCKET_INPUT:
		// We got some data to be read.
		{
			NetworkMessage* nmsg = connection->Receive();
			if(nmsg)
			{
				try
				{
					OnParsePacket(nmsg);
					FreeMessage(nmsg);
				}
				catch(std::runtime_error&)
				{
					FreeMessage(nmsg);
					Close();
				}
			}
		} break;
	}
}