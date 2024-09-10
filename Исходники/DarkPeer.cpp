//==============================================================================
// SendToAll()
//
// Sends a packet to all players.
//==============================================================================
void CDarkPeer::SendToAll(void* pData, DWORD dwDataSize, DWORD dwTimeout, DWORD dwFlags)
{
	Send(ALL_PLAYERS, pData, dwDataSize, dwTimeout, dwFlags);
}