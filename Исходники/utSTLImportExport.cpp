 virtual bool importerTest() {
     Assimp::Importer importer;
     const aiScene *scene = importer.ReadFile( ASSIMP_TEST_MODELS_DIR "/STL/Spider_ascii.stl", aiProcess_ValidateDataStructure );
     return nullptr != scene;
 }