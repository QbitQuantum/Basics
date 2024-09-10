void ClientInterface::updateLobby(){
	NetworkMessageType networkMessageType= getNextMessageType();
	
	switch(networkMessageType){
		case nmtInvalid:
			break;

		case nmtIntro:{
			NetworkMessageIntro networkMessageIntro;

			if(receiveMessage(&networkMessageIntro)){
				
				//check consistency
				if(Config::getInstance().getBool("NetworkConsistencyChecks")){
					if(networkMessageIntro.getVersionString()!=getNetworkVersionString()){
						throw runtime_error("Server and client versions do not match (" + networkMessageIntro.getVersionString() + "). You have to use the same binaries.");
					}	
				}

				//send intro message
				NetworkMessageIntro sendNetworkMessageIntro(getNetworkVersionString(), getHostName(), -1);

				playerIndex= networkMessageIntro.getPlayerIndex();
				serverName= networkMessageIntro.getName();
				sendMessage(&sendNetworkMessageIntro);
					
				assert(playerIndex>=0 && playerIndex<GameConstants::maxPlayers);
				introDone= true;
			}
		}
		break;

		case nmtLaunch:{
			NetworkMessageLaunch networkMessageLaunch;

			if(receiveMessage(&networkMessageLaunch)){
				networkMessageLaunch.buildGameSettings(&gameSettings);

				//replace server player by network
				for(int i= 0; i<gameSettings.getFactionCount(); ++i){
					
					//replace by network
					if(gameSettings.getFactionControl(i)==ctHuman){
						gameSettings.setFactionControl(i, ctNetwork);
					}

					//set the faction index
					if(gameSettings.getStartLocationIndex(i)==playerIndex){
						gameSettings.setThisFactionIndex(i);
					}
				}
				launchGame= true;
			}
		}
		break;

		default:
			throw runtime_error("Unexpected network message: " + intToStr(networkMessageType));
	}
}