bool AssimpWrapper::importAsset( const IO::Uri &file, ui32 flags ) {
    if ( !file.isValid() ) {
        osre_error( Tag, "URI " + file.getUri() + " is invalid " );
        return false;
    }

    unsigned int importFlags = aiProcess_CalcTangentSpace
        | aiProcess_GenSmoothNormals
        | aiProcess_JoinIdenticalVertices
        | aiProcess_ImproveCacheLocality
        | aiProcess_LimitBoneWeights
        | aiProcess_RemoveRedundantMaterials
        | aiProcess_SplitLargeMeshes
        | aiProcess_Triangulate
        | aiProcess_GenUVCoords
        | aiProcess_SortByPType;
    flags = importFlags;

    m_root = AssetRegistry::getPath( "media" );
    m_absPathWithFile = AssetRegistry::resolvePathFromUri( file );

    String filename;
    Directory::getDirectoryAndFile(m_absPathWithFile, m_root, filename);
    filename = m_root + filename;
    Importer myImporter;
    const aiScene *scene = myImporter.ReadFile( filename, flags );
    if ( nullptr == scene ) {
        m_root = "";
        m_absPathWithFile = "";
        return false;
    }
    convertSceneToModel( scene );
    m_model->setMeshArray( m_meshArray );

    return true;
}