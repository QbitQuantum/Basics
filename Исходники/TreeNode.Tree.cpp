void TreeNode::Tree::createNode(const AbstractTreeIterator& parentPath, const String& name, bool leaf)
{
	if (canCreateNodes() == true)
	{
		TreeNode* parentNode = getTreeNodeFromIterator(parentPath);
		if (parentNode != NULL)
		{
			TreeNode* newNode = (*createNodeFunctor)(name);
			parentNode->addChild(newNode);
			newNode->setParent(parentNode);
		}
		else
		{
			argumentError("Need a TreeNode::Iterator to create a node!" ERROR_AT);
		}
	}
	else
	{
		stateError("Tree can't create nodes!" ERROR_AT);
	}
}