int main() {
	Solution slt;
	TreeLinkNode *root = new TreeLinkNode(1);
	root->right = new TreeLinkNode(2);
	slt.connect(root);

	return 0;
}