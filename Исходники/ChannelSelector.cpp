void ChannelSelector::Execute ( void * arg ) {
	while ( status ) {
	    try{
			char buffer[1024] = {0};
			int bytes = 0, desc = 0;
			WSAttributes attributes;
			Connection * newConnection = NULL;
			WSProtocol * protocol = NULL;
			Log ( "Channel Selector: started" );
			while ( status ) { 
				if ( connectionsWaiting->wait ( ) ) {//Needs to have a timeout.
					continue;
				}
				connectionsWaiting->lock ( );
				desc = connectionsWaiting->get ( );
				connectionsWaiting->unlock ( );	
				Log ( "Channel Selector: new connection" );	
				protocol = new RFC_6455();
				newConnection = new Connection ( desc, protocol );
				Log ( "Channel Selector: waiting for handshake" );
				bytes = newConnection->recv ( buffer, sizeof(buffer)/sizeof(char) );
				Log ( "Channel Selector: handshake checking" );
				if ( bytes > 0 ) {				
					Log ( "Channel Selector: handshake received" );
					if ( newConnection->handshake ( buffer, &attributes ) == 0 ){
						/*		
						std::cout<<"[Version] " << attributes.version << std::endl;
						std::cout<<"[Channel] " << attributes.channel << std::endl;
						std::cout<<"[Response] " << std::endl << attributes.response << std::endl;
						*/
						//std::cout<<"[Channel] " << attributes.channel << std::endl;
						newConnection->send ( attributes.response.c_str(), attributes.response.length() );
						if ( channels->find( attributes.channel ) != channels->end() ) {
							//std::cout<< "Connection sent to: " << attributes.channel<<std::endl;
							Log ( "Channel Selector: Connection sent to: " + attributes.channel );
							(*channels) [ attributes.channel ]->addConnection ( newConnection );
						} else {
							Log ( "Channel Selector: Channel Not found" );
							newConnection->close ( );
							//delete newConnection;//Protocol is freed within Connection()
							//newConnection = NULL;
							//protocol = NULL;
						}
						continue;
					}
					Log ( "Channel Selector: unable to find protocol" );
				}
				
				//delete newConnection;//Protocol is freed within Connection()
				//newConnection = NULL;
				//protocol = NULL;
	   		}
	   		break;
	    } catch(std::exception& e){
			Log ( "Channel Selector: failed. --" + std::string(e.what ( )) );
	    }
	}
}