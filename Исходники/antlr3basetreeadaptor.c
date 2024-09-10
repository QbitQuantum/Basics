/** Transform ^(nil x) to x 
 */
static	pANTLR3_BASE_TREE	
   rulePostProcessing	(pANTLR3_BASE_TREE_ADAPTOR adaptor, pANTLR3_BASE_TREE root)
{
	if (root != NULL && root->isNilNode(root))
	{
		if	(root->getChildCount(root) == 0)
		{
			root = NULL;
		}
		else if	(root->getChildCount(root) == 1)
		{
			root = root->getChild(root, 0);
			root->setParent(root, NULL);
			root->setChildIndex(root, -1);
		}
	}

	return root;
}