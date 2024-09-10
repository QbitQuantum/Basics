void Game::Startup(void)
{
	//TODO: Create Back Buffer

	// Initialize DirectX.
	HRESULT hr = CreateGraphics(hWnd);
	if (FAILED(hr))
	{
		return; // Return -1 to abort Window Creation.
	}

	black.frame = 0;
	black.health = 100;
	black.position = BLACKINITPOS;
	black.vector = ZEROVECTOR;
	black.frameDuration = GetTickCount() + FRAMEDURATION;
	black.controllernum = 0;
	XInputGetState(black.controllernum, &black.controllerState);


	// TESTING CONTROLLER
	//black.vibrateState.wLeftMotorSpeed = 60000;
	//XInputSetState(black.controllernum, &black.vibrateState);
	

	grey.frame = 0;
	grey.health = 100;
	grey.position = GREYINITPOS;
	grey.vector = ZEROVECTOR;
	grey.frameDuration = GetTickCount() + FRAMEDURATION;
	grey.controllernum = 1;
	XInputGetState(grey.controllernum, &grey.controllerState);




	floor1pos = D2D1::RectF(400, 0, pRT->GetSize().width - 400, pRT->GetSize().height);
	floor2pos = D2D1::RectF(400, -pRT->GetSize().height, pRT->GetSize().width - 400, 0);
	floor3pos = D2D1::RectF(400, -2 * pRT->GetSize().height, pRT->GetSize().width - 400, -pRT->GetSize().height);
	floorvec = D2D1::SizeF(0, 15);

	D2D1_RECT_F divider = D2D1::RectF(900, 0, 910, pRT->GetSize().height);
	D2D1_RECT_F leftwall = D2D1::RectF(397, 0, 403, pRT->GetSize().height);
	D2D1_RECT_F rightwall = D2D1::RectF(pRT->GetSize().width - 403, 0, pRT->GetSize().width - 397, pRT->GetSize().height);
	rects.push_front(divider);
	rects.push_front(leftwall);
	rects.push_front(rightwall);


	// Left Lane Rects

	for (size_t i = 0; i < NUMRECTS; i++)
	{
		Obstacle temp;
		temp.position.left = (rand() % 396) + 400;
		temp.position.right = temp.position.left + ((rand() % 30) + 75);
		temp.position.top = -(rand() % (int)(3 * pRT->GetSize().height));
		temp.position.bottom = temp.position.top + 20;
		temp.hitbox.left = temp.position.left + 18;
		temp.hitbox.right = temp.position.right - 18;
		temp.hitbox.top = temp.position.top +5;
		temp.hitbox.bottom = temp.position.bottom -5;
		obstacles.push_back(temp);
		
	}

	// Right Lane Rects
	for (size_t i = 0; i < NUMRECTS; i++)
	{

		Obstacle temp;
		temp.position.left = (rand() % 396) + 900;
		temp.position.right = temp.position.left + ((rand() % 30) + 75);
		temp.position.top = -(rand() % (int)(3 * pRT->GetSize().height));
		temp.position.bottom = temp.position.top + 20;
		temp.hitbox.left = temp.position.left + 15;
		temp.hitbox.right = temp.position.right - 15;
		temp.hitbox.top = temp.position.top;
		temp.hitbox.bottom = temp.position.bottom;
		obstacles.push_back(temp);

	}
	obstVec = D2D1::SizeF(0, OBSTACLESPEED);

	currState = Playing;

	/*nNinjaFrame = 0;
	nGreyNinjaFrame = 0;
	playerpos = D2D1::RectF(300, 300, 350, 350);
	player2pos = D2D1::RectF(200, 200, 250, 250);
	dwGreyNinjaTime = GetTickCount() + 100;
	dwBlackNinjaTime = GetTickCount() + 100;*/
	//TODO: Initialize Game Components


}