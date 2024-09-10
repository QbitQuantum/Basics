void FBXModel::load(const GraphicsDevice& device, const std::string& filename, unsigned keyframes)
{
	if (effect.resource == 0)
		effect = Effect::createFromFile<FBXEffect>(device, Config::getValue(ConfigKeys::fbxEffectPath));

	defaultTexture = Texture::createFromFile(device, defaultTexturePath);
	
	vertexDeclaration = device.createVertexDeclaration(FBXInstance::vertexElements);

	KFbxSdkManager* sdkManager = KFbxSdkManager::Create();
	KFbxIOSettings* ios = KFbxIOSettings::Create(sdkManager, IOSROOT);
	sdkManager->SetIOSettings(ios);

	// Create an importer using our sdk manager.
	KFbxImporter* importer = KFbxImporter::Create(sdkManager, "");

	importer->Initialize(filename.c_str(), -1, sdkManager->GetIOSettings());

	// Create a new scene so it can be populated by the imported file.
	KFbxScene* scene = KFbxScene::Create(sdkManager, "");

	// Import the contents of the file into the scene.
	importer->Import(scene);

	KFbxNode* rootBone = 0;
	KFbxNode* rootNode = scene->GetRootNode();

	KFbxAnimStack* animStack = KFbxCast<KFbxAnimStack>(scene->GetSrcObject(FBX_TYPE(KFbxAnimStack), 0));
	KFbxAnimLayer* animLayer = 0;

	if (animStack)
	{
		animLayer = animStack->GetMember(FBX_TYPE(KFbxAnimLayer), 0);
		scene->GetEvaluator()->SetContext(animStack);
	}

	loadBones(rootNode, &rootBone, animLayer);
	loadMeshes(rootNode, device, KFbxGeometryConverter(sdkManager));

	if (animLayer)
	{
		for (unsigned i = 0; i <= keyframes; ++i)
			boneMatricesMap[i] = traverseBones(i, rootBone, Matrix::identity, MatrixCollection(bones.size()));
	}

	sdkManager->Destroy();

	loaded = true;
}