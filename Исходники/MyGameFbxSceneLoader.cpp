void MyGameFbxSceneLoader::loadSceneFromFbx( MyGameScene::MyGameSceneManager* sceneMgr, const string& fileName, MyGameSceneNode* node, vector<MyGameSceneEntity*>& entityList )
{
	FbxManager* fbxMgr= FbxManager::Create();
	FbxIOSettings* fbxIO = FbxIOSettings::Create( fbxMgr, IOSROOT );
	fbxMgr->SetIOSettings( fbxIO );

	FbxScene* fbxScene = FbxScene::Create( fbxMgr, "test" );
	FbxImporter* importer = FbxImporter::Create( fbxMgr, "" );

	importer->Initialize( fileName.c_str(), -1, fbxMgr->GetIOSettings() );
	importer->Import( fbxScene );
	fbxIO->Destroy();

	FbxNode* rootNode = fbxScene->GetRootNode();

	FbxGeometryConverter converter( fbxMgr );
	converter.TriangulateInPlace( rootNode );


    getNodeFromFbxNode( sceneMgr, rootNode, node, entityList );

	rootNode->Destroy();


	fbxScene->Destroy();
	fbxMgr->Destroy();
}