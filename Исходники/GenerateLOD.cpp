// Load Fbx File
void GenerateLOD::LoadFbx()
{
	FbxManager *fbxManager = FbxManager::Create();

	//Create an IOSetting
	FbxIOSettings *ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);

	//Create an impoter
	FbxImporter *lImporter = FbxImporter::Create(fbxManager, "myImporter");
	std::string tmp = std::string(".\\LODs\\") + srcFbxName;
	bool lImporterStatus = lImporter->Initialize(tmp.c_str(), -1, fbxManager->GetIOSettings());
	if (!lImporterStatus) {
		MessageBox(NULL, "No Scuh File in .\\LODs\\ directory !", "Warning", 0);
		return;
	}

	FbxScene *fbxScene = FbxScene::Create(fbxManager, "myScene");
	lImporter->Import(fbxScene);

	FbxNode *rootNode = fbxScene->GetRootNode();
	if (rootNode != NULL) {
		for (int i = 0; i < rootNode->GetChildCount(); ++i) {
			FbxNode *node = rootNode->GetChild(i);
			FbxNodeAttribute *Att = node->GetNodeAttribute();
			if (Att != NULL && Att->GetAttributeType() == FbxNodeAttribute::eMesh) {
				FbxMesh *lMesh = (FbxMesh *)(Att);
				//FbxMesh *lMesh = dynamic_cast<FbxMesh *>(Att);
				if (!lMesh->IsTriangleMesh()) {
					FbxGeometryConverter converter = FbxGeometryConverter(fbxManager);
					FbxNodeAttribute *Attr = converter.Triangulate(lMesh, true);
					lMesh = (FbxMesh *)(Attr);
				}

				//Following is the SImplification
				Reduction_EdgesCollapse_UV(node, lMesh, fbxManager, fbxScene);

			}
		}
	}

	//MessageBox(NULL, "Export Succeed!", "Export", 0);
	fbxManager->Destroy();
}