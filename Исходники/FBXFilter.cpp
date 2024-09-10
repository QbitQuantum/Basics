CC_FILE_ERROR FBXFilter::saveToFile(ccHObject* entity, const char* filename)
{
	if (!entity)
		return CC_FERR_BAD_ARGUMENT;
	
	std::vector<ccGenericMesh*> meshes;
	if (entity->isKindOf(CC_MESH))
	{
		meshes.push_back(static_cast<ccGenericMesh*>(entity));
	}
	else if (entity->isA(CC_HIERARCHY_OBJECT))
	{
		for (unsigned i=0; i<entity->getChildrenNumber(); ++i)
		{
			ccHObject* child = entity->getChild(i);
			if (child->isKindOf(CC_MESH))
				meshes.push_back(static_cast<ccGenericMesh*>(child));
		}
	}

	if (meshes.empty())
	{
        return CC_FERR_NO_SAVE;
	}

	//The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
    FbxManager* lSdkManager = FbxManager::Create();
    if( !lSdkManager )
    {
		ccLog::Warning("[FBX] Error: Unable to create FBX Manager!");
        return CC_FERR_CONSOLE_ERROR;
    }
	else
	{
		ccLog::Print("[FBX] Autodesk FBX SDK version %s", lSdkManager->GetVersion());
	}

	//Create an IOSettings object. This object holds all import/export settings.
	FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	lSdkManager->SetIOSettings(ios);

	//Load plugins from the executable directory (optional)
	//FbxString lPath = FbxGetApplicationDirectory();
	//lSdkManager->LoadPluginsDirectory(lPath.Buffer());

    //Create an FBX scene. This object holds most objects imported/exported from/to files.
    FbxScene* lScene = FbxScene::Create(lSdkManager, "My Scene");
	if( !lScene )
    {
		ccLog::Warning("[FBX] Error: Unable to create FBX scene!");
        return CC_FERR_CONSOLE_ERROR;
    }

    // create scene info
	{
		FbxDocumentInfo* sceneInfo = FbxDocumentInfo::Create(lSdkManager,"SceneInfo");
		sceneInfo->mTitle = qPrintable(QString("Mesh: ") + (meshes.size() == 1 ? meshes[0]->getName() : QString("Multiple meshes")));
		sceneInfo->mAuthor = "CloudCompare";
		sceneInfo->mRevision = "rev. 1.0";
		sceneInfo->mKeywords = "cloudcompare mesh";

		// we need to add the sceneInfo before calling AddThumbNailToScene because
		// that function is asking the scene for the sceneInfo.
		lScene->SetSceneInfo(sceneInfo);
	}

	//create thumbnail
	//{
	//	FbxThumbnail* lThumbnail = FbxThumbnail::Create(lScene,"");

	//	lThumbnail->SetDataFormat(FbxThumbnail::eRGB_24);
	//	lThumbnail->SetSize(FbxThumbnail::e64x64);
	//	lThumbnail->SetThumbnailImage(cSceneThumbnail);

	//	if (lScene->GetSceneInfo())
	//	{
	//		lScene->GetSceneInfo()->SetSceneThumbnail(lThumbnail);
	//	}
	//}

    // Build the node tree.
    FbxNode* lRootNode = lScene->GetRootNode();
	{
		for (size_t i=0; i<meshes.size(); ++i)
		{
			FbxNode* meshNode = ToFbxMesh(meshes[i],lScene);
			if (meshNode)
				lRootNode->AddChild(meshNode);
			else
				ccLog::Warning(QString("[FBX] Failed to convert mesh '%1' to FBX mesh/node!").arg(meshes[i]->getName()));
		}
	}

	// Save the scene.
    bool lResult = SaveScene(lSdkManager, lScene, filename);

    // Destroy all objects created by the FBX SDK.
    if( lSdkManager )
		lSdkManager->Destroy();

	return lResult ? CC_FERR_NO_ERROR : CC_FERR_CONSOLE_ERROR;
}