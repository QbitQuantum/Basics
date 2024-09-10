// -----------------------------------------------------------------------------
// CSeiForwardPlugin::ReceiveMessageL
// 
// 
// -----------------------------------------------------------------------------
//
void CSeiForwardPlugin::ReceiveMessageL( TInt aChannel, TPtrC8 aMessage )
	{
	RDebug::Print( _L( "EcmtSeiForwardPlugin::ReceiveMessageL: channel = %d" ), aChannel );
	
	HBufC8* buf = HBufC8::NewLC( KMaxMsgPrefixLen + 1 + aMessage.Length() );
	TPtr8 message = buf->Des();
		
	message.Format( KMsg, aChannel );
	message.Append( KBlanco );
	message.Append( aMessage );
		
	CEcmtMessageEvent* m = iMessaging->NewMessageEvent( TUid::Uid( KSEIFORWARDPLUGIN_IMPL_UID ), message );
	
	User::LeaveIfNull( m );
	iMessaging->GetMessageSender()->SendMessage( m );
	}