SoPath* TSceneKit::GetSoPath(SoNode * theNode )
{
	TSeparatorKit* sunNode = static_cast< TSeparatorKit* > (getPart( "childList[0]", false ) );
	if( !sunNode )	return NULL;

	TSeparatorKit* rootNode = static_cast< TSeparatorKit* > ( sunNode->getPart( "childList[0]", false ) );
	if( !rootNode )	return NULL;

	SoSearchAction* coinSearch = new SoSearchAction();
	coinSearch->setNode( theNode );
	coinSearch->setInterest( SoSearchAction::FIRST );
	coinSearch->apply( rootNode );
	SoPath* nodePath = coinSearch->getPath( );
	return nodePath;
}