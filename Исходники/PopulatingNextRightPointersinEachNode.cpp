int main() {
    Solution sol;
    TreeLinkNode * p0;

    {
        p0 = new TreeLinkNode(1);
        p0->left = new TreeLinkNode(2);
        p0->right = new TreeLinkNode(3);
        p0->left->left = new TreeLinkNode(4);
        p0->left->right = new TreeLinkNode(5);
        p0->right->left = new TreeLinkNode(6);
        p0->right->right = new TreeLinkNode(7);
        sol.connect(p0);
        while (p0 != NULL) {
            TreeLinkNode * cur = p0;
            while (cur != NULL) {
                cout << cur->val << "->";
                cur = cur->next;
            }
            cout << "#" << endl;
            p0 = p0->left;
        }
    }

    return 0;
}