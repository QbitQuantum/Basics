//Updates our viewMatrix based on the camera's position
void MyDemoGame::UpdateCamera()
{
	// values used to translate and rotate the camera in response to input
	float translationScale = -0.001f;
	float rotationScale = -.01f;
	//Left ad right arrow keys alter X position

	// make all camera manipulations occur at double speed when holding spacebar
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		translationScale *= 2.0f;
		rotationScale *= 2.0f;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		gameCam.setDistanceX(translationScale);
		gameCam.setPosition(gameCam.getDistanceX(), gameCam.getDistanceY(), gameCam.getDistanceZ());
		cameraPosition = XMVectorSet(gameCam.getPositionX(), gameCam.getPositionY(), gameCam.getPositionZ(), 0);
		cameraRotation = XMVectorSet(gameCam.getRotationX(), gameCam.getRotationY(), gameCam.getRotationZ(), 0);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		gameCam.setDistanceX(-translationScale);
		gameCam.setPosition(gameCam.getDistanceX(), gameCam.getDistanceY(), gameCam.getDistanceZ());
		cameraPosition = XMVectorSet(gameCam.getPositionX(), gameCam.getPositionY(), gameCam.getPositionZ(), 0);
		cameraRotation = XMVectorSet(gameCam.getRotationX(), gameCam.getRotationY(), gameCam.getRotationZ(), 0);
	}

	//Up/Down arrow keys alter Y position
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		gameCam.setDistanceY(translationScale);
		gameCam.setPosition(gameCam.getDistanceX(), gameCam.getDistanceY(), gameCam.getDistanceZ());
		cameraPosition = XMVectorSet(gameCam.getPositionX(), gameCam.getPositionY(), gameCam.getPositionZ(), 0);
		cameraRotation = XMVectorSet(gameCam.getRotationX(), gameCam.getRotationY(), gameCam.getRotationZ(), 0);
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		gameCam.setDistanceY(-translationScale);
		gameCam.setPosition(gameCam.getDistanceX(), gameCam.getDistanceY(), gameCam.getDistanceZ());
		cameraPosition = XMVectorSet(gameCam.getPositionX(), gameCam.getPositionY(), gameCam.getPositionZ(), 0);
		cameraRotation = XMVectorSet(gameCam.getRotationX(), gameCam.getRotationY(), gameCam.getRotationZ(), 0);
	}

	//5 and 0 on the numpad alter the Z position
	if (GetAsyncKeyState(VK_NUMPAD0) & 0x8000)
	{
		gameCam.setDistanceZ(translationScale);
		gameCam.setPosition(gameCam.getDistanceX(), gameCam.getDistanceY(), gameCam.getDistanceZ());
		cameraPosition = XMVectorSet(gameCam.getPositionX(), gameCam.getPositionY(), gameCam.getPositionZ(), 0);
		cameraRotation = XMVectorSet(gameCam.getRotationX(), gameCam.getRotationY(), gameCam.getRotationZ(), 0);
	}
	if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
	{
		gameCam.setDistanceZ(-translationScale);
		gameCam.setPosition(gameCam.getDistanceX(), gameCam.getDistanceY(), gameCam.getDistanceZ());
		cameraPosition = XMVectorSet(gameCam.getPositionX(), gameCam.getPositionY(), gameCam.getPositionZ(), 0);
		cameraRotation = XMVectorSet(gameCam.getRotationX(), gameCam.getRotationY(), gameCam.getRotationZ(), 0);
	}

	//4 and 6 on the numpad will rotate along the X axis
	if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
	{
		gameCam.setRotationDistanceX(rotationScale);
		gameCam.setRotation(gameCam.getRotationDistanceX(), gameCam.getRotationDistanceY(), gameCam.getRotationDistanceZ());
		cameraRotation = XMVectorSet(gameCam.getRotationX(), gameCam.getRotationY(), gameCam.getRotationZ(), 0);
	}
	if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000)
	{
		gameCam.setRotationDistanceX(-rotationScale);
		gameCam.setRotation(gameCam.getRotationDistanceX(), gameCam.getRotationDistanceY(), gameCam.getRotationDistanceZ());
		cameraRotation = XMVectorSet(gameCam.getRotationX(), gameCam.getRotationY(), gameCam.getRotationZ(), 0);
	}

	//8 ad 2 on the unmpad will rotate along the y axis
	if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000)
	{
		gameCam.setRotationDistanceY(-rotationScale);
		gameCam.setRotation(gameCam.getRotationDistanceX(), gameCam.getRotationDistanceY(), gameCam.getRotationDistanceZ());
		cameraRotation = XMVectorSet(gameCam.getRotationX(), gameCam.getRotationY(), gameCam.getRotationZ(), 0);
	}
	if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
	{
		gameCam.setRotationDistanceY(rotationScale);
		gameCam.setRotation(gameCam.getRotationDistanceX(), gameCam.getRotationDistanceY(), gameCam.getRotationDistanceZ());
		cameraRotation = XMVectorSet(gameCam.getRotationX(), gameCam.getRotationY(), gameCam.getRotationZ(), 0);
	}

	//reset camera back to original position
	if (GetAsyncKeyState('R') & 0x8000)
	{
		gameCam.reset();
		cameraPosition = XMVectorSet(gameCam.getPositionX(), gameCam.getPositionY(), gameCam.getPositionZ(), 0);
		cameraRotation = XMVectorSet(gameCam.getRotationX(), gameCam.getRotationY(), gameCam.getRotationZ(), 0);
	}

	// return the manipulation scales to their normal values
	translationScale = -0.001f;
	rotationScale = -.01f;

	XMMATRIX V = XMMatrixLookToLH(cameraPosition, cameraRotation, upDirection);
	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V));


}