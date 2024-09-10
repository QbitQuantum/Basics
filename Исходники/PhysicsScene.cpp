void PhysicsWorld::SimulateIslands(const TimeStep &timeStep)
{
	// clear & update flags
	for (RigidBody &body : mRigidBodies)
	{
		// body
		body.mFlags.Clear(PhysicsFlags::ISLAND);
		body.mFlags.Set(PhysicsFlags::CAN_SLEEP);

		// joints
		for (auto &jointEdge : body.mJointEdges)
		{
			Joint &joint = *jointEdge.joint;
			joint.mFlags.Clear(PhysicsFlags::ISLAND);

			if (!joint.mAllowSleep)
				body.mFlags.Clear(PhysicsFlags::CAN_SLEEP);
		}

		// manifolds
		for (auto &collider : body.mColliders)
		for (auto &contactEdge : collider.mContactEdges)
			contactEdge.manifold->flags.Clear(PhysicsFlags::ISLAND);
	}

	// build & solve islands
	const float linearDampFactor = 1.0f - Clamp(mParams.linearDamping  * timeStep.dt, 0.0f, 1.0f);
	const float angularDampFactor = 1.0f - Clamp(mParams.angularDamping * timeStep.dt, 0.0f, 1.0f);
	 float sleepLinearThresholdSQ = mParams.sleepLinearThreshold * mParams.sleepLinearThreshold;
	const float sleepAngularThresholdSQ = mParams.sleepAngularThreshold * mParams.sleepAngularThreshold;
	Island island(mGravity, linearDampFactor, angularDampFactor);
	IN_LIST(RigidBody, mIslandSearchLink) queue;
	for (auto &seed : mRigidBodies)
	{
		// already belongs to one island, continue
		if (seed.mFlags.Test(PhysicsFlags::ISLAND))
			continue;

		// skip sleeping bodies
		if (mParams.allowSleep && !seed.IsAwake())
			continue;

		// skip static bodies
		if (seed.mType == RigidBody::STATIC)
			continue;

		// clear island and construct a new island 
		// using current rigid body as a "seed"
		float minSleepTime = FLT_MAX;
		island.Clear();
		seed.mFlags.Set(PhysicsFlags::ISLAND);
		queue.push_back(&seed);

		// build island
		// breadth first search (BFS) on the constraint graph (using a FIFO queue)
		while (!queue.empty())
		{
			// pop top body off the queue
			RigidBody &body = *queue.pop_front(); // if we use pop_back then this becomes a depth first search (DFS)

			// skip static bodies
			if (body.mType == RigidBody::STATIC)
				continue;

			island.Add(body);

			if (!body.IsAwake())
			{
				// make sure the body stays awake
				body.SetAwake(true);
			}

			if (body.mFlags.Test(PhysicsFlags::CAN_SLEEP)
				&& body.mLinearVelocity.LengthSq() < sleepLinearThresholdSQ
				&& body.mAngularVelocity.LengthSq() < sleepAngularThresholdSQ)
				body.mSleepTimer += timeStep.dt;
			else
				body.mSleepTimer = 0.0f;

			minSleepTime = Min(minSleepTime, body.mSleepTimer);

			// add joints to island (loop through joint edges)
			for (auto &edge : body.mJointEdges)
			{
				Joint &joint = *edge.joint;
				if (!joint.mFlags.Test(PhysicsFlags::ISLAND))
				{
					// add other rigid body (if existent) to island
					if (edge.other)
					{
						RigidBody &otherBody = *edge.other;
						if (!otherBody.mFlags.Test(PhysicsFlags::ISLAND) && otherBody.mType != RigidBody::STATIC)
						{
							otherBody.mFlags.Set(PhysicsFlags::ISLAND);
							queue.push_back(&otherBody);
						}
					}

					// add joint to island
					joint.mFlags.Set(PhysicsFlags::ISLAND);
					island.Add(joint);
				}
			} // end of looping through joint edges

			// add contact manifolds to the island
			for (auto &collider : body.mColliders)
			{
				for (auto &edge : collider.mContactEdges)
				{
					ContactManifold &manifold = *edge.manifold;
					if (manifold.isColliding && !manifold.flags.Test(PhysicsFlags::ISLAND))
					{
						// add other rigid body to island
						RigidBody &otherBody = *edge.other->mParent;
						if (!otherBody.mFlags.Test(PhysicsFlags::ISLAND) && otherBody.mType != RigidBody::STATIC)
						{
							otherBody.mFlags.Set(PhysicsFlags::ISLAND);
							queue.push_back(&otherBody);
						}

						// add manifold to island
						manifold.flags.Set(PhysicsFlags::ISLAND);
						if (!manifold.colliderA->mIsSensor && !manifold.colliderB->mIsSensor) // skip sensors
							island.Add(manifold);
					} // end of looping through contact edges
				} // end of looping through contact edges

			} // end of looping through colliders
		} // end of building island

		// solve island or put island to sleep
		if (minSleepTime < mParams.sleepTimeThreshold)
		{
			island.Step(timeStep);

			// post-solve
			for (auto &body : island.mRigidBodies)
			{
				// record energy (ignores 0.5 constant factor)
				if (body.mType != RigidBody::STATIC)
				{
					const MassData &m = body.mMassData;
					mStats.energy += m.mass * body.mLinearVelocity.LengthSq();
					mStats.energy += body.mAngularVelocity.Dot(m.unitLocalInertiaTensor * body.mAngularVelocity);
				}
			} // end of post-solve
		}
		else
			island.Sleep(timeStep);

		// update island stats
		timeStep.stats.minIslandSize = Min(island.NumRigidBodies(), timeStep.stats.minIslandSize);
		timeStep.stats.maxIslandSize = Max(island.NumRigidBodies(), timeStep.stats.maxIslandSize);
		++timeStep.stats.islands;
	}
	if (!timeStep.stats.islands)
		timeStep.stats.minIslandSize = timeStep.stats.maxIslandSize = 0;
	timeStep.stats.avgIslandSize = timeStep.stats.islands ? static_cast<float>(timeStep.stats.rigidBodies) / timeStep.stats.islands : 0.0f;

}