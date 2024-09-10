	void TransparencyDemo::UpdateDirectionalLight(const GameTime& gameTime)
	{
		static float directionalIntensity = 1.0f;
		float elapsedTime = static_cast<float>(gameTime.ElapsedGameTime().count()) / 1000.0f;

		Library::GamePadComponent* gp = mGame->GetGamePad();

		// Update directional light intensity		
		if (gp->IsButtonDown(GamePadButton::Y) && directionalIntensity < 1.0f)
		{
			directionalIntensity += elapsedTime;
			directionalIntensity = min(directionalIntensity, 1.0f);

			mPixelCBufferPerFrameData.LightColor = XMFLOAT4(directionalIntensity, directionalIntensity, directionalIntensity, 1.0f);
			mDirectionalLight->SetColor(mPixelCBufferPerFrameData.LightColor);
		}
		if (gp->IsButtonDown(GamePadButton::X) && directionalIntensity > 0.0f)
		{
			directionalIntensity -= elapsedTime;
			directionalIntensity = max(directionalIntensity, 0.0f);

			mPixelCBufferPerFrameData.LightColor = XMFLOAT4(directionalIntensity, directionalIntensity, directionalIntensity, 1.0f);
			mDirectionalLight->SetColor(mPixelCBufferPerFrameData.LightColor);
		}


		// Rotate directional light
		XMFLOAT2 rotationAmount = Vector2Helper::Zero;
		if (gp->CurrentState().IsLeftThumbStickRight())
		{
			rotationAmount.x += LightRotationRate.x * elapsedTime;
		}
		if (gp->CurrentState().IsLeftThumbStickLeft())
		{
			rotationAmount.x -= LightRotationRate.x * elapsedTime;
		}
		if (gp->CurrentState().IsLeftThumbStickUp())
		{
			rotationAmount.y += LightRotationRate.y * elapsedTime;
		}
		if (gp->CurrentState().IsLeftThumbStickDown())
		{
			rotationAmount.y -= LightRotationRate.y * elapsedTime;
		}

		XMMATRIX lightRotationMatrix = XMMatrixIdentity();
		if (rotationAmount.x != 0)
		{
			lightRotationMatrix = XMMatrixRotationY(rotationAmount.x);
		}

		if (rotationAmount.y != 0)
		{
			XMMATRIX lightRotationAxisMatrix = XMMatrixRotationAxis(mDirectionalLight->RightVector(), rotationAmount.y);
			lightRotationMatrix *= lightRotationAxisMatrix;
		}

		if (rotationAmount.x != 0.0f || rotationAmount.y != 0.0f)
		{
			mDirectionalLight->ApplyRotation(lightRotationMatrix);
			mProxyModel->ApplyRotation(lightRotationMatrix);

			const XMFLOAT3& lightdirection = mDirectionalLight->Direction();
			mVertexCBufferPerFrameData.LightDirection = XMFLOAT4(lightdirection.x, lightdirection.y, lightdirection.z, 0.0f);
		}
	}