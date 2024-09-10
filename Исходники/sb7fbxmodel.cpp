	//FbxManager* lSdkManager = FbxManager::Create();
	sb7fbxmodel::sb7fbxmodel(char *fileName)
	{
		FbxManager* lSdkManager = FbxManager::Create();

		// Create the IO settings object.
		FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
		lSdkManager->SetIOSettings(ios);

		// Create an importer using the SDK manager.
		FbxImporter* lImporter = FbxImporter::Create(lSdkManager,"");

		// Use the first argument as the filename for the importer.
		if(!lImporter->Initialize(fileName, -1, lSdkManager->GetIOSettings())) { 
			printf("Call to FbxImporter::Initialize() failed.\n"); 
			printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString()); 
			exit(-1); 
		}

		// Create a new scene so that it can be populated by the imported file.
		FbxScene* lScene = FbxScene::Create(lSdkManager,"myScene");

		// Import the contents of the file into the scene.
		lImporter->Import(lScene);
		ProcessNode(lScene->GetRootNode());

		// The file is imported; so get rid of the importer.
		lImporter->Destroy();
	}