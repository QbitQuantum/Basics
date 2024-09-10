	bool IsPointOnMyFlank(EntityId actorEntityID, const Vec3& actorPos, const Vec3& targetPos, const Vec3& pointPos)
	{
		CAIBattleFrontGroup* group = gGameAIEnv.battleFrontModule->GetGroupForEntity(actorEntityID);
		ASSERT_IS_NOT_NULL(group);
		if (!group || group->GetMemberCount() == 1)
			return true; // I'm alone so this is my flank

		const Vec3& groupAveragePos = group->GetAveragePosition();

		// Set up a coordinate system where Y corresponds to the direction
		// from the battle group's center position towards the target
		Vec3 Y = (targetPos - groupAveragePos);
		Vec3 X = Vec3(0,0,-1).Cross(Y);

		// Calculate flank side sign
		Vec3 vGroupAveragePosToActor = actorPos - groupAveragePos;
		float flankSideSign = (vGroupAveragePosToActor.Dot(X) > 0.0f) ? 1.0f : -1.0f; // Flank side sign (-1 for left, +1 for right)

		// Calculate how far the point is on the X-axis
		Vec3 groupAveragePosToPoint = pointPos - groupAveragePos;
		float pointDistOnXAxis = groupAveragePosToPoint.Dot(X);

		bool pointIsOnMyFlank = pointDistOnXAxis * flankSideSign > 0.0f;
		return pointIsOnMyFlank;
	}