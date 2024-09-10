void FrustumPhysicsObject::onUpdate(float delta)
{
	btMatrix3x3 view = convert(itrCamera_3.at(attributeIndex_)->mat_view);
	btVector3 pos =  convert(itrCamera_3.at(attributeIndex_)->ptr_spatial->ptr_position->position);
	btQuaternion q;
	view.getRotation(q);
	btTransform world = getWorldTransform();
	world.setRotation(q);
	world.setOrigin(pos);
	setWorldTransform(world);
	
	setCollisionShape(CollisionShapes::Instance()->getFrustumShape(attributeIndex_));
}