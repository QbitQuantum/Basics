FBXSceneImporter::FBXSceneImporter(std::string file_name)
{
	std::string log_file_name = file_name;
	log_file_name.append("log.txt");
	myfile.open(log_file_name.c_str());

	// Initialize the SDK manager. This object handles memory management.
	lSdkManager = FbxManager::Create();

	FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	lSdkManager->SetIOSettings(ios);

	// Create an importer using the SDK manager.
	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

	// Use the first argument as the filename for the importer.
	if (!lImporter->Initialize(file_name.c_str(), -1, lSdkManager->GetIOSettings())) {
		myfile << "Call to FbxImporter::Initialize() failed.\n";
		myfile << "Error returned: " <<  lImporter->GetStatus().GetErrorString() << "";
		myfile.close();
		exit(-1);
	}

	// Create a new scene so that it can be populated by the imported file.
	lScene = FbxScene::Create(lSdkManager, "myScene");

	// Import the contents of the file into the scene.
	lImporter->Import(lScene);

	// The file is imported, so get rid of the importer.
	lImporter->Destroy();

	FbxGeometryConverter converter(lSdkManager);
	converter.Triangulate(lScene, true);

	scene_to_fill = new Scene(Utilities::get_file_name_from_path_wo_extension(file_name));
	resource_manager.add_scene(scene_to_fill);

	// Print the nodes of the scene and their attributes recursively.
	// Note that we are not printing the root node because it should
	// not contain any attributes.
	FbxNode* lRootNode = lScene->GetRootNode();
	if (lRootNode) 
	{
		for (int i = 0; i < lRootNode->GetChildCount(); i++)
		{
			read_node(lRootNode->GetChild(i));
		}
	}

	if (lRootNode)
	{
		for (int i = 0; i < lRootNode->GetChildCount(); i++)
		{
			PrintNode(lRootNode->GetChild(i));
		}
	}

	// Destroy the SDK manager and all the other objects it was handling.
	myfile.close();
	lSdkManager->Destroy();

}