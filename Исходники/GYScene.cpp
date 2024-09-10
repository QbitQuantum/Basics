GYINT32 GYScene::RemoveCreature(GYCreature& creature)
{
	GYINT32 result = INVALID_VALUE;
	do 
	{
		GYZone* pZone = GetZone(creature.GetPosition());
		if (GYNULL == pZone)
		{
			break;
		}

		creature.OnLeaveScene(*this);

		if (0 != pZone->RemoveCreature(creature))
		{
			break;
		}

		if (0 !=  m_creatureSet[creature.GetObjectType()].Delete(creature))
		{
			break;
		}

		result = 0;

	} while (GYFALSE);
	return result;
}