bool CDownloadQueue::SendNextUDPPacket()
{
	if ( m_filelist.empty() || !theApp->serverconnect->IsUDPSocketAvailable() || !theApp->IsConnectedED2K()) {
		return false;
	}

	// Start monitoring the server and the files list
	if ( !m_queueServers.IsActive() ) {
		AddObserver( &m_queueFiles );
		
		theApp->serverlist->AddObserver( &m_queueServers );
	}
	

 	bool packetSent = false;
 	while ( !packetSent ) {
 		// Get max files ids per packet for current server
 		int filesAllowed = GetMaxFilesPerUDPServerPacket();
 
 		if (filesAllowed < 1 || !m_udpserver || IsConnectedServer(m_udpserver)) {
 			// Select the next server to ask, must not be the connected server
 			do {
				m_udpserver = m_queueServers.GetNext();
			} while (IsConnectedServer(m_udpserver));
	
 			m_cRequestsSentToServer = 0;
 			filesAllowed = GetMaxFilesPerUDPServerPacket();
  		}
 
 		
 		// Check if we have asked all servers, in which case we are done
 		if (m_udpserver == NULL) {
 			DoStopUDPRequests();
 			
 			return false;
  		}
  
 		// Memoryfile containing the hash of every file to request
		// 28bytes allocation because 16b + 4b + 8b is the worse case scenario.
 		CMemFile hashlist( 28 );
 		
		CPartFile* file = m_queueFiles.GetNext();
		
		while ( file && filesAllowed ) {
 			uint8 status = file->GetStatus();
 			
			if ( ( status == PS_READY || status == PS_EMPTY ) && file->GetSourceCount() < thePrefs::GetMaxSourcePerFileUDP() ) {
				if (file->IsLargeFile() && !m_udpserver->SupportsLargeFilesUDP()) {
					AddDebugLogLineN(logDownloadQueue, wxT("UDP Request for sources on a large file ignored: server doesn't support it"));
				} else {
					++m_cRequestsSentToServer;
					hashlist.WriteHash( file->GetFileHash() );
					// See the notes on TCP packet
					if ( m_udpserver->GetUDPFlags() & SRV_UDPFLG_EXT_GETSOURCES2 ) {
						if (file->IsLargeFile()) {
							wxASSERT(m_udpserver->SupportsLargeFilesUDP());
							hashlist.WriteUInt32( 0 );
							hashlist.WriteUInt64( file->GetFileSize() );
						} else {
							hashlist.WriteUInt32( file->GetFileSize() );
						}
					}
					--filesAllowed;
				}
  			}
		
			// Avoid skipping a file if we can't send any more currently
			if ( filesAllowed ) {
				file = m_queueFiles.GetNext();
			}
		}
		
		// See if we have anything to send
 		if ( hashlist.GetLength() ) {
 			packetSent = SendGlobGetSourcesUDPPacket(hashlist);
		}
 		
 		// Check if we've covered every file
		if ( file == NULL ) {
 			// Reset the list of asked files so that the loop will start over
			m_queueFiles.Reset();
			
 			// Unset the server so that the next server will be used
 			m_udpserver = NULL;
  		}
  	}
	
	return true;
}