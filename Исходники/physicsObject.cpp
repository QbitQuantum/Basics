bool PhysicsObject::init(unsigned int attributeIndex, short collisionFilterGroup)
{
	if(attributeIndex < 0)
	{
		return false;
	}
	attributeIndex_ = attributeIndex;
	collisionFilterGroup_ = collisionFilterGroup;

	//Get the init data from a physics attribute
	AttributePtr<Attribute_Physics> ptr_physics = itrPhysics_.at(attributeIndex);
	btScalar mass = static_cast<btScalar>(ptr_physics->mass);

	//Resolve mass, local inertia of the collision shape, and also the collision shape itself.
	btCollisionShape* collisionShape = subClassSpecificCollisionShape();
	if(collisionShape != nullptr)
	{
		setCollisionShape(collisionShape);
	}
	else
	{
		ERROR_MESSAGEBOX("Error in PhysicsObject::init. Expected collision shape pointer unexpectedly set to nullptr. Using default shape instead.");
		setCollisionShape(CollisionShapes::Instance()->getDefaultShape());
	}
	
	btVector3 localInertia = subClassCalculateLocalInertiaHook(mass);
	setMassProps(mass, localInertia); //Set inverse mass and inverse local inertia
	updateInertiaTensor();
	if((getCollisionFlags() & btCollisionObject::CF_STATIC_OBJECT))
	{
		btTransform world;

		AttributePtr<Attribute_Spatial> ptr_spatial = itrPhysics_.at(attributeIndex_)->ptr_spatial;
		AttributePtr<Attribute_Position> ptr_position = ptr_spatial->ptr_position;
 		world.setOrigin(convert(ptr_position->position));
		world.setRotation(convert(ptr_spatial->rotation));
		setWorldTransform(world);  //Static physics objects: transform once
	}
	else
	{
		//Non-static physics objects: let a derived btMotionState handle transforms.
		MotionState* customMotionState = new MotionState(attributeIndex);
		setMotionState(customMotionState);

		setAngularVelocity(btVector3(ptr_physics->angularVelocity.x,
										ptr_physics->angularVelocity.y,
										ptr_physics->angularVelocity.z));
		setLinearVelocity(btVector3(ptr_physics->linearVelocity.x,
										ptr_physics->linearVelocity.y,
										ptr_physics->linearVelocity.z));
		//Gravity is set after "addRigidBody" for non-static physics objects
	}

	if(ptr_physics->collisionResponse)
	{
		setCollisionFlags(getCollisionFlags() & ~CF_NO_CONTACT_RESPONSE); //Activate collision response
	}
	else
	{
		setCollisionFlags(getCollisionFlags() | CF_NO_CONTACT_RESPONSE); //Deactivate collision response
	}
	
	return subClassSpecificInitHook();
}