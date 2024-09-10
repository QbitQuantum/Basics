int main() {
    int n, v;
    char cmd[32];

    while (scanf("%d", &n) != EOF) {
        BinarySearchTree bst;
        for (int i = 0; i < n; ++i) {
            scanf("%s", cmd);
            if (!strcmp(cmd, "find")) {
                scanf("%d", &v);
                TreeNode *ptr = bst.find(v);
                if (!ptr) {
                    puts("null");
                } else {
                    printf("%x : %d\n", (unsigned)ptr, ptr->v);
                }
            } else if (!strcmp(cmd, "findMin")) {
                TreeNode *mini = bst.findMin();
                if (!mini) {
                    puts("null");
                } else {
                    printf("%x : %d\n", (unsigned)mini, mini->v);
                }
            } else if (!strcmp(cmd, "findMax")) {
                TreeNode *maxi = bst.findMax();
                if (!maxi) {
                    puts("null");
                } else {
                    printf("%x : %d\n", (unsigned)maxi, maxi->v);
                }
            } else if (!strcmp(cmd, "insert")) {
                scanf("%d", &v);
                bst.insert(v);
            } else if (!strcmp(cmd, "remove")) {
                scanf("%d", &v);
                bst.remove(v);
            } else if (!strcmp(cmd, "show")) {
                bst.show();
            }
        }
    }
    return 0;
}