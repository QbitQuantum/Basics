DLLEXP NodeHandle h3dGetNodeParent( NodeHandle node )
{
	SceneNode *sn = Modules::sceneMan().resolveNodeHandle( node );
	VALIDATE_NODE( sn, "h3dGetNodeParent", 0 );
	
	return sn->getParent() != 0x0 ? sn->getParent()->getHandle() : 0;
}