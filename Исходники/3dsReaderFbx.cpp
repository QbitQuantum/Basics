bool C3dsReaderFbx::Read()
{
	OBJ_ASSERT(m_pFbxFile);
	if(!m_pFbxFile)
		return false;

	std::string fileName(m_fileName.string()); // Extract native file path string

	KString lCurrentTakeName;
	bool lStatus;

	MSG_INFO("Parsing .3DS file '" << fileName << "'.");

	// Create an importer.
	KFbxImporter* lImporter = m_pFbxFile->GetFbxSdkManager()->CreateKFbxImporter();
	lImporter->SetFileFormat(KFbxImporter::e3D_STUDIO_3DS);

	// Initialize the importer by providing a filename.
	if(lImporter->Initialize(fileName.c_str()) == false)
	{
		MSG_ERROR("Call to KFbxImporter::Initialize() failed. Error returned: " << lImporter->GetLastErrorString());
		return false;
	}

	// Import the scene.
	lStatus = lImporter->Import(*m_pFbxFile->GetFbxScene());

	if(!lStatus)
	{
		MSG_ERROR("Error importing the 3DS scene: " << lImporter->GetLastErrorString());
		return false;
	}

	return true;
}