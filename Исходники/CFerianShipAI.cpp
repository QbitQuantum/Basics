CSpaceObject *CFerianShipAI::FindRandomAsteroid (void)

//	FindRandomAsteroid
//
//	Returns a random asteroid within 60 light-seconds

	{
	int i;
	Metric rMaxDist2 = MAX_MINING_RANGE2;
	Metric rCloseDist2 = CLOSE_MINING_RANGE2;
	CSpaceObject *Table[MAX_RANDOM_COUNT];
	int iCount = 0;

	for (i = 0; 
			(i < m_pShip->GetSystem()->GetObjectCount() && iCount < MAX_RANDOM_COUNT); 
			i++)
		{
		CSpaceObject *pObj = m_pShip->GetSystem()->GetObject(i);

		if (pObj && pObj->HasAttribute(ATTRIBUTE_ASTEROID))
			{
			CVector vRange = pObj->GetPos() - m_pShip->GetPos();
			Metric rDistance2 = vRange.Dot(vRange);

			//	If we're within the max dist, add it to the list

			if (rDistance2 < rMaxDist2)
				Table[iCount++] = pObj;

			//	If we're within 10 light-seconds, add it twice more (to increase
			//	the probability)

			if (rDistance2 < rCloseDist2)
				{
				Table[iCount++] = pObj;
				Table[iCount++] = pObj;
				}
			}
		}

	//	Pick a random entry from the list

	if (iCount == 0)
		return NULL;
	else
		return Table[mathRandom(0, iCount-1)];
	}