bool D3DAnimation::Init() {
	if (!D3DBase::Init()) {
		return false;
	}
	
	mLastMousePos.x = 0;
	mLastMousePos.y = 0;

	BOX_DESC box = {1.0f, 1.0f, 1.0f, 3};
	GRID_DESC grid = {20.0f, 30.0f, 60, 40};
	SPHERE_DESC sphere = {0.5f, 20, 20};
	CYLINDER_DESC cylinder = { 0.5f, 0.3f, 3.0f, 20, 20 };

	Material mGridMat;
	Material mBoxMat;
	Material mCylinderMat;
	Material mSphereMat;



	mGridMat.Ambient  = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	mGridMat.Diffuse  = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	mGridMat.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 16.0f);

	mCylinderMat.Ambient  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mCylinderMat.Diffuse  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mCylinderMat.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 16.0f);

	mSphereMat.Ambient  = XMFLOAT4(0.6f, 0.8f, 0.9f, 1.0f);
	mSphereMat.Diffuse  = XMFLOAT4(0.6f, 0.8f, 0.9f, 1.0f);
	mSphereMat.Specular = XMFLOAT4(0.9f, 0.9f, 0.9f, 16.0f);

	mBoxMat.Ambient  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mBoxMat.Diffuse  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mBoxMat.Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 16.0f);

	fogenable = true;
	
	XMFLOAT4X4 I;
	XMFLOAT4X4 rotation;
	XMStoreFloat4x4(&rotation, XMMatrixRotationY(XM_PI));
	XMStoreFloat4x4(&I, XMMatrixIdentity());
	//instanceName;translation;rotation;scale;modelName;modelFilename;texturePath;VShaderName;PShaderName;LayoutName; vertexTypeName;
	std::vector<ObjectInstance_M3dModelList_DESC> objlist = {
		{"player", {0.0f, 0.0f, -100.0f}, rotation, {0.05f, 0.05f, -0.05f}, "soldier", ".\\Models\\soldier.m3d", ".\\Textures\\","BasicAnimationVS","FixFunctionLightPS","PosNormalTexTanSkinned","PosNormalTexTanAnimation"}
	};
	std::vector<ObjectInstance_BOXLIST_DESC> boxlist = {
		{ "podium",{0.0f, 0.5f, 0.0f}, I, {3.0f,1.0f,3.0f}, "box", mBoxMat, ".\\Textures\\", "stone.dds", "stones_nmap.dds", "BasicVS","FixFunctionLightPS","PosNormTexTan","PosNormalTexTan",box} 
	};
	std::vector<ObjectInstance_GRIDLIST_DESC> gridlist = {
		{ "land", {0.0f, 0.0f,0.0f}, I, {1.0f,1.0f,1.0f}, "grid", mGridMat, ".\\Textures\\", "floor.dds", "floor_nmap.dds", "BasicVS","FixFunctionLightPS","PosNormTexTan","PosNormalTexTan",grid}
	};
	mDirLights[0].Ambient  = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	mDirLights[0].Diffuse  = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mDirLights[0].Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mDirLights[0].Direction = XMFLOAT3(0.57735f, -0.57735f, 0.57735f);
	dirLightsw[0] = true;
	mDirLights[1].Ambient  = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mDirLights[1].Diffuse  = XMFLOAT4(0.20f, 0.20f, 0.20f, 1.0f);
	mDirLights[1].Specular = XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f);
	mDirLights[1].Direction = XMFLOAT3(-0.57735f, -0.57735f, 0.57735f);
	dirLightsw[1] = true;
	mDirLights[2].Ambient  = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mDirLights[2].Diffuse  = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	mDirLights[2].Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mDirLights[2].Direction = XMFLOAT3(0.0f, -0.707f, -0.707f);
	dirLightsw[2] = true;
	mSpotLights[0].Ambient = XMFLOAT4(0.2f, 1.0f, 0.2f, 1.0f);
	mSpotLights[0].Diffuse = XMFLOAT4(0.5f, 1.0f, 0.5f, 1.0f);
	mSpotLights[0].Specular = XMFLOAT4(0.5f, 1.0f, 0.5f, 1.0f);
	mSpotLights[0].Position = XMFLOAT3(0.0f, 5.0f, 0.0f);
	mSpotLights[0].Range = 25.0f;
	mSpotLights[0].Att = XMFLOAT3(0.0f, 0.15f, 0.0f);
	XMFLOAT3 dir;
	XMStoreFloat3(&dir, XMVector3Normalize(XMLoadFloat3(&XMFLOAT3(0.0f, -5.0f, -100.0f))));
	mSpotLights[0].Direction = dir;
	mSpotLights[0].Spot = 56.0f;
	SpotLightsw[0] = true;
	mSpotLights[1].Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mSpotLights[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mSpotLights[1].Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mSpotLights[1].Position = XMFLOAT3(0.0f, 2.5f, -100.0f);
	mSpotLights[1].Range = 15.0f;
	mSpotLights[1].Att = XMFLOAT3(0.0f, 0.15f, 0.0f);
	mSpotLights[1].Direction = XMFLOAT3(0.0f, 0.0f, -1.0f);
	mSpotLights[1].Spot = 50.0f;
	SpotLightsw[1] = true;
	std::vector<ObjectInstance_SPHERELIST_DESC> spherelist;
	std::vector<ObjectInstance_CYLINDERLIST_DESC> cylinderlist;
	for(int i = 0; i < 5; ++i)
	{
		ObjectInstance_CYLINDERLIST_DESC item1 = { "pillar" + std::to_string(i * 2 + 1), {-5.0f, 1.5f, -10.0f + i*5.0f}, I, {1.0f,1.0f,1.0f}, "cylinder", mCylinderMat, ".\\Textures\\", "bricks.dds", "bricks_nmap.dds", "BasicVS","FixFunctionLightPS","PosNormTexTan","PosNormalTexTan", cylinder};
		ObjectInstance_CYLINDERLIST_DESC item2 = { "pillar" + std::to_string(i * 2 + 2), {+5.0f, 1.5f, -10.0f + i*5.0f}, I, {1.0f,1.0f,1.0f}, "cylinder", mCylinderMat, ".\\Textures\\", "bricks.dds", "bricks_nmap.dds", "BasicVS","FixFunctionLightPS","PosNormTexTan","PosNormalTexTan",cylinder};
		cylinderlist.push_back(item1);
		cylinderlist.push_back(item2);
		ObjectInstance_SPHERELIST_DESC item3 = { "ball" + std::to_string(i * 2 + 1), {-5.0f, 3.5f, -10.0f + i*5.0f}, I, {1.0f,1.0f,1.0f}, "sphere", mCylinderMat, ".\\Textures\\", "stone.dds", "stones_nmap.dds", "BasicVS","FixFunctionLightPS","PosNormTexTan","PosNormalTexTan",sphere};
		ObjectInstance_SPHERELIST_DESC item4 = { "ball" + std::to_string(i * 2 + 2), {+5.0f, 3.5f, -10.0f + i*5.0f}, I, {1.0f,1.0f,1.0f}, "sphere", mCylinderMat, ".\\Textures\\", "stone.dds", "stones_nmap.dds", "BasicVS","FixFunctionLightPS","PosNormTexTan","PosNormalTexTan",sphere};
		spherelist.push_back(item3);
		spherelist.push_back(item4);

		mPointLights[i * 2].Ambient = XMFLOAT4(1.f, 0.9f, 0.3f, 1.0f);
		mPointLights[i * 2].Diffuse = XMFLOAT4(1.f, 0.9f, 0.3f, 1.0f);
		mPointLights[i * 2].Specular = XMFLOAT4(1.f, 0.9f, 0.3f, 1.0f);
		mPointLights[i * 2].Position = XMFLOAT3(-5.0f, 3.5f, -10.0f + i * 5.0f);
		mPointLights[i * 2].Att = XMFLOAT3(0.0f, 0.0f, 0.9f);
		mPointLights[i * 2].Range = 4.0f;
		pointLightsw[i * 2] = true;
		mPointLights[i * 2 + 1].Ambient = XMFLOAT4(1.f, 0.9f, 0.3f, 1.0f);
		mPointLights[i * 2 + 1].Diffuse = XMFLOAT4(1.f, 0.9f, 0.3f, 1.0f);
		mPointLights[i * 2 + 1].Specular = XMFLOAT4(1.f, 0.9f, 0.3f, 1.0f);
		mPointLights[i * 2 + 1].Position = XMFLOAT3(+5.0f, 3.5f, -10.0f + i * 5.0f);
		mPointLights[i * 2 + 1].Att = XMFLOAT3(0.0f, 0.9f, 0.0f);
		mPointLights[i * 2 + 1].Range = 4.0f;
		pointLightsw[i * 2 + 1] = true;
	}
	list = new Object3DList(this,objlist);
	list->AddBoxist(boxlist);
	list->AddGridList(gridlist);
	list->AddCylinderList(cylinderlist);
	list->AddSphereList(spherelist);
	list->Init();
	Cam.SetLens(0.25f * XM_PI, getAspectRatio(), 1.0f, 1000.0f);
	return true;
}