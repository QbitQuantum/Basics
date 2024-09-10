bool Model::Load( const char *filename ) {

	buffer.Create( Video::VF_GENERIC );

	KFbxImporter *importer = KFbxImporter::Create( manager, "" );

	if( !importer->Initialize( filename, -1, manager->GetIOSettings()) ){
		printf( "error loading model %s\n", filename );
		return false;
	}

	scene = KFbxScene::Create( manager, "scene1" );
	     
	importer->Import( scene );

	// wtf is this for?
	bool shit = scene->GetGlobalSettings().SetDefaultCamera( PRODUCER_BOTTOM );//(char *) lCamera->GetName());

	// convert axis system (should be done by fbx exporter??)
	KFbxAxisSystem SceneAxisSystem = scene->GetGlobalSettings().GetAxisSystem();
    KFbxAxisSystem OurAxisSystem(KFbxAxisSystem::XAxis, KFbxAxisSystem::ParityOdd, KFbxAxisSystem::RightHanded);
    if( SceneAxisSystem != OurAxisSystem )
    {
        OurAxisSystem.ConvertScene(scene);
    }
	importer->Destroy();

	// Get animation names
	scene->FillAnimStackNameArray( AnimationStackNames );
	
	 
	// identify and triangulate meshes in scene
	FindMeshes( scene->GetRootNode() );

	SetAnimationStack(1);
	
    AnimationFrameTime.SetTime(0, 0, 0, 1, 0, scene->GetGlobalSettings().GetTimeMode());

	return true;
}