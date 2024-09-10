int main(void)
{
    TreeLinkNode* root = new TreeLinkNode(1);
    //TreeLinkNode* tmp = root;
    //tmp->left = new TreeLinkNode(2);
    //tmp->right = new TreeLinkNode(3);
    //tmp->right->right = new TreeLinkNode(6);
    //tmp->right->right->right = new TreeLinkNode(8);
    //tmp = tmp->left;
    //tmp->left = new TreeLinkNode(4);
    //tmp->right = new TreeLinkNode(5);
    //tmp->left->left = new TreeLinkNode(7);

    Solution sol;
    sol.connect(root);
    return 0;
}