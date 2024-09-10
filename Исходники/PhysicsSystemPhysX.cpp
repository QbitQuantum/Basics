void PhysicsSystemPhysX::update(const Time& deltaTime)
{	
	// Step the simulation forward
	mScene->simulate(deltaTime.seconds());

	if (mScene->fetchResults())
	{

		// Now let's push back the transforms into the World
		ComponentManager* colliderBoxManager = getWorld()->getComponentManager<CColliderBox>();
		ComponentManager* transformManager = getWorld()->getComponentManager<CTransform>();
		for (std::size_t i = 0; i < colliderBoxManager->size(); ++i)
		{
			Entity E = colliderBoxManager->getInstanceEntity(i);
			CColliderBox* box = (CColliderBox*)colliderBoxManager->getInstance(i);
			CTransform* transform = (CTransform*)transformManager->getComponentFromEntity(E);

			// Create
			if (box->userData == nullptr)
			{
				PxMaterial* boxMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.1f);

				PxRigidDynamic* boxActor = mPhysics->createRigidDynamic(PxTransform(transform->position.x, transform->position.y, transform->position.z));
				boxActor->createShape(PxBoxGeometry(10.f, 10.f, 10.f), *boxMaterial);
				PxRigidBodyExt::updateMassAndInertia(*boxActor, 30);
				//boxActor->setLinearVelocity(PxVec3(0, -50, 0));

				mScene->addActor(*boxActor);
				box->userData = boxActor;
			}
			// Update
			else
			{
				PxRigidDynamic* boxActor = (PxRigidDynamic*)box->userData;
				PxTransform pxTransform = boxActor->getGlobalPose();

				transform->position.x = pxTransform.p.x;
				transform->position.y = pxTransform.p.y;
				transform->position.z = pxTransform.p.z;

				transform->rotation.x = pxTransform.q.x;
				transform->rotation.y = pxTransform.q.y;
				transform->rotation.z = pxTransform.q.z;
				transform->rotation.w = pxTransform.q.w;
			}
		}

		syncActors();
	}
}