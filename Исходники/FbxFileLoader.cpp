/**
 * FBX ファイルをシーンに読み込む
 *
 * @param file_path FBX ファイルパス
 */
bool FbxFileLoader::load_fbx( const char_t* file_path )
{
	bool result = false;

	if ( fbx_scene_ )
	{
		fbx_scene_->Destroy( true );
	}

	fbx_scene_ = FbxScene::Create( fbx_manager_, "scene" );

	FbxImporter* importer = FbxImporter::Create( fbx_manager_, "" );
    
	if ( importer->Initialize( file_path, -1, fbx_manager_->GetIOSettings() ) )
	{
		result = importer->Import( fbx_scene_ );
	}
	
	importer->Destroy();

	FbxGeometryConverter converter( fbx_manager_ );
	converter.Triangulate( fbx_scene_, true );

	return result;
}