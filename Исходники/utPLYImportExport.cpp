    virtual bool exporterTest() {
        Importer importer;
        Exporter exporter;
        const aiScene *scene = importer.ReadFile(ASSIMP_TEST_MODELS_DIR "/PLY/cube.ply", 0);
        EXPECT_NE(nullptr, scene);
        EXPECT_EQ(aiReturn_SUCCESS, exporter.Export(scene, "ply", ASSIMP_TEST_MODELS_DIR "/PLY/cube_test.ply"));

        return true;
    }