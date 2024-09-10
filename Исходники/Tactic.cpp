int AttackWeakestEnemy::validateTactic(list<Action*> &newActions, Unit* squad, const vector<Unit*>& enemyUnits,
        const vector<Unit*>& alliedUnits)
{
	squad->setTarget(-1);
	if (enemyUnits.size() == 0)
	{
		return 0;
	}

	int Ret = 0;
	float minHP = 100;
	Coordinates enemyAvrg;
	int sumHP;

	Coordinates myPos = squad->getAveragePos();
	if (squad->getNShipsAlive() == 0)
		return 0;

	Unit *wekeastUnit = NULL;

	vector<Unit*> enemyNear;
	//cria uma lista com a unidades dentro do alcançe
	for (unsigned int i = 0; i < enemyUnits.size(); i++)
	{
		Coordinates enemyAvrg = enemyUnits[i]->getAveragePos();
		if (enemyUnits[i]->getNShipsAlive() > 0)
		{
			float dist = myPos.distance(enemyAvrg);
			if (dist < squad->getSquadBaseStats().range)
			{
				enemyNear.push_back(enemyUnits[i]);
			}
		}
	}

	//percorre a lista de unidades inimigas no alçance um busca da mais fraca
	for (unsigned int i = 0; i < enemyNear.size(); i++)
	{
        enemyAvrg = enemyNear[i]->getAveragePos();
		if (enemyNear[i]->getNShipsAlive() > 0)
		{
			sumHP = 0;
			for (unsigned int j = 0; j < enemyNear[i]->nShips(); ++j)
			{
				sumHP += enemyNear[i]->getShip(j)->getHP();
			}

			int maxHP = enemyNear[i]->getUnitInfo()->squadSize * enemyNear[i]->getUnitInfo()->stats.maxHP;

			// Considerar apenas o inteiro
			int percent = (sumHP / maxHP) * 100;
			if (percent < minHP)
			{
				minHP = percent;
				wekeastUnit = enemyNear[i];
				squad->setTarget( i );
			}
		}

	}

	//ataca as naves do esquadrao de maneira aleatoria
	if (wekeastUnit)
	{
		for (unsigned int i = 0; i < squad->nShips(); ++i)
		{
			Ship *iShip = squad->getShip(i);

			if (iShip->isAlive() && iShip->getStats().currentAtkCD == 0)
			{
				while (1)
				{
					int s = rand() % wekeastUnit->nShips();
					if (wekeastUnit->getShip(s)->isAlive())
					{
						iShip->getStats().currentAtkCD = iShip->getBaseStats().maxAtkCD;
						newActions.push_back(new AttackAction(iShip, wekeastUnit->getShip(s), squad->getUnitInfo(), wekeastUnit->getUnitInfo()));
						++Ret;
						break;
					}
				}
			}
		}
	}

    // TODO: Se eu nao conseguir atacar, devo desconsiderar o target?
//	if (Ret == 0)
//        squad->setTarget(-1);

	return Ret;
}