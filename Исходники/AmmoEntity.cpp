// Return false if the entity is to be destroyed
bool CAmmoEntity::Update(TFloat32 updateTime)
{

	if (!landed)
	{
		Position().y -= m_FallSpeed * updateTime;

		if (Position().y < m_Height)
		{
			landed = true;
		}
	}
	else
	{
		m_SinWave += updateTime;
		Position().y = m_Height + sin(m_SinWave);
		// Rotate on the spot and bob up and down (for effect)
		Matrix().RotateY((kfPi / 3) * updateTime);

	}

	//TODO: Collision detection
	TInt32 enumID;
	EntityManager.BeginEnumEntities(enumID, "", "", "Tank");
	CTankEntity* theTank = dynamic_cast<CTankEntity*> (EntityManager.EnumEntity(enumID));
	while (theTank)
	{
		float radius = Template()->Mesh()->BoundingRadius();
		if (Length(Position() - theTank->Position()) < (theTank->GetRadius() + radius))	//If distance between the ammo and the tank is less than the tank's radius
		{
			EntityManager.EndEnumEntities(enumID);
			// Hit the tank, send the hit message and destroy the bullet
			SMessage theCollectMessage;
			theCollectMessage.from = GetUID();
			theCollectMessage.type = Msg_Ammo;
			theCollectMessage.intParam = m_RefillSize;
			Messenger.SendMessageA(theTank->GetUID(), theCollectMessage);
			return false;
		}


		theTank = dynamic_cast<CTankEntity*> (EntityManager.EnumEntity(enumID));
	}

	EntityManager.EndEnumEntities(enumID);

	return true;
}