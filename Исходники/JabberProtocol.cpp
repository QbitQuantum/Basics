void
JabberProtocol::OnTag(XMLEntity *entity)
{
	char buffer[4096]; // general buffer space
	static int seen_streams = 0;

	if (entity->IsCompleted() && !strcasecmp(entity->Name(), "iq"))
	{
		
		// handle roster retrival
		if (entity->Child("query") && entity->Child("query")->Attribute("xmlns") &&
			!strcasecmp(entity->Child("query")->Attribute("xmlns"),"jabber:iq:roster"))
		{
			ParseRosterList(entity);
			return;
		}
		
		// handle session retrival
		if (entity->Attribute("id") && entity->Attribute("type") &&
			!strcasecmp(entity->Attribute("type"), "result") &&
			!strcasecmp(entity->Attribute("id"), "sess_1"))
		{
			release_sem(logged);
		
			mainWindow->Lock();
			mainWindow->PostMessage(JAB_LOGGED_IN);
			mainWindow->Unlock();
			
			return;
		}
		
		// handle binding retrival
		if (entity->Attribute("id") && entity->Attribute("type") &&
			!strcasecmp(entity->Attribute("type"), "result") &&
			!strcasecmp(entity->Attribute("id"), "bind_0"))
		{
			jid = BString(entity->Child("bind")->Child("jid")->Data());

			fprintf(stderr, "JID: %s.\n", jid.String());

			Session();
			
			return;
		}
		
		if (entity->Attribute("type") && entity->Child("query") &&
			!strcasecmp(entity->Attribute("type"), "result") &&
			entity->Child("query", "xmlns", "jabber:iq:register"))
		{
			Authorize();
			
			return;
		}
		
		if (entity->Attribute("type") && entity->Attribute("id") &&
			!strcasecmp(entity->Attribute("type"), "result") &&
			!strcasecmp(entity->Attribute("id"), "request_room_info"))
		{
			BMessage msg(JAB_PREFERENCES_DATAFORM);
			msg.AddPointer("XMLEntity", entity);
			MessageRepeater::Instance()->PostMessage(&msg);
			
			return;
		}
		
		if (entity->Attribute("type") && entity->Attribute("id") &&
			!strcasecmp(entity->Attribute("type"), "error"))
		{
			if (!strcasecmp(entity->Attribute("id"), "storage_request"))
			{
				_storage_supported = false;
				return;
			}
			else if (!strcasecmp(entity->Attribute("id"), "save_conferences"))
			{
				_storage_supported = false;
				sprintf(buffer, "Storage XEP-0049 is not supported on server. Cannot save conferences.\n\nNext time will try save to roster.");
				ModalAlertFactory::Alert(buffer, "Pity", NULL, NULL, B_WIDTH_AS_USUAL, B_STOP_ALERT); 
				return;
			}
			else if (!strcasecmp(entity->Attribute("id"), "request_room_info"))
			{
				
				if (entity->Child("error") &&
					entity->Child("error")->Child("text") &&
					entity->Child("error")->Attribute("code"))
					sprintf(buffer, "Error %s:\n\n%s", entity->Child("error")->Attribute("code"),
							entity->Child("error")->Child("text")->Data());
				else
					sprintf(buffer, "Error %s", entity->Child("error")->Attribute("code"));
			
				ModalAlertFactory::Alert(buffer, "OK", NULL, NULL, B_WIDTH_AS_USUAL, B_STOP_ALERT); 
			
				return;
			}
				
			if (entity->Child("error") &&
				entity->Child("error")->Child("text") &&
				entity->Child("error")->Attribute("code"))
				sprintf(buffer, "Error %s:\n\n%s", entity->Child("error")->Attribute("code"),
					entity->Child("error")->Child("text")->Data());
			else
				sprintf(buffer, "Error %s", entity->Child("error")->Attribute("code"));
			
			ModalAlertFactory::Alert(buffer, "OK", NULL, NULL, B_WIDTH_AS_USUAL, B_STOP_ALERT); 
			
			Disconnect();
			
			return;
			
		}
		
		if (entity->Attribute("id") && entity->Child("query") && entity->Child("query")->Attribute("xmlns") &&
			entity->Attribute("type") &&
			!strcasecmp(entity->Attribute("id"), "storage_request") &&
			!strcasecmp(entity->Attribute("type"), "result") &&
			!strcasecmp(entity->Child("query")->Attribute("xmlns"), "jabber:iq:private"))
		{
			if (entity->Child("query")->Child("storage"))
				ParseStorage(entity->Child("query")->Child("storage"));
				
			return;
		}
		
		if (entity->Attribute("type") && !strcasecmp(entity->Attribute("type"), "get"))
		{
			BString iq_from;
			BString iq_id;   
			
			if (entity->Attribute("from")) {
				iq_from = BString(entity->Attribute("from"));
			}
			
			if (entity->Attribute("id")) {
				iq_id = BString(entity->Attribute("id"));
			}
			
			// handle version request
			XMLEntity *query = entity->Child("query");
			if (query && query->Attribute("xmlns")) {
				if (!strcasecmp(query->Attribute("xmlns"), "jabber:iq:version")) {
					ProcessVersionRequest(iq_id, iq_from);
				}
			}
			
			// handle version request
			query = entity->Child("ping");
			if (query && query->Attribute("xmlns")) {
				if (!strcasecmp(query->Attribute("xmlns"), "urn:xmpp:ping"))
				{
					Pong(iq_id, iq_from);
				}
			}
			
			return;
		}
		
		fprintf(stderr, "Unknown IQ message.\n");
		return;
	}
	
	// handle authorization success
	if (entity->IsCompleted() && !strcasecmp(entity->Name(), "success"))
	{
		InitSession();
		
		return;
		
	}
	
	// handle presence messages
	if (entity->IsCompleted() && !strcasecmp(entity->Name(), "presence"))
	{
		ProcessPresence(entity);
		
		return;
	}
	
	// handle stream error
	if (entity->IsCompleted() && !strcasecmp(entity->Name(), "stream:error")) {
		sprintf(buffer, "An stream error has occurred.");
		ModalAlertFactory::Alert(buffer, "Sorry", NULL, NULL, B_WIDTH_AS_USUAL, B_STOP_ALERT); 
		
		Disconnect();
		
		return;
	}
	
	// handle stream error
	if (entity->IsCompleted() && !strcasecmp(entity->Name(), "stream:features"))
	{
		mainWindow->Lock();
		int wantRegister = mainWindow->_login_new_account->Value();
		mainWindow->Unlock();
		
		if (wantRegister == B_CONTROL_ON)
		{
			if (entity->Child("register"))
			{
				mainWindow->Lock();
				mainWindow->_login_new_account->SetValue(B_CONTROL_OFF);
				mainWindow->Unlock();
				
				SendUserRegistration(user, pass, "haiku");
			} else
			{
				sprintf(buffer, "Registration not supported on this server.");
				ModalAlertFactory::Alert(buffer, "Sorry", NULL, NULL, B_WIDTH_AS_USUAL, B_STOP_ALERT); 
				
				Disconnect();
			}
		}
		else if (entity->Child("mechanisms"))
			Authorize();
		else if (entity->Child("bind"))
			Bind();
		else if (entity->Child("session"))
			Session();
			
		return;
		
	}
	
	// handle failures
	if (entity->IsCompleted() && !strcasecmp(entity->Name(), "failure")) {
		if (entity->Child("not-authorized") != NULL)
			sprintf(buffer, "Not authorized failure.");
		else if (entity->Child("invalid-mechanism") != NULL)
			sprintf(buffer, "Invalid mechanism failure.");
		else if (entity->Child("invalid-authzid") != NULL)
			sprintf(buffer, "Invalid authorization Id.");
		else
			sprintf(buffer, "An failure occured.");
			
		ModalAlertFactory::Alert(buffer, "Sorry", NULL, NULL, B_WIDTH_AS_USUAL, B_STOP_ALERT); 
		
		Disconnect();
		
		return;
	}
	
	// handle disconnection
	if (entity->IsCompleted() && !strcasecmp(entity->Name(), "stream:stream"))
	{
		++seen_streams;
		if (seen_streams % 2 == 1)
			Disconnect();
			
		return;
	}
	
	// handle incoming messages
	if (entity->IsCompleted() && !strcasecmp(entity->Name(), "message"))
	{
		//TalkManager::Instance()->Lock();
		TalkManager::Instance()->ProcessMessageData(entity);
		//TalkManager::Instance()->Unlock();
		
		return;
	}
	
	//delete entity;
}