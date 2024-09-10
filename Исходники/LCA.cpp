TreeNode* getAncestor(TreeNode* root, TreeNode* node1, TreeNode* node2) {
    if(root == NULL || node1 == NULL || node2 == NULL) {
        return root;
    }
    // Divide
    TreeNode* left = getAncestor(root->left, node1, node2);
    TreeNode* right = getAncestor(root->right, node1, node2);
    // Conquer
    if(left == NULL && right == NULL) {
        return NULL;
    }
    if(left == NULL && right != NULL) {
        return right;
    }
    if(left != NULL && right == NULL) {
        return left;
    }
    if(left != NULL && right != NULL) {
        return root;
    }

}