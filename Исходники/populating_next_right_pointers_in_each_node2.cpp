int main(int argc, char *argv[])
{
    Solution sol;

    TreeLinkNode *root = new TreeLinkNode(1);
    root->left = new TreeLinkNode(2);
    root->right = new TreeLinkNode(3);
    root->left->left = new TreeLinkNode(4);
    root->left->right = new TreeLinkNode(5);
    // root->right->left = new TreeLinkNode(6);
    root->right->right = new TreeLinkNode(7);

    print_tree_next_value(root);
    sol.connect(root);
    print_tree_next_value(root);

    return 0;
}