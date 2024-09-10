void VehicleObject::setPosition(const glm::vec3& pos)
{
	GameObject::setPosition(pos);
	if( collision->getBulletBody() ) {
		auto bodyOrigin = btVector3(position.x, position.y, position.z);
		for(auto& part : dynamicParts)
		{
			if( part.second.body == nullptr ) continue;
			auto body = part.second.body;
			auto rel = body->getWorldTransform().getOrigin() -
					bodyOrigin;
			body->getWorldTransform().setOrigin(
				btVector3(pos.x + rel.x(), pos.y + rel.y(), pos.z + rel.z()));
		}

		auto t = collision->getBulletBody()->getWorldTransform();
		t.setOrigin(btVector3(pos.x, pos.y, pos.z));
		collision->getBulletBody()->setWorldTransform(t);
	}
}