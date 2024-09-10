	void CollisionAvoidance::Update(SteeringOutput* output)
	{
		float shortestTime = FLT_MAX;

		//for now
		const float DIAMETER = 2.0f;

		Agent* firstTarget = nullptr;
		float  firstMinSeparation = 0;
		float  firstDistance = 0;
		Vec3   firstRelativePos;
		Vec3   firstRelativeVel;

		//used in for loop
		Vec3 relativePos;
		Vec3 relativeVel;
		float relativeSpeed   = 0.0f;
		float timeToCollision = 0.0f;
		float distance		  = 0.0f;
		float minSeparation   =	0.0f;									  

		AgentMap* map = TheAIManager::Instance() ->GetAgentMap();
		for(auto it = map ->begin(); it != map ->end(); ++it)
		{
			relativePos = it ->second ->GetPos() - m_parent ->GetPos();
			relativeVel = it ->second ->GetVel() - m_parent ->GetVel();
			relativeSpeed = relativeVel.Length();
			timeToCollision = DotProduct(firstRelativePos, relativeVel) / (relativeSpeed * relativeSpeed);

			distance = relativePos.Length();
			minSeparation = distance - relativeSpeed * shortestTime;

			if(minSeparation > DIAMETER) continue;

			if((timeToCollision > 0) && (timeToCollision < shortestTime))
			{
				shortestTime = timeToCollision;
				firstTarget = it ->second;
				firstMinSeparation = minSeparation;
				firstDistance = distance;
				firstRelativePos = relativePos;
				firstRelativeVel = relativeVel;
			}
		}

		if(!firstTarget) return;

		if((firstMinSeparation <= 0) || (distance < DIAMETER))
			relativePos = firstTarget ->GetPos() - m_parent ->GetPos();

		else
			relativePos = firstRelativePos + firstRelativeVel * shortestTime;

		relativePos.Normalize();
		output ->linear = relativePos * m_parent ->GetMaxAcc();
	}