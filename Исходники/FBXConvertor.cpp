//--------------------------------------------------------------------------
void ConvertorFBX(const char* lFilename,
	const VeDirectoryPtr& spDest) noexcept
{
	FbxManager* lSdkManager = FbxManager::Create();
	VE_ASSERT_ALWAYS(lSdkManager);
	VeUserLogI("Autodesk FBX SDK version ", lSdkManager->GetVersion());
	FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	VE_ASSERT_ALWAYS(ios);
	lSdkManager->SetIOSettings(ios);
	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "Import for Venus3D");
	VE_ASSERT_ALWAYS(lImporter->Initialize(lFilename, -1, lSdkManager->GetIOSettings()));
	FbxScene* lScene = FbxScene::Create(lSdkManager, "ImportedScnee");
	VE_ASSERT_ALWAYS(lImporter->Import(lScene));
	SaveContent(lScene, spDest);
	lSdkManager->Destroy();
}