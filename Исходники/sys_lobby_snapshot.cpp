/*
========================
idLobby::SendCompletedPendingSnap
========================
*/
void idLobby::SendCompletedPendingSnap( int p )
{

	assert( lobbyType == GetActingGameStateLobbyType() );
	
	int time = Sys_Milliseconds();
	
	peer_t& peer = peers[p];
	
	if( !peer.IsConnected() )
	{
		return;
	}
	
	if( peer.snapProc == NULL || !peer.snapProc->PendingSnapReadyToSend() )
	{
		return;
	}
	
	// If we have a pending snap ready to send, we better have a pending snap
	assert( peer.snapProc->HasPendingSnap() );
	
	// Get the snap data blob now, even if we don't send it.
	// This is somewhat wasteful, but we have to do this to keep the snap job pipe ready to keep doing work
	// If we don't do this, this peer will cause other peers to be starved of snapshots, when they may very well be ready to send a snap
	byte buffer[ MAX_SNAP_SIZE ];
	int maxLength = sizeof( buffer ) - peer.packetProc->GetReliableDataSize() - 128;
	
	int size = peer.snapProc->GetPendingSnapDelta( buffer, maxLength );
	
	if( !CanSendMoreData( p ) )
	{
		return;
	}
	
	// Can't send anymore snapshots until all fragments are sent
	if( peer.packetProc->HasMoreFragments() )
	{
		return;
	}
	
	// If the peer doesn't have the latest resource list, send it to him before sending any new snapshots
	if( SendResources( p ) )
	{
		return;
	}
	
	int timeFromJobSub = time - peer.lastSnapJobTime;
	int timeFromLastSend = time - peer.lastSnapTime;
	
	if( timeFromLastSend > 0 )
	{
		peer.snapHz = 1000.0f / ( float )timeFromLastSend;
	}
	else
	{
		peer.snapHz = 0.0f;
	}
	
	if( net_snapshot_send_warntime.GetInteger() > 0 && peer.lastSnapTime != 0 && net_snapshot_send_warntime.GetInteger() < timeFromLastSend )
	{
		idLib::Printf( "NET: Took %d ms to send peer %d snapshot\n", timeFromLastSend, p );
	}
	
	if( peer.throttleSnapsForXSeconds != 0 )
	{
		if( time < peer.throttleSnapsForXSeconds )
		{
			return;
		}
		
		// If we were trying to recover ping, see if we succeeded
		if( peer.recoverPing != 0 )
		{
			if( peer.lastPingRtt >= peer.recoverPing )
			{
				peer.failedPingRecoveries++;
			}
			else
			{
				const int peer_throttle_minSnapSeq = session->GetTitleStorageInt( "net_peer_throttle_minSnapSeq", net_peer_throttle_minSnapSeq.GetInteger() );
				if( peer.snapProc->GetFullSnapBaseSequence() > idSnapshotProcessor::INITIAL_SNAP_SEQUENCE + peer_throttle_minSnapSeq )
				{
					// If throttling recovered the ping
					int maxRate = common->GetSnapRate() * session->GetTitleStorageInt( "net_peer_throttle_maxSnapRate", net_peer_throttle_maxSnapRate.GetInteger() );
					peer.throttledSnapRate = idMath::ClampInt( common->GetSnapRate(), maxRate, peer.throttledSnapRate + common->GetSnapRate() );
				}
			}
		}
		
		peer.throttleSnapsForXSeconds = 0;
	}
	
	peer.lastSnapTime = time;
	
	if( size != 0 )
	{
		if( size > 0 )
		{
			NET_VERBOSESNAPSHOT_PRINT_LEVEL( 3, va( "NET: (peer %d) Sending snapshot %d delta'd against %d. Since JobSub: %d Since LastSend: %d. Size: %d\n", p, peer.snapProc->GetSnapSequence(), peer.snapProc->GetBaseSequence(), timeFromJobSub, timeFromLastSend, size ) );
			ProcessOutgoingMsg( p, buffer, size, false, 0 );
		}
		else if( size < 0 )  	// Size < 0 indicates the delta buffer filled up
		{
			// There used to be code here that would disconnect peers if they were in game and filled up the buffer
			// This was causing issues in the playtests we were running (Doom 4 MP) and after some conversation
			// determined that it was not needed since a timeout mechanism has been added since
			ProcessOutgoingMsg( p, buffer, -size, false, 0 );
			if( peer.snapProc != NULL )
			{
				NET_VERBOSESNAPSHOT_PRINT( "NET: (peerNum: %d - name: %s) Resending last snapshot delta %d because his delta list filled up. Since JobSub: %d Since LastSend: %d Delta Size: %d\n", p, GetPeerName( p ), peer.snapProc->GetSnapSequence(), timeFromJobSub, timeFromLastSend, size );
			}
		}
	}
	
	// We calculate what our outgoing rate was for each sequence, so we can have a relative comparison
	// for when the client reports what his downstream was in the same timeframe
	if( IsHost() && peer.snapProc != NULL && peer.snapProc->GetSnapSequence() > 0 )
	{
		//NET_VERBOSE_PRINT("^8  %i Rate: %.2f   SnapSeq: %d GetBaseSequence: %d\n", lastAppendedSequence, peer.packetProc->GetOutgoingRateBytes(), peer.snapProc->GetSnapSequence(), peer.snapProc->GetBaseSequence() );
		peer.sentBpsHistory[ peer.snapProc->GetSnapSequence() % MAX_BPS_HISTORY ] = peer.packetProc->GetOutgoingRateBytes();
	}
}