int main() {
    Solution so;
    TreeLinkNode *nodes[] = {
        new TreeLinkNode(1),
        new TreeLinkNode(1, new TreeLinkNode(2), new TreeLinkNode(3)),
        new TreeLinkNode(1,
            new TreeLinkNode(2, new TreeLinkNode(4), new TreeLinkNode(5)),
            new TreeLinkNode(3, new TreeLinkNode(6), new TreeLinkNode(7))),
    };
    for (auto node : nodes) {
        so.connect(node);
        printResult(node);
        puts("");
    }
}