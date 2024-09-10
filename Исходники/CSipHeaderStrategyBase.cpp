// ----------------------------------------------------------------------------
// CSipHeaderStrategyBase::EliminateClientsL
// ----------------------------------------------------------------------------
//
void CSipHeaderStrategyBase::EliminateClientsL(
    CSIPRequest& aRequest,
    RArray<TUid>& aUids )
    {
	for ( TInt i=0; i < aUids.Count();i++ )
		{
		MSipClient* client = iSipClients.GetByUID( aUids[i] );
		if ( client && !CompareHeaders( aRequest,*client) )
			{
			aUids.Remove( i );
			i--;
			}	
		}
    }