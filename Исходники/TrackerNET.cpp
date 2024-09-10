//-----------------------------------------------------------------------------
// Purpose: Checks to see if we should resend any reliable packets
//-----------------------------------------------------------------------------
void CTrackerNET::CheckReliablePacketSending()
{
	float time = m_pThreads->GetTime();

	// reliable packets are held in the m_ReliableMessages queue in the order that they were sent
	// if a packet is resent, it is moved to the end of the queue
	// packets are also checked at this time to see if they have been acknowledged
	while (m_ReliableMessages.Count())
	{
		// get the first message
		int index = m_ReliableMessages.Head();

		// get the message
		SentMessage_t &msg = m_ReliableMessages[index];

		// check the resend time, if it's not time to resend then we have nothing more to do 
		if (msg.resendTime > time)
			break;	

		// get the network target for this message
		if (!m_TargetList.IsValidIndex(msg.networkTargetHandle) 
			|| !m_TargetList.IsInList(msg.networkTargetHandle) 
			|| m_TargetList[msg.networkTargetHandle].targetID != msg.networkTargetID)
		{
			// message's target has been removed, kill
			if (msg.message)
			{
				msg.message->deleteThis();
			}
			m_ReliableMessages.Remove(index);
			continue;
		}

		NetworkTarget_t &target = m_TargetList[msg.networkTargetHandle];

		// check to see if it's already been acknowledged
		if (msg.sequenceNumber <= target.outgoingAcknowledged)
		{
			// message has been acknowledged, kill
			if (msg.message)
			{
				msg.message->deleteThis();
			}
			m_ReliableMessages.Remove(index);

			// move onto next message
			continue;
		}

		// check to see if we should resend this packet
		msg.resendAttempt++;
		if (msg.resendAttempt < MAX_SEND_ATTEMPTS)
		{
			// only send the message if it's in the message send window
			if (msg.sequenceNumber < target.outgoingAcknowledged + MESSAGE_WINDOW)
			{
				WriteToLog("-> Resending '%d' (os:%d > %d) (%s)\n", msg.message->GetMsgID(), msg.sequenceNumber, target.outgoingAcknowledged, target.netAddress.ToStaticString());

				// send that it again
				InternalSendMessage(msg.message, &target, msg.sequenceNumber);
			}
			else
			{
				// hold back on sending the message
				WriteToLog("-> Holding back resend '%d' (os:%d > %d) (%s)\n", msg.message->GetMsgID(), msg.sequenceNumber, target.outgoingAcknowledged, target.netAddress.ToStaticString());
				msg.resendAttempt--;
			}

			// set the time before retrying again
			// send times: 0.0 1.5 1.5 1.5 (1.5) = 6.0 second timeout, 4 packets sent
			msg.resendTime = time + RESEND_TIME;

			// move it to the end of the list
			m_ReliableMessages.Unlink(index);
			m_ReliableMessages.LinkToTail(index);

			// next packet
			continue;
		}

		// target has failed to respond, remove the target and respond with a failed message
		WriteToLog("Could not deliver packet: %d (os:%d)\n", msg.message->GetMsgID(), msg.sequenceNumber);

		// send back a send failure message to the app
		// convert the send message into a receive message
		CSendMessage *sendMsg = dynamic_cast<CSendMessage *>(msg.message);
		if (sendMsg)
		{
			IBinaryBuffer *buf = sendMsg->GetBuffer();
			
			buf->SetPosition(buf->GetBufferData());
			buf->Advance(buf->GetReservedSize());
			CReceiveMessage *failMsg = new CReceiveMessage(buf, true);

			if (failMsg->IsValid())
			{
				failMsg->SetFailed();
				failMsg->SetNetAddress(target.netAddress);
				failMsg->SetSessionID(sendMsg->SessionID());

				int newIndex = m_FailedMsgs.AddToTail();
				FailedMsg_t &fmsg = m_FailedMsgs[newIndex];
				fmsg.message = failMsg;
			}
			else
			{
				delete failMsg;
			}
		}

		// target not responding, so cancel the connection
		// remove from target map
		int mapindex = FindTargetIndexByAddress(target.netAddress);
		assert(m_TargetMap.IsValidIndex(mapindex));
		m_TargetMap.RemoveAt(mapindex);

		// remove target from list
		m_TargetList.Remove(msg.networkTargetHandle);
		
		// message will automatically be delete since it's target is gone
	}
}