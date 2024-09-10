bool FBXScene::LoadScene(const char* filename, std::ostream& output, Vector3& minPos, Vector3& maxPos)
{
    int lFileMajor, lFileMinor, lFileRevision;

    int i, lAnimStackCount;
    bool lStatus;

	FbxIOSettings *ios = FbxIOSettings::Create(mSdkManager, IOSROOT);
	mSdkManager->SetIOSettings(ios);
	FbxGeometryConverter lGConverter(mSdkManager);
	
	// Create an importer using our sdk manager.
	FbxImporter* pFBXImporter = FbxImporter::Create(mSdkManager,"");

    // Initialize the importer by providing a filename.
    const bool lImportStatus = pFBXImporter->Initialize(filename, -1, mSdkManager->GetIOSettings());
	pFBXImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

    if( !lImportStatus )
    {
		output << "FBX Importer Error: " << pFBXImporter->GetStatus().GetErrorString() << std::endl;

        if ( pFBXImporter->GetStatus() == FbxStatus::eInvalidFileVersion )
        {
			output << "FBX version number for file " << filename << " is " << lFileMajor << " " << lFileMinor << " " << lFileRevision << std::endl;
		}

        return false;
    }

    if (pFBXImporter->IsFBX())
    {
		output << "FBX version number for file " << filename << " is " << lFileMajor << " " << lFileMinor << " " << lFileRevision << std::endl;

        // From this point, it is possible to access animation stack information without
        // the expense of loading the entire file.

		output << "Animation Stack Information" << std::endl;

        lAnimStackCount = pFBXImporter->GetAnimStackCount();

		output << "    Number of Animation Stacks: " << lAnimStackCount << std::endl;
		output << "    Current Animation Stack: " << pFBXImporter->GetActiveAnimStackName().Buffer() << std::endl;
		
        for(i = 0; i < lAnimStackCount; i++)
        {
            FbxTakeInfo* lTakeInfo = pFBXImporter->GetTakeInfo(i);

			output << "    Animation Stack " << i << std::endl;
			output << "    Name: " << lTakeInfo->mName.Buffer() << std::endl;
			output << "    Description: " <<  lTakeInfo->mDescription.Buffer() << std::endl;
			output << "    Import Name: " << lTakeInfo->mImportName.Buffer() << std::endl;
			output << "    Import State: " << (lTakeInfo->mSelect ? "true" : "false") << std::endl;
        }
    }
	
    // Import the scene.
    lStatus = pFBXImporter->Import(mScene);

	if ( !lStatus )
	{
		output << "Failed Importing FBX!" << std::endl;
		output << "FBX is password protected!" << std::endl;

		if ( pFBXImporter->GetStatus() == FbxStatus::ePasswordError )
		{
			output << "FBX is password protected!" << std::endl;
		}
	}

	mFilename = pFBXImporter->GetFileName().Buffer();

    // Destroy the importer.
    pFBXImporter->Destroy();
	ios->Destroy();

	ProcessScene(mScene);

	return lStatus;
}