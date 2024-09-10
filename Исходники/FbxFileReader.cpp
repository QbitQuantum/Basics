FbxFileReader::FbxFileReader(const string& filename) : m_pScene(nullptr), m_pSdkManager(nullptr)
{
    // Initialize the resources needed to import fbx files
    m_pSdkManager = FbxManager::Create();
    
	FbxIOSettings* pIOSettings = FbxIOSettings::Create(m_pSdkManager, IOSROOT);
    m_pSdkManager->SetIOSettings(pIOSettings);
	
	FbxImporter* pImporter = FbxImporter::Create(m_pSdkManager,"");
    if( !pImporter->Initialize(filename.c_str(), -1, pIOSettings) )
        throw exception("Failed to initialize FbxImporter.");
    
    // Prepare a scene to contain the fbx data
    m_pScene = FbxScene::Create(m_pSdkManager,"myScene");
    pImporter->Import(m_pScene);

    // Done importing
    pImporter->Destroy();

	//Check if the scene contains a root node
    if( !m_pScene->GetRootNode() )
        throw std::exception("No RootNode could be found.");
}