int main()
{
	Node *root = new Node(1);
	root->left = new Node(2);
	root->right = new Node(3);
	g.connect(root);
	printf("%d\n", root->left->next->val);
	system("pause");
	return 0;
}