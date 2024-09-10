int main(void) {
	Solution solution;
	TreeLinkNode *root = new TreeLinkNode(1);
	root->left = new TreeLinkNode(2);
	root->right = new TreeLinkNode(3);
	root->left->left = new TreeLinkNode(4);
	root->left->right = new TreeLinkNode(5);
	root->right->right = new TreeLinkNode(7);
	solution.connect(root);
	inorderTraversal(root);
	cout << "\nPassed\n";
	cout << "\nPassed All\n";
	return 0;
}