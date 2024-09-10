// ----------------------------------------------------------------------------------------
// CFMSServer::FindVariation() 
// ----------------------------------------------------------------------------------------
void CFMSServer::FindVariation()
	{
	FLOG(_L("CFMSServer::FindVariation()"));
	CRepository* centrep = NULL;
	TInt variation = 1;
	TRAPD( err, centrep = CRepository::NewL( KCRUidFotaServer ) );
	if ( centrep )
		{
		FLOG(_L("CFMSServer::FindVariation()::Inside cenrep if"));
		TInt err = centrep->Get( KFotaMonitoryServiceEnabled, variation );                 
		if( err == KErrNone)
			{ 
			FLOG(_L("CFMSServer::FindVariation()::cenrep key found with %d"),variation);
			}
		delete centrep;
		}
	if ( err == KErrNone )
		{
		TBuf<10> var; //32-bit has max of 10 chars in Decimal
		var.Num(variation,EBinary);
		TInt size = var.Length(), maxlen = 4;
		if( size < maxlen)
			{
			TBuf<4> temp;
			temp.AppendFill('0',maxlen-size);
			temp.Append(var);
			var.Zero();
			var.Append(temp);
			}
		var.AppendFill('0',6);
		if( var[0] == '1' )//memory
			{
			FLOG(_L("CFMSServer::FindVariation():: memory monitor supported"));    		
			iMemoryMon = ETrue;
			}
		if( var[1] == '1' ) //startup
			{
			FLOG(_L("CFMSServer::FindVariation()::Phone restart monitor supported"));
			iPhoneRestartMon = ETrue;
			}
		if( var[2] == '1' )//user or charger
			{			
			FLOG(_L("CFMSServer::FindVariation()::charger monitor supported"));    		
			iChargerMon = ETrue;
			}
		if( var[3] == '1' )//newtwork
			{
			FLOG(_L("CFMSServer::FindVariation()::network monitor supported"));
			iNetworkMon = ETrue;
			}    	
		}	
	}