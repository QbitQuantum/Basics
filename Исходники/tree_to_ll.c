void _cleanup(tree *root)
{
        if (root == NULL)
                return;

        _cleanup(root->left);
        root->left = NULL;

        _cleanup(root->right);
        root->right = NULL;
        
        if (root->left == NULL && root->right == NULL) {
                free(root);
                return;
        }
}