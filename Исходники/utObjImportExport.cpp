 virtual bool importerTest() {
     Assimp::Importer importer;
     const aiScene *scene = importer.ReadFile( ASSIMP_TEST_MODELS_DIR "/OBJ/spider.obj", 0 );
     return nullptr != scene;
 }