void SceneCacheNode<BaseType>::buildTagFilterMenu( void *data, PRM_Name *menu, int maxSize, const PRM_SpareData *, const PRM_Parm * )
{
	SceneCacheNode<BaseType> *node = reinterpret_cast<SceneCacheNode<BaseType>*>( data );
	if ( !node )
	{
		return;
	}
	
	menu[0].setToken( "*" );
	menu[0].setLabel( "*" );
	
	std::string file;
	if ( !node->ensureFile( file ) )
	{
		// mark the end of our menu
		menu[1].setToken( 0 );
		return;
	}
	
	ConstSceneInterfacePtr scene = node->scene( file, node->getPath() );
	if ( !scene )
	{
		// mark the end of our menu
		menu[1].setToken( 0 );
		return;
	}
	
	SceneInterface::NameList tags;
	scene->readTags( tags );
	std::vector<std::string> tagStrings;
	for ( SceneInterface::NameList::const_iterator it=tags.begin(); it != tags.end(); ++it )
	{
		tagStrings.push_back( *it );
	}
	
	node->createMenu( menu, tagStrings );
}