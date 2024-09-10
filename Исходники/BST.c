// find ceil of a given input in BST. If input is more
// than the max key in BST, return -1
int Ceil(struct node* root, int input)
{
	if (root == NULL)
		return -1;
	if (root->data == input)
		return input;
	if (root->data < input)
		return Ceil(root->right, input);
	
	int ceil = Ceil(root->left, input);
	return (ceil >= input)? ceil: root->data;
}