void PhysXPhysics::VSyncVisibleScene()
{
	for (ActorIdToPysXRigidBodyTable::const_iterator it = m_actorRigidBodyMap.begin(); it != m_actorRigidBodyMap.end(); it++)
	{
		ActorId const id = it->first;

		PxTransform pxLoc = it->second->getGlobalPose();
		Mat4x4 loc;
		PxMatrixToMat4x4(PxMat44(pxLoc), &loc);
		
		Actor* pActor = g_pApp->m_pGame->VGetActor(id);
		if (pActor)
		{
			TransformComponent* pTransformComponent = pActor->GetComponent<TransformComponent>(TransformComponent::g_Name);

			if (pTransformComponent)
			{
				if (pTransformComponent->GetTransform() != loc)
				{
					Vec3 rot = loc.GetYawPitchRoll();
					pTransformComponent->SetPosition(loc.GetPosition());
					pTransformComponent->SetRotation(Vec3(XMConvertToDegrees(rot.x), XMConvertToDegrees(rot.y), XMConvertToDegrees(rot.z)));
					EventDataPtr pEvent(BE_NEW EvtData_Move_Actor(id, loc));
					IEventManager::Get()->VQueueEvent(pEvent);
				}
			}
		}
	}
}