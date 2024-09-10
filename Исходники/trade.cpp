//o---------------------------------------------------------------------------o
//|   Function    :  CItem *startTrade( CSocket *mSock, CChar *nChar )
//|   Date        :  February 2, 2006
//|   Programmer  :  giwo
//o---------------------------------------------------------------------------o
//|   Purpose     :  Handles everything necesarry to start a secure trade
//o---------------------------------------------------------------------------o
CItem *startTrade( CSocket *mSock, CChar *nChar )
{
	if( mSock == NULL || !ValidateObject( nChar ) )
		return NULL;

	CChar *mChar	= mSock->CurrcharObj();
	CSocket *nSock	= nChar->GetSocket();

	if( !ValidateObject( mChar ) || nSock == NULL )
		return NULL;

	CItem *tradeWindowOne = CreateTradeWindow( mSock, nSock, mChar );
	if( !ValidateObject( tradeWindowOne ) )
		return NULL;

	CItem *tradeWindowTwo = CreateTradeWindow( nSock, mSock, nChar );
	if( !ValidateObject( tradeWindowTwo ) )
	{
		tradeWindowOne->Delete();
		return NULL;
	}

	const SERIAL tw1Serial = tradeWindowOne->GetSerial();
	const SERIAL tw2Serial = tradeWindowTwo->GetSerial();

	tradeWindowOne->SetTempVar( CITV_MOREX, tw2Serial );
	tradeWindowTwo->SetTempVar( CITV_MOREX, tw1Serial );

	CPSecureTrading cpstOne( (*nChar), tw1Serial, tw2Serial );
	cpstOne.Name( nChar->GetName() );
	mSock->Send( &cpstOne );
	
	CPSecureTrading cpstTwo( (*mChar), tw2Serial, tw1Serial );
	cpstTwo.Name( mChar->GetName() );
	nSock->Send( &cpstTwo );

	CPWornItem toWear = (*tradeWindowOne);
	mSock->Send( &toWear );
	nSock->Send( &toWear );

	CPWornItem toWear2 = (*tradeWindowTwo);
	mSock->Send( &toWear2 );
	nSock->Send( &toWear2 );

	return tradeWindowOne;
}