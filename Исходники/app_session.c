int AppSessionSendOwnerMessage( AppSession *as, UserSession *sender, char *msg, int length )
{
	int msgsndsize = 0;
	if( as == NULL )
	{
		DEBUG("[AppSession] AppSession parameter is empty\n");
		return -1;
	}
	
	time_t ntime = time( NULL );
	DEBUG("[AppSession] OLD TIME %lld NEW TIME %lld\n", (long long)as->as_Timer, (long long)ntime );
	if( ( ntime - as->as_Timer ) > TIMEOUT_APP_SESSION )
	{
		as->as_Obsolete = TRUE;
	}
	as->as_Timer = ntime;

	DEBUG("[AppSession] Send message %s\n", msg );
	
	char *newmsg = NULL;
	
	if( ( newmsg = FCalloc( length+256, sizeof(char) ) ) != NULL )
	{
		User *usend = sender->us_User;
		DEBUG("[AppSession] AS POINTER %p SENDER %p\n", as, usend );
		int newmsgsize = sprintf( newmsg, WS_MESSAGE_TEMPLATE_USER, as->as_AuthID, as->as_SASID, usend->u_Name, msg );
		
		msgsndsize += WebSocketSendMessageInt( as->as_UserSessionList->usersession, newmsg, newmsgsize );
		DEBUG("[AppSession] FROM %s  TO %s  MESSAGE SIZE %d\n", usend->u_Name, as->as_UserSessionList->usersession->us_User->u_Name, msgsndsize );

		FFree( newmsg );
	}
	else
	{
		FERROR("Cannot allocate memory for message\n");
	}
	
	return msgsndsize;
}