/// Step forward the simulation
void Box2DSystem::update(const Time& deltaTime)
{
	mSimulation->Step(deltaTime.seconds(), 8, 8);

	// Compute stuff with the world
	ComponentManager* colliderBoxManager = mWorld->getComponentManager<CColliderBox>();
	ComponentManager* transformManager = mWorld->getComponentManager<CTransform>();

	for (std::size_t i = 0; i < colliderBoxManager->getInstanceCount(); ++i)
	{
		CColliderBox* boxCollider = (CColliderBox*)colliderBoxManager->getInstance(i);
		CTransform* transform = (CTransform*)transformManager->getComponentFromEntity(colliderBoxManager->getInstanceEntity(i));
		if (!transform)
		{
			mWorld->createComponent(CTransform(), colliderBoxManager->getInstanceEntity(i));
			transform = (CTransform*)transformManager->getComponentFromEntity(colliderBoxManager->getInstanceEntity(i));
		}

		if (!boxCollider->userData)
		{
			b2BodyDef groundBodyDef2;
			groundBodyDef2.type = boxCollider->_isDynamic ? b2_dynamicBody : b2_staticBody;
			groundBodyDef2.position = b2Vec2(transform->getPosition().x, transform->getPosition().y);
			b2Body* groundBody2 = mSimulation->CreateBody(&groundBodyDef2);

			b2PolygonShape groundShape2;
			groundShape2.SetAsBox(10.f, 10.f);
			groundBody2->CreateFixture(&groundShape2, 1.f);

			groundBody2->SetUserData(boxCollider);
			boxCollider->userData = groundBody2;
		}
		else
		{
			b2Body* boxColliderBody = (b2Body*)boxCollider->userData;
			transform->position.x = boxColliderBody->GetPosition().x;
			transform->position.y = boxColliderBody->GetPosition().y;
			transform->rotation = Quaternion::fromMatrix(mat4::rotatez(boxColliderBody->GetAngle()));
		}
	}

	// Now let's go through the actors to find stuff in them
	for (std::size_t i = 0; i < mWorld->actors.size(); ++i)
	{
		Actor* actor = mWorld->actors[i];
		SCColliderBox* box = dynamic_cast<SCColliderBox*>(actor->getRootComponent());
		if (box)
		{
			if (!box->userData)
			{
				b2BodyDef groundBodyDef2;
				groundBodyDef2.type = box->_isDynamic ? b2_dynamicBody : b2_staticBody;
				groundBodyDef2.position = b2Vec2(actor->getActorLocation().x, actor->getActorLocation().y);
				b2Body* groundBody2 = mSimulation->CreateBody(&groundBodyDef2);

				b2PolygonShape groundShape2;
				groundShape2.SetAsBox(10.f, 10.f);
				groundBody2->CreateFixture(&groundShape2, 1.f);

				groundBody2->SetUserData(box);
				box->userData = groundBody2;

				box->rigidBody = new RigidBodyBox2D(groundBody2);
				
			}

			// Apply manual forces
			b2Body* boxColliderBody = (b2Body*)box->userData;
			

			CTransform transform = box->t;

			
			transform.position.x = boxColliderBody->GetPosition().x;
			transform.position.y = boxColliderBody->GetPosition().y;
			transform.rotation = Quaternion::fromMatrix(mat4::rotatez(boxColliderBody->GetAngle()));

			// Push the new physics transform back to the actor
			actor->setTransform(transform);
		}
	}
}