/*
  Need store the pose after simulation
*/
void MxActor::ActionAfterSimulation()
{
	// update pose to max node
	if(getInteractivity() != RB_DYNAMIC)
		return;

	// update rigid body's last pose
	//ccMaxNode* pn = ccMaxWorld::FindNode(m_node);
	assert(maxNodeActor);
	Matrix3 globalPose;
	globalPose.IdentityMatrix();

	if (m_bulletBody)
	{
		NxActorDesc&  actorDesc  = m_desc;

		btTransform localTrans;
		max2Bullet(actorDesc.localPose,localTrans);

		btTransform maxWorldTrans = m_bulletBody->getWorldTransform()*localTrans.inverse();

		bullet2Max(maxWorldTrans,globalPose);
		//@todo: need correction for boxes (off center etc)

		maxNodeActor->SetSimulatedPose(globalPose);
		Matrix3 poseTM = maxNodeActor->GetCurrentTM();
		SaveLastPose(poseTM);
	}
}