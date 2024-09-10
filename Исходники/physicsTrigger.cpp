PhysicsTrigger::PhysicsTrigger(Trigger *trigger) {
	// We use the radius of the scale for the trigger since it takes half extents.
	auto shape = new btBoxShape(btConvert(trigger->getScale() * 0.5f));
	shape->setMargin(0.01f);

	// Set the physic's object transformation matrix to be the same
	// as the transform matrix of the game object.
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btConvert(trigger->getPosition()));
	transform.setRotation(btConvert(trigger->getRotation()));

	auto state = new btDefaultMotionState();
	state->setWorldTransform(transform);
	mActor = new btRigidBody(0.0f, state, shape);

	// Set the trigger flag on the actor.
	// CF_NO_CONTACT_RESPONSE set's it to be a trigger interaction
	// CF_CUSTOM_MATERIAL_CALLBACK let's us get notifications.
	mActor->setCollisionFlags(
		mActor->getCollisionFlags() | 
		btCollisionObject::CF_NO_CONTACT_RESPONSE | 
		btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK
	);

	// create a relationship between the trigger and the physics representation
	mTrigger = trigger;
}