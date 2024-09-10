int main() {
    int a[] = {3, 4, 5, 1, 9, 2, 0, 4, 5};
    int m, n = sizeof(a) / sizeof(int);
    for (m = 1; m < n; m <<= 1);
    m <<= 1;
    node *tree = (node *)calloc(m, sizeof(node));
    puts("build");
    PRA(a, n);
    build(tree, a, 0, n-1, 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++)
            a[j] += 1;
        // printf("(%d, %d)\n", 0, i);
        update(tree, a, 0, n-1, 1, 0, i, 1);
    }
    PRA(a, n);
    print_tree(tree, a, 0, n-1, 1);
    puts("query");
    int v;
    for (int i = 0; i < n; i++) {
        v = query(tree, a, 0, n-1, 1, 0, i);
        printf("(%d, %d): %d\n", 0, i, v);
    }
    for (int i = 0; i < n; i++) {
        v = query(tree, a, 0, n-1, 1, i, n-1);
        printf("(%d, %d): %d\n", i, n-1, v);
        assert(v == lsearch(a, i, n-1));
    }
    
    return 0;
}