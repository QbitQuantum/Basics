const aiScene* MeshShape::loadMesh(
    const std::string& _uri, const common::ResourceRetrieverPtr& _retriever)
{
    // Remove points and lines from the import.
    aiPropertyStore* propertyStore = aiCreatePropertyStore();
    aiSetImportPropertyInteger(propertyStore,
                               AI_CONFIG_PP_SBP_REMOVE,
                               aiPrimitiveType_POINT
                               | aiPrimitiveType_LINE
                              );

    // Wrap ResourceRetriever in an IOSystem from Assimp's C++ API.  Then wrap
    // the IOSystem in an aiFileIO from Assimp's C API. Yes, this API is
    // completely ridiculous...
    AssimpInputResourceRetrieverAdaptor systemIO(_retriever);
    aiFileIO fileIO = createFileIO(&systemIO);

    // Import the file.
    const aiScene* scene = aiImportFileExWithProperties(
                               _uri.c_str(),
                               aiProcess_GenNormals
                               | aiProcess_Triangulate
                               | aiProcess_JoinIdenticalVertices
                               | aiProcess_SortByPType
                               | aiProcess_OptimizeMeshes,
                               &fileIO,
                               propertyStore
                           );

    // If succeeded, store the importer in the scene to keep it alive. This is
    // necessary because the importer owns the memory that it allocates.
    if(!scene)
    {
        dtwarn << "[MeshShape::loadMesh] Failed loading mesh '" << _uri << "'.\n";
        return nullptr;
    }

    // Assimp rotates collada files such that the up-axis (specified in the
    // collada file) aligns with assimp's y-axis. Here we are reverting this
    // rotation. We are only catching files with the .dae file ending here. We
    // might miss files with an .xml file ending, which would need to be looked
    // into to figure out whether they are collada files.
    std::string extension;
    const size_t extensionIndex = _uri.find_last_of('.');
    if(extensionIndex != std::string::npos)
        extension = _uri.substr(extensionIndex);

    std::transform(std::begin(extension), std::end(extension),
                   std::begin(extension), ::tolower);

    if(extension == ".dae" || extension == ".zae")
        scene->mRootNode->mTransformation = aiMatrix4x4();

    // Finally, pre-transform the vertices. We can't do this as part of the
    // import process, because we may have changed mTransformation above.
    scene = aiApplyPostProcessing(scene, aiProcess_PreTransformVertices);
    if(!scene)
        dtwarn << "[MeshShape::loadMesh] Failed pre-transforming vertices.\n";

    return scene;
}