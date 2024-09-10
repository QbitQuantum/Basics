void ILibWrapper_WebRTC_ConnectionFactory_SetTurnServer(ILibWrapper_WebRTC_ConnectionFactory factory, struct sockaddr_in6* turnServer, char* username, int usernameLength, char* password, int passwordLength, ILibWebRTC_TURN_ConnectFlags turnSetting)
{
	ILibWrapper_WebRTC_ConnectionFactoryStruct *cf = (ILibWrapper_WebRTC_ConnectionFactoryStruct*)factory;
	cf->mTurnSetting = turnSetting;

	if(turnServer != NULL) {memcpy(&(cf->mTurnServer), turnServer, INET_SOCKADDR_LENGTH(turnServer->sin6_family));}
	if(cf->mTurnServerUsername!=NULL) {free(cf->mTurnServerUsername);cf->mTurnServerUsername = NULL;}
	if(cf->mTurnServerPassword!=NULL) {free(cf->mTurnServerPassword);cf->mTurnServerPassword = NULL;}

	if(turnSetting == ILibWebRTC_TURN_DISABLED)
	{
		ILibWebRTC_SetTurnServer(cf->mStunModule, NULL, NULL, 0, NULL, 0, ILibWebRTC_TURN_DISABLED);
	}
	else
	{
		if((cf->mTurnServerUsername = (char*)malloc(usernameLength))==NULL){ILIBCRITICALEXIT(254);}
		cf->mTurnServerUsernameLen = usernameLength;
		memcpy(cf->mTurnServerUsername, username, usernameLength);

		if((cf->mTurnServerPassword = (char*)malloc(passwordLength))==NULL){ILIBCRITICALEXIT(254);}
		cf->mTurnServerPasswordLen = passwordLength;
		memcpy(cf->mTurnServerPassword, password, passwordLength);
	

		ILibWebRTC_SetTurnServer(cf->mStunModule, turnServer, username, usernameLength, password, passwordLength, turnSetting);
	}
}