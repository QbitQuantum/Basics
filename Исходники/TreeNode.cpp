void TreeNode::deleteSelfAndSubTreeIncludingHiddenChildren()
{
	for (int i = getChildCountIncludingHiddenChildren()-1; i >= 0; --i)
	{
		TreeNode* child = getChild(i);
		child->setParent(NULL); // For performance prevent child from calling removeFromParent()
		child->deleteSelfAndSubTree();
	}

	deleteSelf();
}