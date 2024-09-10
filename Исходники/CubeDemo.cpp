	void CubeDemo::update(const GameTimer & timer)
	{
		mCamera->update(timer);
		mAngle += XM_PI * static_cast<float>(timer.elapsedGameTime());
		XMStoreFloat4x4(&mWorldMatrix, XMMatrixRotationY(mAngle));
	}