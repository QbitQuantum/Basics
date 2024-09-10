JNIEXPORT jboolean JNICALL Java_de_tesis_dynaware_javafx_graphics_importers_fbx_JFbxLib_open(JNIEnv *env, jobject obj, jstring filePath) {

	sdkManager = FbxManager::Create();

	FbxIOSettings *ios = FbxIOSettings::Create(sdkManager, IOSROOT);

	sdkManager->SetIOSettings(ios);

	FbxImporter *importer = FbxImporter::Create(sdkManager,"");

	if(!importer->Initialize(env->GetStringUTFChars(filePath, 0), -1, sdkManager->GetIOSettings())) {
		throwIOException(env);
	}

	FbxScene *scene = FbxScene::Create(sdkManager,"");

	importer->Import(scene);
	importer->Destroy();

	currentNode = scene->GetRootNode();

	return JNI_TRUE;
}