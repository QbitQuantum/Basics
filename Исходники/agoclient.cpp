void agocontrol::AgoConnection::run() {
	try {
		receiver = session.createReceiver("agocontrol; {create: always, node: {type: topic}}");
	} catch(const std::exception& error) {
		std::cerr << error.what() << std::endl;
		printf("could not create receiver when connecting to broker\n");
		_exit(1);
	}
	// reportDevices(); // this is obsolete as it is handled by addDevice 
	while( true ) {
		try{
			Variant::Map content;
			Message message = receiver.fetch(Duration::SECOND * 3);
			session.acknowledge();

			// workaround for bug qpid-3445
			if (message.getContent().size() < 4) {
				throw qpid::messaging::EncodingException("message too small");
			}

			decode(message, content);
			// std::cout << content << std::endl;

			if (content["command"] == "discover") {
				reportDevices(); // make resolver happy and announce devices on discover request
			} else {
				if (message.getSubject().size() == 0) {
					// no subject, this is a command
					string internalid = uuidToInternalId(content["uuid"].asString());
					// lets see if this is for one of our devices
					bool isOurDevice = (internalid.size() > 0) && (deviceMap.find(internalIdToUuid(internalid)) != deviceMap.end());
					//  only handle if a command handler is set. In addition it needs to be one of our device when the filter is enabled
					if ( ( isOurDevice || (!(filterCommands))) && commandHandler != NULL) {

						// printf("command for id %s found, calling handler\n", internalid.c_str());
						if (internalid.size() > 0) content["internalid"] = internalid;
						qpid::types::Variant::Map responsemap = commandHandler(content);
						// found a match, reply to sender and pass the command to the assigned handler method
						const Address& replyaddress = message.getReplyTo();
						// only send a reply if this was for one of our childs
						// or if it was the special command inventory when the filterCommands was false, that's used by the resolver
						// to reply to "anonymous" requests not destined to any specific uuid
						if ((replyaddress && isOurDevice) || (content["command"]=="inventory" && filterCommands==false)) {
							// std::cout << "sending reply" << std::endl;
							Session replysession = connection.createSession();
							try {
								Sender replysender = replysession.createSender(replyaddress);
								Message response;
								encode(responsemap, response);
								response.setSubject(instance);
								replysender.send(response);
								replysession.close();
							} catch(const std::exception& error) {
								printf("can't send reply\n");
								replysession.close();
							}
						} 
					}
				} else if (eventHandler != NULL) {
					eventHandler(message.getSubject(), content);
				}
			}
		} catch(const NoMessageAvailable& error) {
			
		} catch(const std::exception& error) {
			std::cerr << error.what() << std::endl;
			if (session.hasError()) {
				clog << agocontrol::kLogCrit << "Session has error, recreating" << std::endl;
				session.close();
				session = connection.createSession(); 
				receiver = session.createReceiver("agocontrol; {create: always, node: {type: topic}}"); 
				sender = session.createSender("agocontrol; {create: always, node: {type: topic}}"); 
			}

			usleep(50);
		}
	}
}