	MsgRemoteParticipant::MsgRemoteParticipant(iCore::MsgThread &thread,
		ConversationManager &conversationManager,
		boost::function<void (IRemoteParticipant*, bool)> registrator,
		Utils::SafeRef<IRemoteParticipant> remoteParticipant) :
		MsgObject(thread),
		m_conversationManager(conversationManager),
		m_registrator(registrator)
	{
		m_isDestroyed = false;
		m_registrator(this, true);

		boost::shared_ptr<ConversationProfile> conversationProfile =
			remoteParticipant->GetConversationProfile();

		ESS_ASSERT(conversationProfile != 0);

		m_media.reset(new MediaWrapper(m_user,
			conversationProfile->GetNatIpConverter()));

		m_remoteParticipant = remoteParticipant;

		m_remoteParticipant->LinkUser(this);
	}