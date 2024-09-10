	void PinholeCamera::update(const GameTimer & timer)
	{
		RayTraceCamera::update(timer);
		XMFLOAT3 movementAmount = { 0.0f, 0.0f, 0.0f };

		if (mKeyboard != nullptr)
		{
			if (mKeyboard->isKeyDown(DIK_W))
			{
				movementAmount.y = 1.0f;
			}
			if (mKeyboard->isKeyDown(DIK_S))
			{
				movementAmount.y = -1.0f;
			}
			if (mKeyboard->isKeyDown(DIK_A))
			{
				movementAmount.x = -1.0f;
			}
			if (mKeyboard->isKeyDown(DIK_D))
			{
				movementAmount.x = 1.0f;
			}


			if (mKeyboard->isKeyDown(DIK_R))
			{
				movementAmount.z = -1.0f ;
			}
			if (mKeyboard->isKeyDown(DIK_F))
			{
				movementAmount.z = 1.0f;
			}

			if (mKeyboard->isKeyDown(DIK_Q))
			{
				mViewPlaneDistance -= 10.0f * timer.elapsedGameTime();
			}
			if (mKeyboard->isKeyDown(DIK_E))
			{
				mViewPlaneDistance += 10.0f * timer.elapsedGameTime();
			}
		}

		float rotationAmount = 0;
		if ((mMouse != nullptr))
		{
			if ((mMouse->isButtonDown(MouseButtons::MouseButtonsLeft)))
			{

				LPDIMOUSESTATE mouseState = mMouse->currentState();
				rotationAmount = -mouseState->lX ;
				//rotationAmount.y = -mouseState->lY * mMouseSensitivity;
			}
		}
		//XMStoreFloat3(&mUp,XMVector3Transform(upVector(), XMMatrixRotationZ(rotationAmount/180.0f * 3.14)));
		XMVECTOR position = eyeVector();
		XMVECTOR movement = XMLoadFloat3(&movementAmount) * mMovementRate * timer.elapsedGameTime();

		/*XMVECTOR strafe = right * XMVectorGetX(movement);
		position += strafe;

		XMVECTOR forward = XMLoadFloat3(&mDirection) * XMVectorGetY(movement);
		position += forward;*/

		XMStoreFloat3(&mPosition, position + movement);
		
	}