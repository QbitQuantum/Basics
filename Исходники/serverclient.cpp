void ServerClient::sendAddObject(uint16_t id)
{
	Object *object = g_game->getObjectById(id);
	if(!object)
		return;

	ObjectType type = object->getObjectType();
	Packet packet;
	packet.push<uint8_t>((uint8_t)NetworkHeader::AddObject);
	packet.push<uint16_t>(id);
	packet.push<uint8_t>((uint8_t)type);
	packet.push<uint8_t>(object->getPosition().x);
	packet.push<uint8_t>(object->getPosition().y);
	packet.push<uint8_t>(object->getMoveSpeed());
	packet.push<uint8_t>(object->getFlags());

	if(type == ObjectType::Bomb)
	{
		packet.push<uint8_t>(object->getOwner()->getId());
		packet.push<uint8_t>(object->getPower());
		packet.push<uint8_t>(object->getRadius());
		packet.push<uint16_t>(object->getOwner()->getBombDetonationTime());
	}
	else if(type == ObjectType::Crate)
		packet.push<uint8_t>(object->getCrate()->getHealth());
	else if(type == ObjectType::Effect)
	{
		packet.push<uint16_t>(object->getPoint().x);
		packet.push<uint16_t>(object->getPoint().y);
		packet.push<uint8_t>(object->getEffect()->getSteps());
		packet.push<uint8_t>((object->getEffect()->isInfinite() ? 1 : 0));
	}
	else if(type == ObjectType::Fireball)
	{
		packet.push<uint8_t>(object->getOwner()->getId());
		packet.push<uint8_t>(object->getPower());
		packet.push<uint8_t>((uint8_t)object->getFireball()->getDirection());
	}
	else if(type == ObjectType::Powerup)
		packet.push<uint8_t>((uint8_t)object->getPowerup()->getType());

	packet.pushString(object->getTexture());
	packet.write(m_socket);
}