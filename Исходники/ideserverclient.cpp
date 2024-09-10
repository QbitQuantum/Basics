/***************************************************************************
	Connect & Disconnect
****************************************************************************/
void	DDEIntegratorClient::SetClientTopic	( char* pszTopicName )
{
	if ( m_hszClientTopic )
		DdeFreeStringHandle( gDDEClientId, m_hszClientTopic);
	m_hszClientTopic =
			DdeCreateStringHandle( gDDEClientId, (LPSTR)pszTopicName, CP_WINANSI );
}