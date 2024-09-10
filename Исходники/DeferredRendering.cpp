void CascadeShadow::CascadeUpdate(){
	float nearClip = 0.01f;
	float farClip = 100.0f;

	float m_Lamda = 0.8f;

	// 平行分割処理.
	float splitPositions[MAX_CASCADE + 1];
	ComputeSplitPositions(MAX_CASCADE, m_Lamda, nearClip, farClip, splitPositions);

	float SlideBack = 50.0f;

	auto camera = Game::GetMainCamera();
	auto campos = camera->gameObject->mTransform->WorldPosition();
	auto camvec = camera->gameObject->mTransform->Forward();
	float forward = splitPositions[0];

	// カスケード処理.
	for (int i = 0; i<MAX_CASCADE; ++i)
	{
		float size = splitPositions[i + 1] - splitPositions[i + 0];

		auto lightPos = campos + camvec * (forward + size / 2) + mLightVect * -SlideBack;

		m_LightView = XMMatrixLookToLH(lightPos, mLightVect, XMVectorSet(0, 1, 0, 1));

		forward += size;

		float aspect = float(WindowState::mWidth) / float(WindowState::mHeight);
		float fov = XM_PIDIV4;
		float farHeight = tanf(fov) * splitPositions[i + 1];
		float farWidth = farHeight * aspect;

		size = farWidth * 1.41421356f * 1.41421356f;
		m_LightProj = XMMatrixOrthographicLH(size, size, 0.01f, 100.0f);

		// ライトのビュー射影行列.
		m_ShadowMatrix[i] = m_LightView * m_LightProj;

		XMVECTOR min, max;

		// 分割した視錘台の8角をもとめて，ライトのビュー射影空間でAABBを求める.
		CalculateFrustum(
			splitPositions[i + 0],
			splitPositions[i + 1],
			m_ShadowMatrix[i],
			&min,
			&max);

		// クロップ行列を求める.
		XMMATRIX crop = CreateCropMatrix(min, max);

		// シャドウマップ行列と分割位置を設定.
		m_ShadowMatrix[i] = m_ShadowMatrix[i] * crop;
		m_SplitPos[i] = splitPositions[i + 1];
	}
}