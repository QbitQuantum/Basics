 bool Fbx::LoadScene( KFbxSdkManager* pSdkManager, KFbxDocument* pScene, const char* pFilename )
{
	int lFileMajor, lFileMinor, lFileRevision;
	int lSDKMajor,  lSDKMinor,  lSDKRevision;
	//int lFileFormat = -1;
	int i, lTakeCount;
	KString lCurrentTakeName;
	bool lStatus;
	char lPassword[1024];

	// Get the file version number generate by the FBX SDK.
	KFbxSdkManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

	// Create an importer.
	KFbxImporter* lImporter = KFbxImporter::Create(pSdkManager,"");

	// Initialize the importer by providing a filename.
	const bool lImportStatus = lImporter->Initialize(pFilename);
	lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

	if( !lImportStatus )
	{
		printf("Call to KFbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", lImporter->GetLastErrorString());

		if (lImporter->GetLastErrorID() == KFbxIO::eFILE_VERSION_NOT_SUPPORTED_YET ||
			lImporter->GetLastErrorID() == KFbxIO::eFILE_VERSION_NOT_SUPPORTED_ANYMORE)
		{
			printf("FBX version number for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
			printf("FBX version number for file %s is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);
		}

		return false;
	}

	printf("FBX version number for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);

	if (lImporter->IsFBX())
	{
		printf("FBX version number for file %s is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);

		// From this point, it is possible to access take information without
		// the expense of loading the entire file.

		printf("Take Information\n");

		lTakeCount = lImporter->GetTakeCount();

		printf("    Number of takes: %d\n", lTakeCount);
		printf("    Current take: \"%s\"\n", lImporter->GetCurrentTakeName());
		printf("\n");

		for(i = 0; i < lTakeCount; i++)
		{
			KFbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

			printf("    Take %d\n", i);
			printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
			printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

			// Change the value of the import name if the take should be imported 
			// under a different name.
			printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

			// Set the value of the import state to false if the take should be not
			// be imported. 
			printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
			printf("\n");
		}

		// Set the import states. By default, the import states are always set to 
		// true. The code below shows how to change these states.
		IOSREF.SetBoolProp(IMP_FBX_MATERIAL,        true);
		IOSREF.SetBoolProp(IMP_FBX_TEXTURE,         true);
		IOSREF.SetBoolProp(IMP_FBX_LINK,            true);
		IOSREF.SetBoolProp(IMP_FBX_SHAPE,           true);
		IOSREF.SetBoolProp(IMP_FBX_GOBO,            true);
		IOSREF.SetBoolProp(IMP_FBX_ANIMATION,       true);
		IOSREF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
	}

	// Import the scene.
	lStatus = lImporter->Import(pScene);

	if(lStatus == false && lImporter->GetLastErrorID() == KFbxIO::ePASSWORD_ERROR)
	{
		printf("Please enter password: "******"%s", lPassword);
		KString lString(lPassword);

		IOSREF.SetStringProp(IMP_FBX_PASSWORD,      lString);
		IOSREF.SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

		lStatus = lImporter->Import(pScene);

		if(lStatus == false && lImporter->GetLastErrorID() == KFbxIO::ePASSWORD_ERROR)
		{
			printf("\nPassword is wrong, import aborted.\n");
		}
	}

	// Destroy the importer.
	lImporter->Destroy();

	return lStatus;
}