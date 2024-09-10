void Human_Vendor::onSpeechInput( P_PLAYER pTalker, const QString& comm )
{
	if ( !pTalker->socket() )
		return;

	if ( m_npc->inRange( pTalker, 4 ) && VendorChkName( m_npc, comm ) )
	{
		if ( comm.contains( tr( " BUY" ) ) )
		{
			m_npc->vendorBuy( pTalker );
		}
		else if ( comm.contains( tr( " SELL" ) ) )
		{
			m_npc->vendorSell( pTalker );
		}
	}
}