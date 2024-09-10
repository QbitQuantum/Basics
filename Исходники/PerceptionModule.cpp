void PerceptionModule::UpdatePerception()
{
	const float viewDistanceSqr = mViewDistance*mViewDistance;
	const float viewSpan = cos(mViewAngle * 0.5f);

	//const AgentList& agents = mOwner.GetWorld().GetAgentList();
	const std::vector<Agent*> agents = mOwner.GetWorld().GetAgents();

	//AgentList::const_iterator iter = agents.begin();
	int size = agents.size();
	//for(; iter!= agents.end(); ++iter)
	for (int i = 0; i < size; ++i)
	{
		const Agent* agent = agents[i]; //(*iter);
		// Ignore self
		if (&mOwner == agent)
		{
			continue;
		}

		// Check if agent is in range
		const SVector2 ownerToTarget = agent->GetPosition() - mOwner.GetPosition();
		const float distanceSqr = LengthSquared(ownerToTarget);
		if (distanceSqr > viewDistanceSqr)
		{
			continue;
		}

		// Check if agent is in view cone
		const SVector2 dirToTarget = Normalize(ownerToTarget);
		const float dot = Dot(mOwner.GetHeading(), dirToTarget);
		if (dot < viewSpan)
		{
			continue;
		}

		// Check if we have line of site
		if (!mOwner.GetWorld().HasLOS(mOwner.GetPosition(), agent->GetPosition()))
		{
			continue;
		}

		// Check if we have a record for this agent
		bool hasRecord = false;
		MemoryRecords::iterator memoryIter = mMemoryRecords.begin();
		while (memoryIter != mMemoryRecords.end())
		{
			PerceptionData& record = (*memoryIter);
			if (record.pAgent == agent)
			{
				record.lastSeenLocation = agent->GetPosition();
				record.lastRecordedTime = 0.0f;
				record.level = Confirm;
				hasRecord = true;
				break;
			}
			++memoryIter;
		}

		// Add a new record if agent is new
		if (!hasRecord)
		{
			PerceptionData newRecord;
			newRecord.pAgent = agent;
			newRecord.lastSeenLocation = agent->GetPosition();
			newRecord.lastRecordedTime = 0.0f;
			newRecord.level = Confirm;
			mMemoryRecords.push_back(newRecord);
		}
	}
}