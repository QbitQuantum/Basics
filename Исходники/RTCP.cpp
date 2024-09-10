void RTCPInstance::incomingReportHandler1() {
	
	do {
		
		Boolean callByeHandler = False;
		int tcpReadStreamSocketNum = fRTCPInterface.nextTCPReadStreamSocketNum();
		unsigned char tcpReadStreamChannelId = fRTCPInterface.nextTCPReadStreamChannelId();
		unsigned packetSize = 0;
		unsigned numBytesRead;
		struct sockaddr_in fromAddress;
		Boolean packetReadWasIncomplete;
		Boolean readResult
			= fRTCPInterface.handleRead(&fInBuf[fNumBytesAlreadyRead], maxPacketSize - fNumBytesAlreadyRead,
					numBytesRead, fromAddress, packetReadWasIncomplete);
		if (packetReadWasIncomplete) {
			fNumBytesAlreadyRead += numBytesRead;
			return; // more reads are needed to get the entire packet
		} else { // normal case: We've read the entire packet 
			packetSize = fNumBytesAlreadyRead + numBytesRead;
			fNumBytesAlreadyRead = 0; // for next time
		}
		if (!readResult) break;

		// Ignore the packet if it was looped-back from ourself:
		Boolean packetWasFromOurHost = False;
		if (RTCPgs()->wasLoopedBackFromUs(envir(), fromAddress)) {
			packetWasFromOurHost = True;
			// However, we still want to handle incoming RTCP packets from
			// *other processes* on the same machine.  To distinguish this
			// case from a true loop-back, check whether we've just sent a
			// packet of the same size.  (This check isn't perfect, but it seems
			// to be the best we can do.)
			if (fHaveJustSentPacket && fLastPacketSentSize == packetSize) {
				// This is a true loop-back:
				fHaveJustSentPacket = False;
				break; // ignore this packet
			}
		}

		unsigned char* pkt = fInBuf;
		if (fIsSSMSource && !packetWasFromOurHost) {
			// This packet is assumed to have been received via unicast (because we're a SSM source, and SSM receivers send back RTCP "RR"
			// packets via unicast).  'Reflect' the packet by resending it to the multicast group, so that any other receivers can also
			// get to see it.

			// NOTE: Denial-of-service attacks are possible here.
			// Users of this software may wish to add their own,
			// application-specific mechanism for 'authenticating' the
			// validity of this packet before reflecting it.

			// NOTE: The test for "!packetWasFromOurHost" means that we won't reflect RTCP packets that come from other processes on
			// the same host as us.  The reason for this is that the 'packet size' test above is not 100% reliable; some packets
			// that were truly looped back from us might not be detected as such, and this might lead to infinite forwarding/receiving
			// of some packets.  To avoid this possibility, we only reflect RTCP packets that we know for sure originated elsewhere.
			// (Note, though, that if we ever re-enable the code in "Groupsock::multicastSendOnly()", then we could remove the test for
			// "!packetWasFromOurHost".)
			
			fRTCPInterface.sendPacket(pkt, packetSize);
			fHaveJustSentPacket = True;
			fLastPacketSentSize = packetSize;
			
		}

#ifdef DEBUG
		fprintf(stderr, "[%p]saw incoming RTCP packet (from address %s, port %d)\n", this, AddressString(fromAddress).val(), ntohs(fromAddress.sin_port));
		for (unsigned i = 0; i < packetSize; ++i) {
			if (i%4 == 0) fprintf(stderr, " ");
			fprintf(stderr, "%02x", pkt[i]);
		}
		fprintf(stderr, "\n");
#endif
		int totPacketSize = IP_UDP_HDR_SIZE + packetSize;

		// Check the RTCP packet for validity:
		// It must at least contain a header (4 bytes), and this header
		// must be version=2, with no padding bit, and a payload type of
		// SR (200) or RR (201):
		if (packetSize < 4) 
			break;
		
		unsigned rtcpHdr = ntohl(*(u_int32_t*)pkt);
		if ((rtcpHdr & 0xE0FE0000) != (0x80000000 | (RTCP_PT_SR<<16))) {
#ifdef DEBUG
			fprintf(stderr, "rejected bad RTCP packet: header 0x%08x\n", rtcpHdr);
#endif
			break;
		}

		// Process each of the individual RTCP 'subpackets' in (what may be)
		// a compound RTCP packet.
		int typeOfPacket = PACKET_UNKNOWN_TYPE;
		unsigned reportSenderSSRC = 0;
		Boolean packetOK = False;
		while (1) {
			
			unsigned rc = (rtcpHdr>>24)&0x1F;
			unsigned pt = (rtcpHdr>>16)&0xFF;
			unsigned length = 4*(rtcpHdr&0xFFFF); // doesn't count hdr
			ADVANCE(4); // skip over the header
			if (length > packetSize) break;

			// Assume that each RTCP subpacket begins with a 4-byte SSRC:
			if (length < 4) break; length -= 4;
			reportSenderSSRC = ntohl(*(u_int32_t*)pkt); ADVANCE(4);

			Boolean subPacketOK = False;
			
			switch (pt) {
				case RTCP_PT_SR: {
#ifdef DEBUG
							 fprintf(stderr, "SR\n");
#endif
							 if (length < 20) break; length -= 20;

							 // Extract the NTP timestamp, and note this:
							 unsigned NTPmsw = ntohl(*(u_int32_t*)pkt); ADVANCE(4);
							 unsigned NTPlsw = ntohl(*(u_int32_t*)pkt); ADVANCE(4);
							 unsigned rtpTimestamp = ntohl(*(u_int32_t*)pkt); ADVANCE(4);
							 if (fSource != NULL) {
								 RTPReceptionStatsDB& receptionStats
									 = fSource->receptionStatsDB();
								 receptionStats.noteIncomingSR(reportSenderSSRC,
										 NTPmsw, NTPlsw, rtpTimestamp);
							 }
							 ADVANCE(8); // skip over packet count, octet count


							 // If a 'SR handler' was set, call it now:
							 if (fSRHandlerTask != NULL) (*fSRHandlerTask)(fSRHandlerClientData);

							 // The rest of the SR is handled like a RR (so, no "break;" here)
						 }
				
				case RTCP_PT_RR: {
#ifdef DEBUG
							 fprintf(stderr, "RR\n");
#endif
							 unsigned reportBlocksSize = rc*(6*4);
							 if (length < reportBlocksSize) break;
							 length -= reportBlocksSize;

							 if (fSink != NULL) {
								 // Use this information to update stats about our transmissions:
								 RTPTransmissionStatsDB& transmissionStats = fSink->transmissionStatsDB();
								 for (unsigned i = 0; i < rc; ++i) {
									 unsigned senderSSRC = ntohl(*(u_int32_t*)pkt); ADVANCE(4);
									 // We care only about reports about our own transmission, not others'
									 if (senderSSRC == fSink->SSRC()) {
										 unsigned lossStats = ntohl(*(u_int32_t*)pkt); ADVANCE(4);
										 unsigned highestReceived = ntohl(*(u_int32_t*)pkt); ADVANCE(4);
										 unsigned jitter = ntohl(*(u_int32_t*)pkt); ADVANCE(4);
										 unsigned timeLastSR = ntohl(*(u_int32_t*)pkt); ADVANCE(4);
										 unsigned timeSinceLastSR = ntohl(*(u_int32_t*)pkt); ADVANCE(4);
										 transmissionStats.noteIncomingRR(reportSenderSSRC, fromAddress,
												 lossStats,
												 highestReceived, jitter,
												 timeLastSR, timeSinceLastSR);
									 } else {
										 ADVANCE(4*5);
									 }
								 }
							 } else {
								 ADVANCE(reportBlocksSize);
							 }


							 if (pt == RTCP_PT_RR) { // i.e., we didn't fall through from 'SR'
								 // If a 'RR handler' was set, call it now:

								 // Specific RR handler:
								 if (fSpecificRRHandlerTable != NULL) {
									 netAddressBits fromAddr;
									 portNumBits fromPortNum;
									 if (tcpReadStreamSocketNum < 0) {
										 // Normal case: We read the RTCP packet over UDP
										 fromAddr = fromAddress.sin_addr.s_addr;
										 fromPortNum = ntohs(fromAddress.sin_port);
									 } else {
										 // Special case: We read the RTCP packet over TCP (interleaved)
										 // Hack: Use the TCP socket and channel id to look up the handler
										 fromAddr = tcpReadStreamSocketNum;
										 fromPortNum = tcpReadStreamChannelId;
									 }
									 Port fromPort(fromPortNum);
									 RRHandlerRecord* rrHandler
										 = (RRHandlerRecord*)(fSpecificRRHandlerTable->Lookup(fromAddr, (~0), fromPort));
									 if (rrHandler != NULL) {
										 if (rrHandler->rrHandlerTask != NULL) {
											 (*(rrHandler->rrHandlerTask))(rrHandler->rrHandlerClientData);
										 }
									 }
								 }

								 // General RR handler:
								 if (fRRHandlerTask != NULL) (*fRRHandlerTask)(fRRHandlerClientData);
							 }

							 subPacketOK = True;
							 typeOfPacket = PACKET_RTCP_REPORT;
							 break;
						 }
				
				case RTCP_PT_BYE: {
#ifdef DEBUG
							  fprintf(stderr, "BYE\n");
#endif
							  // If a 'BYE handler' was set, arrange for it to be called at the end of this routine.
							  // (Note: We don't call it immediately, in case it happens to cause "this" to be deleted.)
							  if (fByeHandlerTask != NULL
									  && (!fByeHandleActiveParticipantsOnly
										  || (fSource != NULL
											  && fSource->receptionStatsDB().lookup(reportSenderSSRC) != NULL)
										  || (fSink != NULL
											  && fSink->transmissionStatsDB().lookup(reportSenderSSRC) != NULL))) {
								  callByeHandler = True;
							  }

							  // We should really check for & handle >1 SSRCs being present #####

							  subPacketOK = True;
							  typeOfPacket = PACKET_BYE;
							  break;
						  }
						  // Later handle SDES, APP, and compound RTCP packets #####
				default:
#ifdef DEBUG
						  fprintf(stderr, "UNSUPPORTED TYPE(0x%x)\n", pt);
#endif
						  subPacketOK = True;
						  break;
			}
			if (!subPacketOK) break;

			// need to check for (& handle) SSRC collision! #####

#ifdef DEBUG
			fprintf(stderr, "validated RTCP subpacket (type %d): %d, %d, %d, 0x%08x\n", typeOfPacket, rc, pt, length, reportSenderSSRC);
#endif

			// Skip over any remaining bytes in this subpacket:
			ADVANCE(length);

			// Check whether another RTCP 'subpacket' follows:
			if (packetSize == 0) {
				packetOK = True;
				break;
			} else if (packetSize < 4) {
#ifdef DEBUG
				fprintf(stderr, "extraneous %d bytes at end of RTCP packet!\n", packetSize);
#endif
				break;
			}
			rtcpHdr = ntohl(*(u_int32_t*)pkt);
			if ((rtcpHdr & 0xC0000000) != 0x80000000) {
#ifdef DEBUG
				fprintf(stderr, "bad RTCP subpacket: header 0x%08x\n", rtcpHdr);
#endif
				break;
			}
		}

		if (!packetOK) {
#ifdef DEBUG
			fprintf(stderr, "rejected bad RTCP subpacket: header 0x%08x\n", rtcpHdr);
#endif
			break;
		} else {
#ifdef DEBUG
			fprintf(stderr, "validated entire RTCP packet\n");
#endif
		}

		onReceive(typeOfPacket, totPacketSize, reportSenderSSRC);

		// Finally, if we need to call a "BYE" handler, do so now (in case it causes "this" to get deleted):
		if (callByeHandler && fByeHandlerTask != NULL/*sanity check*/) {
			TaskFunc* byeHandler = fByeHandlerTask;
			fByeHandlerTask = NULL; // because we call the handler only once, by default
			(*byeHandler)(fByeHandlerClientData);
		}
	} while (0);
}