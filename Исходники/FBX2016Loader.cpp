// FBXデータから頂点データにコンバート
// ※パスは「/」でしか通らない
//const char* filename = "../datas/box.fbx";
bool LoadFBXConvertToVertexData(const char* filename, VertexDataArray& outVertexData)
{
	//==============================================================================
	// FBXオブジェクト初期化
	//==============================================================================
	// FBXマネージャー作成
	FbxManager* pFBXManager = FbxManager::Create();

	// シーン作成
	FbxScene* pScene = FbxScene::Create(pFBXManager, "");

	// FBXのIO設定オブジェクト作成
	FbxIOSettings *pIO = FbxIOSettings::Create(pFBXManager, IOSROOT);
	pFBXManager->SetIOSettings(pIO);

	// インポートオブジェクト作成
	FbxImporter* pImporter = FbxImporter::Create(pFBXManager, "");

	// ファイルインポート
	if(pImporter->Initialize(filename, -1, pFBXManager->GetIOSettings()) == false)
	{
		return false;
	}

	// シーンへインポート
	if(pImporter->Import(pScene) == false)
	{
		return false;
	}

	// ※この時点でインポートオブジェクトはいらない
	pImporter->Destroy();

	//==============================================================================
	// FBXオブジェクトの処理
	//==============================================================================
	// シーンのものすべてを三角化
	FbxGeometryConverter geometryConverte(pFBXManager);
	geometryConverte.Triangulate(pScene, true);

	// メッシュ情報処理
	GetMeshData(pScene->GetRootNode(), outVertexData);

	//==============================================================================
	// FBXオブジェクト色々破棄
	//==============================================================================
	pIO->Destroy();
	pScene->Destroy();
	pFBXManager->Destroy();

	getchar();

	return true;
}