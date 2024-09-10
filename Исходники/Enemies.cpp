void Enemies::createEnemy(int model, FLOAT x1, FLOAT y1, FLOAT z1, FLOAT x2, FLOAT y2, FLOAT z2, FLOAT x3, FLOAT y3, FLOAT z3, FLOAT x4, FLOAT y4, FLOAT z4, FLOAT scale, int speed, int collisionstype)
{
	Enemy* newEnemy;

	newEnemy = new Enemy();

	XMMATRIX modelScale = XMMatrixScaling(scale, scale, -scale);
	XMMATRIX modelRot = XMMatrixRotationY(0);
	XMMATRIX modelOffset = XMMatrixTranslation(x1, y1, z1);


	newEnemy->setModelScale(modelScale);
	newEnemy->setModelRot(modelRot);
	newEnemy->setModelOffset(modelOffset);

	newEnemy->SetPositionOne(x1, y1, z1);
	newEnemy->SetPositionTwo(x2, y2, z2);
	newEnemy->SetPositionThree(x3, y3, z3);
	newEnemy->SetPositionFour(x4, y4, z4);



	if (model == simpleEnemy)
	{
		anEnemy = mSimpleEnemy;
	}
	else if (model == tractor)
	{
		anEnemy = mTractor;
	}


	

	newEnemy->setModel(anEnemy);
	newEnemy->setScale(scale);
	newEnemy->setSpeed(speed);
	newEnemy->setcollisiontype(collisionstype);


	BasicModelInstance oneEnemy;


	theEnemy.Model = anEnemy;


	XMStoreFloat4x4(&theEnemy.World, modelScale*modelRot*modelOffset);


	newEnemy->setBasicMInstance(theEnemy);

	oneEnemy = newEnemy->getBasicMInstance();



	addEnemy(theEnemy);

	enemyclass.push_back(newEnemy);


	LevelCollisions.push_back(EnemyBox);

	newEnemy->setWorld(theEnemy.World);





}