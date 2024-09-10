void MeshNode::onAttach( SceneNode &parentNode )
{
	// Find parent model node
	SceneNode *node = &parentNode;
	while( node->getType() != SceneNodeTypes::Model ) node = node->getParent();
	_parentModel = (ModelNode *)node;
	_parentModel->markNodeListDirty();
}