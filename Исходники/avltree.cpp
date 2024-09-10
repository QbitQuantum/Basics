int AVLTree::count_depth(node *r){
	if (r == NULL)
		return 0;
	return 1 + max(count_depth(r->left), count_depth(r->right));
}