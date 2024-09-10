	void AutotrainerSipCall::OnForkingOccured(const IRemoteParticipant *origCall,
		Utils::SafeRef<IRemoteParticipant> newCall,
		const resip::SipMessage &msg)
	{
		newCall->DestroyParticipant();
	}