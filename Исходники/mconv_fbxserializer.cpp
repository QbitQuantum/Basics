    bool FbxSerializer::load(const String &path, void *&pData)
    {
        if (mFbxManager == nullptr)
        {
            T3D_LOG_ERROR("FBX Manager haven't been initialized !");
            return false;
        }

        // Create an importer
        FbxImporter *pFbxImporter = FbxImporter::Create(mFbxManager, "");

        // Initialize the importer by providing a filename.
        bool bImportStatus = pFbxImporter->Initialize(path.c_str(), -1, mFbxManager->GetIOSettings());

        if (!bImportStatus)
        {
            T3D_LOG_ERROR("Unable to initialize FBX importer !");
            return false;
        }

        // Import the scene
        bool bStatus = pFbxImporter->Import(mFbxScene);

        // Destroy the importer
        pFbxImporter->Destroy();

        // 统一切换成OpenGL的右手坐标系和以米为单位的坐标系
        FbxAxisSystem::OpenGL.ConvertScene(mFbxScene);
        // 统一以1米为单位
        FbxSystemUnit::m.ConvertScene(mFbxScene);

        // 不是三角形为面的mesh，统一转换成三角形为面的mesh
        FbxGeometryConverter converter(mFbxManager);
        converter.Triangulate(mFbxScene, true);

        pData = mFbxScene;

        return bStatus;
    }