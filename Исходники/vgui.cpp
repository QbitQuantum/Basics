//-----------------------------------------------------------------------------
// Purpose: message pump
//			loops through and sends all active messages
//			note that more messages may be posted during the process
//-----------------------------------------------------------------------------
bool CVGui::DispatchMessages()
{
	int time = g_pSystem->GetTimeMillis();

	m_InDispatcher = true;
	bool doneWork = (m_MessageQueue.Count() > 12);

	bool bUsingDelayedQueue = (m_DelayedMessageQueue.Count() > 0);

	// Need two passes because we send the mouse move message after all
	// other messages are done, but the mouse move message may itself generate
	// some more messages
	int nPassCount = 0;
	while ( nPassCount < 2 )
	{
		while (m_MessageQueue.Count() > 0 || (m_SecondaryQueue.Count() > 0) || bUsingDelayedQueue)
		{
			// get the first message
			MessageItem_t *messageItem = NULL;
			int messageIndex = 0;

			// use the secondary queue until it empties. empty it after each message in the
			// primary queue. this makes primary messages completely resolve 
			bool bUsingSecondaryQueue = (m_SecondaryQueue.Count() > 0);
			if (bUsingSecondaryQueue)
			{
				doneWork = true;
				messageIndex = m_SecondaryQueue.Head();
				messageItem = &m_SecondaryQueue[messageIndex];
			}
			else if (bUsingDelayedQueue)
			{
				if (m_DelayedMessageQueue.Count() >0)
				{
					messageItem = (MessageItem_t*)&m_DelayedMessageQueue.ElementAtHead();
				}
				if (!messageItem || messageItem->_arrivalTime > time)
				{
					// no more items in the delayed message queue, move to the system queue
					bUsingDelayedQueue = false;
					continue;
				}
			}
			else
			{
				messageIndex = m_MessageQueue.Head();
				messageItem = &m_MessageQueue[messageIndex];
			}

			// message debug code 

			if ( m_bDebugMessages )
			{
				char *qname = bUsingSecondaryQueue ? "Secondary" : "Primary";

				if (strcmp(messageItem->_params->GetName(), "Tick")
					&& strcmp(messageItem->_params->GetName(), "MouseFocusTicked") 
					&& strcmp(messageItem->_params->GetName(), "KeyFocusTicked")
					&& strcmp(messageItem->_params->GetName(), "CursorMoved"))
				{
					if (!stricmp(messageItem->_params->GetName(), "command"))
					{
						g_pIVgui->DPrintf2( "%s Queue dispatching command( %s, %s -- %i )\n", qname, messageItem->_params->GetName(), messageItem->_params->GetString("command"), messageItem->_messageID );
					}
					else
					{
						g_pIVgui->DPrintf2( "%s Queue dispatching( %s -- %i )\n", qname ,messageItem->_params->GetName(), messageItem->_messageID );
					}
				}
			}

			// send it
			KeyValues *params = messageItem->_params;

			// Deal with special internal cursor movement messages
			if ( messageItem->_messageTo == 0xFFFFFFFF )
			{
				if ( !Q_stricmp( params->GetName(), "SetCursorPosInternal" ) )
				{
					int nXPos = params->GetInt( "xpos", 0 );
					int nYPos = params->GetInt( "ypos", 0 );
					g_pInput->UpdateCursorPosInternal( nXPos, nYPos );
				}
			}
			else
			{
				VPanel *vto = (VPanel *)g_pIVgui->HandleToPanel(messageItem->_messageTo);
				if (vto)
				{
					//			Msg("Sending message: %s to %s\n", params ? params->GetName() : "\"\"", vto->GetName() ? vto->GetName() : "\"\"");
					vto->SendMessage(params, g_pIVgui->HandleToPanel(messageItem->_from));
				}
			}

			// free the keyvalues memory
			// we can't reference the messageItem pointer anymore since the queue might have moved in memory
			if (params)
			{
				params->deleteThis();
			}

			// remove it from the queue
			if (bUsingSecondaryQueue)
			{
				m_SecondaryQueue.Remove(messageIndex);
			}
			else if (bUsingDelayedQueue)
			{
				m_DelayedMessageQueue.RemoveAtHead();
			}
			else
			{
				m_MessageQueue.Remove(messageIndex);
			}
		}

		++nPassCount;
		if ( nPassCount == 1 )
		{
			// Specifically post the current mouse position as a message
			g_pInput->PostCursorMessage();
		}
	}

	// Make sure the windows cursor is in the right place after processing input 
	// Needs to be done here because a message provoked by the cursor moved
	// message may move the cursor also
	g_pInput->HandleExplicitSetCursor( );

	m_InDispatcher = false;
	return doneWork;
}