unsigned int getParent(CompleteTree *tree, unsigned int i) {
	return getAncestor(tree, i, 1);
}