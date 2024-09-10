void KviIrcConnectionRequestQueue::timerSlot()
{
	if(m_channels.isEmpty())
	{
		m_timer.stop();
	} else {
		KviChannelWindow * pChan = m_channels.head();
		QByteArray encodedChan = pChan->connection()->encodeText(pChan->target()).data();
		/* The following switch will let the execution flow pass-through if any request type
		 * is currently disabled (or not available on the server). Channel's "MODE" request is
		 * the only mandatory request.
		 */
		switch(m_curType)
		{
			case BanException:
				if(pChan->serverInfo()->supportedListModes().contains('e') &&
					!KVI_OPTION_BOOL(KviOption_boolDisableBanExceptionListRequestOnJoin) &&
					!(	pChan->serverInfo()->getNeedsOpToListModeseI() &&
						!pChan->isMeOp()
					 )
				)
				{
					if(!pChan->connection()->sendFmtData("MODE %s e",encodedChan.data()))
						clearAll(); // disconnected
					else pChan->setSentListRequest('e');
					m_curType = Invite;
					break;
				}
			case Invite:
				if(pChan->serverInfo()->supportedListModes().contains('I') &&
					!KVI_OPTION_BOOL(KviOption_boolDisableInviteListRequestOnJoin) &&
					!(	pChan->serverInfo()->getNeedsOpToListModeseI() &&
						!pChan->isMeOp()
					 )
				)
				{
					if(!pChan->connection()->sendFmtData("MODE %s I",encodedChan.data()))
						clearAll(); // disconnected
					else pChan->setSentListRequest('I');
					m_curType = QuietBan;
					break;
				}
			case QuietBan:
				if(pChan->serverInfo()->supportedListModes().contains('q') &&
					!KVI_OPTION_BOOL(KviOption_boolDisableQuietBanListRequestOnJoin))
				{
					if(!pChan->connection()->sendFmtData("MODE %s q",encodedChan.data()))
						clearAll(); // disconnected
					else pChan->setSentListRequest('q');
					m_curType = Who;
					break;
				}
			case Who:
				if(!KVI_OPTION_BOOL(KviOption_boolDisableWhoRequestOnJoin))
				{
					// TODO: cleanup
					pChan->connection()->stateData()->setLastSentChannelWhoRequest(kvi_unixTime());
					if(pChan->connection()->lagMeter())
					{
						KviCString tmp;
						if(pChan->serverInfo()->supportsWhox())
							tmp.sprintf("WHO %s %acdfhlnrsu",encodedChan.data());
						else
							tmp.sprintf("WHO %s",encodedChan.data());
						pChan->connection()->lagMeter()->lagCheckRegister(tmp.ptr(),60);
					}
					if(pChan->serverInfo()->supportsWhox())
					{
						if(!pChan->connection()->sendFmtData("WHO %s %acdfhlnrsu",encodedChan.data()))
							clearAll(); // disconnected
						else pChan->setSentWhoRequest();
					} else {
						if(!pChan->connection()->sendFmtData("WHO %s",encodedChan.data()))
							clearAll(); // disconnected
						else pChan->setSentWhoRequest();
					}
					m_curType = Ban;
					break;
				}
			case Ban:
				if(!KVI_OPTION_BOOL(KviOption_boolDisableBanListRequestOnJoin))
				{
					if(!pChan->connection()->sendFmtData("MODE %s b",encodedChan.data()))
					{
						clearAll(); // disconnected
					} else {
						pChan->setSentListRequest('b');
						m_channels.dequeue();
					}
					m_curType = Mode;
					break;
				}
			default:
				// we're at the end of the list
				m_channels.dequeue();
				pChan->checkChannelSync();
				m_curType = Mode;
				if(m_channels.isEmpty())
				{
					m_timer.stop();
					return;
				}
				pChan = m_channels.head();
				encodedChan = pChan->connection()->encodeText(pChan->target());
			case Mode:
				if(!pChan->connection()->sendFmtData("MODE %s",encodedChan.data()))
				{
					clearAll(); // disconnected
					break;
				}
				m_curType = BanException;
				break;
		}
	}
}