 virtual bool importerTest() {
     Assimp::Importer importer;
     const aiScene *scene = importer.ReadFile( ASSIMP_TEST_MODELS_DIR "/X3D/ComputerKeyboard.x3d", aiProcess_ValidateDataStructure );
     return nullptr != scene;
 }