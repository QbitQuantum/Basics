void SampleSubmarine::explode(PxRigidActor* actor, const PxVec3& explosionPos, const PxReal explosionStrength)
{
	size_t numRenderActors = mRenderActors.size();
	for(PxU32 i = 0; i < numRenderActors; i++)
	{
		if(&(mRenderActors[i]->getPhysicsShape()->getActor()) == actor)
		{
			PxShape* shape = mRenderActors[i]->getPhysicsShape();
			PxTransform pose = PxShapeExt::getGlobalPose(*shape);
			
			PxGeometryHolder geom = shape->getGeometry();

			// create new actor from shape (to split compound)
			PxRigidDynamic* newActor = mPhysics->createRigidDynamic(pose);
			if(!newActor) fatalError("createRigidDynamic failed!");

			PxShape* newShape = newActor->createShape(geom.any(), *mMaterial);
			newShape->userData = mRenderActors[i];
			mRenderActors[i]->setPhysicsShape(newShape);
			
			newActor->setActorFlag(PxActorFlag::eVISUALIZATION, true);
			newActor->setLinearDamping(10.5f);
			newActor->setAngularDamping(0.5f);
			PxRigidBodyExt::updateMassAndInertia(*newActor, 1.0f);
			mScene->addActor(*newActor);
			mPhysicsActors.push_back(newActor);
			
			PxVec3 explosion = pose.p - explosionPos;
			PxReal len = explosion.normalize();
			explosion *= (explosionStrength / len);
			newActor->setLinearVelocity(explosion);
			newActor->setAngularVelocity(PxVec3(1,2,3));

		}
	}

	removeActor(actor);
}