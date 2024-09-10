 virtual bool binaryImporterTest() {
     Assimp::Importer importer;
     const aiScene *scene = importer.ReadFile( ASSIMP_TEST_MODELS_DIR "/glTF2/2CylinderEngine-glTF-Binary/2CylinderEngine.glb", aiProcess_ValidateDataStructure);
     return nullptr != scene;
 }