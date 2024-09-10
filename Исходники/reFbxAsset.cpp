void reFBXAsset::import()
{
	FbxImporter* importer = FbxImporter::Create(sdk,"");
	meshes = new reFileAsset(this);
	meshes->setPath("meshes");
	children.push_back(meshes);
	if(!importer->Initialize(path().toUtf8().constData(), -1, sdk->GetIOSettings())) {
		printf("Call to FbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", importer->GetLastErrorString());
		return;
	}
	FbxScene* lScene = FbxScene::Create(sdk, "myScene");
	FbxAxisSystem ga(FbxAxisSystem::OpenGL);
	ga.ConvertScene(lScene);
	importer->Import(lScene);
	FbxNode* lRootNode = lScene->GetRootNode();
	if(lRootNode) {
		reNode* node = importNode(lRootNode, NULL);
		node->name(info.baseName().toStdString());
		QString path = dataDir() + QDir::separator() + node->name().c_str() + ".json";
		node->save(path.toStdString());
	}
	importer->Destroy();
}