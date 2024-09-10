bool DuckHuntMain::Init()
{
	if (!D3DApp::Init())
		return false;

	// Must init Effects first since InputLayouts depend on shader signatures.
	Effects::InitAll(md3dDevice);
	InputLayouts::InitAll(md3dDevice);
	RenderStates::InitAll(md3dDevice);
	mCrosshair = new Crosshair(md3dDevice);
	mTexMgr.Init(md3dDevice);
	DuckHuntMain::ShowCursors(false);
	mSky = new Sky(md3dDevice, L"Textures/desertcube1024.dds", 5000.0f);
	mSmap = new ShadowMap(md3dDevice, SMapSize, SMapSize);
	Terrain::InitInfo tii;
	tii.HeightMapFilename = L"Textures/myT5.raw";
	tii.LayerMapFilename0 = L"Textures/grass.dds";
	tii.LayerMapFilename1 = L"Textures/darkdirt.dds";
	tii.LayerMapFilename2 = L"Textures/stone.dds";
	tii.LayerMapFilename3 = L"Textures/lightdirt.dds";
	tii.LayerMapFilename4 = L"Textures/snow.dds";
	tii.BlendMapFilename = L"Textures/blend.dds";
	tii.HeightScale = 50.0f;
	tii.HeightmapWidth = 2049;
	tii.HeightmapHeight = 2049;
	tii.CellSpacing = 0.5f;

	mTerrain.Init(md3dDevice, md3dImmediateContext, tii);
	//Sound
	result = FMOD::System_Create(&mSystem);
	result = mSystem->init(32, FMOD_INIT_NORMAL, 0);
	result = mSystem->createSound("Sounds/GunFire.wav", FMOD_DEFAULT, 0, &mGunFire);
	result = mGunFire->setMode(FMOD_LOOP_OFF);






	mCam.SetLens(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
	mSsao = new Ssao(md3dDevice, md3dImmediateContext, mClientWidth, mClientHeight, mCam.GetFovY(), mCam.GetFarZ());

	BuildScreenQuadGeometryBuffers();

	testModelDuck = new BasicModel(md3dDevice, mTexMgr, "Models\\duck.obj", L"Textures\\DUCK.jpg");



	BasicModelInstance testInstanceDuck;
	BasicModelInstance testInstanceDuck2;
	BasicModelInstance testInstanceDuck3;
	BasicModelInstance testInstanceDuck4;

	testInstanceDuck.Model = testModelDuck;
	testInstanceDuck2.Model = testModelDuck;
	testInstanceDuck3.Model = testModelDuck;
	testInstanceDuck4.Model = testModelDuck;



	//Duck 1
	XMMATRIX modelScale = XMMatrixScaling(1.0f, 1.0f, -1.0f);
	XMMATRIX modelRot = XMMatrixRotationY(0.0f);
	XMMATRIX modelOffset = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	//Duck 2
	XMMATRIX modelScale2 = XMMatrixScaling(2.0f, 2.0f, -1.0f);
	XMMATRIX modelRot2 = XMMatrixRotationY(-1.0f);
	XMMATRIX modelOffset2 = XMMatrixTranslation(1.0f, 1.0f, -1.0f);
	//Duck3
	XMMATRIX modelScale3 = XMMatrixScaling(1.5f, 1.5f, 1.5f);
	XMMATRIX modelRot3 = XMMatrixRotationY(0.5f);
	XMMATRIX modelOffset3 = XMMatrixTranslation(2.0f, 1.0f, -1.0f);
	//Duck4
	XMMATRIX modelScale4 = XMMatrixScaling(0.5f, 0.5f, -1.0f);
	XMMATRIX modelRot4 = XMMatrixRotationY(1.0f);
	XMMATRIX modelOffset4 = XMMatrixTranslation(0.5f, 1.0f, -1.0f);


	//Duck 1
	XMStoreFloat4x4(&testInstanceDuck.World, modelScale*modelRot*modelOffset);
	mModelInstances.push_back(testInstanceDuck);

	//Duck 2
	XMStoreFloat4x4(&testInstanceDuck2.World, modelScale2*modelRot2*modelOffset2);
	mModelInstances.push_back(testInstanceDuck2);

	//Duck 3
	XMStoreFloat4x4(&testInstanceDuck3.World, modelScale3*modelRot3*modelOffset3);
	mModelInstances.push_back(testInstanceDuck3);

	//Duck 4
	XMStoreFloat4x4(&testInstanceDuck4.World, modelScale4*modelRot4*modelOffset4);
	mModelInstances.push_back(testInstanceDuck4);


	//create collision box
	for (unsigned i = 0; i < mModelInstances.size(); i++)
	{
		mModelInstances[i].Model->CreateCollisionBox(mModelInstances[i].Model->BasicVertices);
	}






	//
	// Compute scene bounding box.
	//

	XMFLOAT3 minPt(+MathHelper::Infinity, +MathHelper::Infinity, +MathHelper::Infinity);
	XMFLOAT3 maxPt(-MathHelper::Infinity, -MathHelper::Infinity, -MathHelper::Infinity);
	for (UINT i = 0; i < mModelInstances.size(); ++i)
	{
		for (UINT j = 0; j < mModelInstances[i].Model->BasicVertices.size(); ++j)
		{
			XMFLOAT3 P = mModelInstances[i].Model->BasicVertices[j].Pos;

			minPt.x = MathHelper::Min(minPt.x, P.x);
			minPt.y = MathHelper::Min(minPt.x, P.x);
			minPt.z = MathHelper::Min(minPt.x, P.x);

			maxPt.x = MathHelper::Max(maxPt.x, P.x);
			maxPt.y = MathHelper::Max(maxPt.x, P.x);
			maxPt.z = MathHelper::Max(maxPt.x, P.x);
		}
	}

	//
	// Derive scene bounding sphere from bounding box.
	//
	mSceneBounds.Center = XMFLOAT3(
		0.5f*(minPt.x + maxPt.x),
		0.5f*(minPt.y + maxPt.y),
		0.5f*(minPt.z + maxPt.z));

	XMFLOAT3 extent(
		0.5f*(maxPt.x - minPt.x),
		0.5f*(maxPt.y - minPt.y),
		0.5f*(maxPt.z - minPt.z));

	mSceneBounds.Radius = sqrtf(extent.x*extent.x + extent.y*extent.y + extent.z*extent.z);

	return true;
}