void Game::UpdateScene(float dt)
{

	addDeltaTime(dt);

	theEnemies->update(dt);

	int levelColsize = LevelCollisions.size();
	int tempOtherObject;

	//////updates the enemy collisions as they move
	std::vector <XNA::AxisAlignedBox> temp;
	//original value = 3
	temp = theEnemies->getEnemyCollisions();

	std::vector <XNA::AxisAlignedBox> tempObject;
	//original value = 5
	tempObject = Objects->getObjectCollisions();

	std::vector <XNA::AxisAlignedBox> tempLevel;
	//original value = 26
	tempLevel = Level1->getLevelPartsCollisions();

	tempOtherObject = tempObject.size() + temp.size() + tempLevel.size();


	int tempSize = temp.size();


	int sizeDifference = 0;

	sizeDifference = LevelCollisions.size() - tempOtherObject;


	if (sizeDifference > 0)
	{

		int something = 0;
		LevelCollisions.pop_back();

		int j = 0;
		for (UINT i = tempLevel.size(); i < (tempLevel.size() + tempObject.size()); i++, j++)
		{

			LevelCollisions[i] = tempObject[j];

		}

		if (temp.size() >= 0)
		{

			j = 0;
			for (UINT i = (tempLevel.size() + tempObject.size()); i < (tempLevel.size() + tempObject.size() + temp.size()); i++, j++)
			{

				LevelCollisions[i] = temp[j];
				LevelCollisions[i].Center = temp[j].Center;
			}
		}

	}
	else
	{
		int	j = 0;
		for (UINT i = tempObject.size() + tempLevel.size(); i < tempOtherObject; i++, j++)
		{
			LevelCollisions[i] = temp[j];
		}
	}

	/////////////////////////////

	PlayerOne->setLevelCollisions(LevelCollisions);

	/////////////////////////////

	XMVECTOR desiredCharDir = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	XMVECTOR playerPos = XMLoadFloat3(&mPlayerPosition);


	XMVECTOR camRight = XMLoadFloat3(&mCam.GetRight());
	XMVECTOR camForward = XMLoadFloat3(&mCam.GetLook());
	XMVECTOR camUp = XMLoadFloat3(&mCam.GetUp());

	XMVECTOR multiply = XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f);

	camUp = XMVectorAdd(camUp, multiply);

	bool jumpChar = false;


	bool moveChar = false;


	if (GetAsyncKeyState('W') & 0x8000)
	{
		desiredCharDir += (camForward);

		moveChar = true;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		desiredCharDir += -(camForward);

		moveChar = true;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		desiredCharDir += (camRight);

		moveChar = true;
	}



	if (GetAsyncKeyState('D') & 0x8000)
	{
		desiredCharDir += -(camRight);

		moveChar = true;
	}


	if (GetAsyncKeyState('Q') & 0x8000)
	{
		float dy = 1.5 * dt;
		mCam.RotateY(-dy);
	}

	if (GetAsyncKeyState('E') & 0x8000)
	{

		float dy = 1.5 * dt;
		mCam.RotateY(dy);
	}


	if (GetAsyncKeyState('R') & 0x8000)
	{
		float dy = 0.25 * dt;
		mCam.Pitch(dy);
	}

	if (GetAsyncKeyState('F') & 0x8000)
	{
		float dy = 0.25 * dt;
		mCam.Pitch(-dy);
	}

	if (PlayerOne->getOnGround() == true)
	{
		if (GetAsyncKeyState( VK_SPACE ))
		{
			desiredCharDir += camUp;
			moveChar = true;
			SoundSystem::Play(QUACK);
		}

	}

	XMVECTOR addGravity = XMVectorSet(0.0f, -30.f * DeltaTimeF, 0.0f, 0.0f);
	XMFLOAT3 tGrav;
	XMStoreFloat3(&tGrav, addGravity);

	XMVECTOR tGravity = XMLoadFloat3(&tGrav);

	if (PlayerOne->getOnGround() == true)
	{

	}
	else if (PlayerOne->getOnGround() == false)
	{

		desiredCharDir += addGravity;
	}

	//		
	// Switch the number of lights based on key presses.
	//
	if (GetAsyncKeyState('0') & 0x8000)
	{
		mLightCount = 0;
	}
	if (GetAsyncKeyState('1') & 0x8000)
		mLightCount = 1;

	if (GetAsyncKeyState('2') & 0x8000)
		mLightCount = 2;

	if (GetAsyncKeyState('3') & 0x8000)
		mLightCount = 3;



	////send player information to the camera

	mCam.getPlayerPos(PlayerOne->getPlayerPosition());
	mCam.getDeltaTime(dt);

	mCam.moveCam();

	PlayerOne->move(dt, desiredCharDir, theEnemies, Objects);

	PlayerOne->update();

}