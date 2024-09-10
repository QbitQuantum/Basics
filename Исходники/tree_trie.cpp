int main(int argc, const char ** argv) {
    Node node;
    node.insert("cat");
    node.insert("can");
    node.insert("cam");
    node.insert("ban");
    node.insert("ban");
    node.insert("b");
    assert(node.contain("b"));
    assert(!node.contain("ba"));
    assert(node.contain("ban"));
    node.print(0);
    node.remove("cam");
    node.remove("ban");
    node.print(0);
    return 0;
}