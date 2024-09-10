	bool ParticleChain::checkPenetration(const Ogre::Vector3 &position, Ogre::Vector3 &closestSurfacePos, Ogre::Vector3 &collisionNormal)
	{
		PxShape *hit = nullptr;
		PxVec3 pxPos = Convert::toPx(position);
		if (mPhysXScene->getPxScene()->overlapAny(PxSphereGeometry(0.05f), PxTransform(pxPos), hit))
		{
			PxVec3 actorCenter = hit->getActor().getWorldBounds().getCenter();
			PxVec3 rayDir = actorCenter - pxPos;
			rayDir.normalize();
			PxVec3 rayOrigin = pxPos - rayDir.multiply(PxVec3(0.2f, 0.2f, 0.2f));
			if (mPhysXScene->getPxScene()->overlapAny(PxSphereGeometry(0.05f), PxTransform(rayOrigin), hit)) return false;
			PxRaycastHit rayHit;
			if (mPhysXScene->getPxScene()->raycastSingle(rayOrigin, rayDir,  0.2f, PxSceneQueryFlag::eIMPACT|PxSceneQueryFlag::eNORMAL|PxSceneQueryFlag::eDISTANCE, rayHit))
			{
				closestSurfacePos = Convert::toOgre(rayHit.impact);
				collisionNormal = Convert::toOgre(rayHit.normal);
				return true;
			}
		}
		return false;
	}