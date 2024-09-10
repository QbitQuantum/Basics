int main() {
	Solution s;

	TreeLinkNode root(1);
	TreeLinkNode left(2);
	TreeLinkNode right(3);
	root.left = &left;
	root.right = &right;
	root.next = NULL;
	s.connect(&root);

	return 0;
}