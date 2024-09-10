void RaceScene::Enter()
{
	mFollowCamera = mSceneManager->addFpsCameraNode(2, nullptr, XMFLOAT3(0, 100.0f, -100.0f), XMFLOAT3(0, 1.0f, 0.0f), XMFLOAT3(0, 1.0f, 0), true);
	mFollowCamera->setNearZ(1.0f);
	mFollowCamera->setFarZ(1000.0f);
	mFollowCamera->setShadowRange(300.0f);

	mSideCamera = mSceneManager->addFpsCameraNode(3, nullptr);
	mSideCamera->setNearZ(1.0f);
	mSideCamera->setFarZ(1000.0f);
	mSideCamera->setShadowRange(300.0f);

	mPlayerVehicle = new Vehicle(mSceneManager, mTerrainNode, "carA");

	mSceneManager->setActiveCamera(2);
	
	XMFLOAT3 camPos = mFreeCamera->getPosition();
	mPlayerVehicle->setPosition(camPos);

	mFreeCamera->update(0);
	XMFLOAT3 look = mFreeCamera->getLookVector();
	XMVECTOR look_v = XMVector3Normalize(XMVectorSet(look.x, 0, look.z, 0));
	XMVECTOR neg_x_v = XMVectorSet(-1.0f, 0, 0, 0);
	XMVECTOR axis = XMVector3Normalize(XMVector3Cross(neg_x_v, look_v));
	
	XMVECTOR angle = XMVector3AngleBetweenNormals(neg_x_v, look_v);
	XMVECTOR quat_v = XMQuaternionRotationAxis(axis, XMVectorGetX(angle));
	XMFLOAT4 quat;
	XMStoreFloat4(&quat, quat_v);
	mPlayerVehicle->setRotation(quat);

	mVideoDriver->setDeferredAntiAliasing(true);

	IMeshNode* skyNode = mSceneManager->getSkyNode();
	if (skyNode)
		skyNode->setMaterialName("skydome_material");

	u32 textureWidth = mVideoDriver->getBackBufferWidth() / 2;
	u32 textureHeight = mVideoDriver->getBackBufferHeight() / 2;

	ITextureManager* textureManager = ITextureManager::getInstance();
	mTireTrailTexture = textureManager->createTexture2D("tire_trail", 
		textureWidth,
		textureHeight, 
		ETBT_SHADER_RESOURCE | ETBT_RENDER_TARGET,
		nullptr, 1, EGF_R16_FLOAT);

	mTireTrailDepthSurface = textureManager->createDepthStencilSurface("tire_trail_depth",
		textureWidth,
		textureHeight,
		16, 0, false, 1, 0, false, false);
}