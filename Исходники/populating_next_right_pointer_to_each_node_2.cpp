int main(int argc, char const *argv[])
{
	TreeLinkNode* head = new TreeLinkNode(1);
	head->left = new TreeLinkNode(2);
	head->right = new TreeLinkNode(3);
	Solution s;
	s.connect(head);
	return 0;
}