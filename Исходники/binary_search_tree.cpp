int main(int, char**)
{
    BinarySearchTree<int> bst;
    bst.insert(1);
    shared_ptr<visual_tree> vt(new BinarySearchTree<int>::VisualTree(bst));

    ascii_tree(vt).print();
    bst.insert(5);
    ascii_tree(vt).print();
    bst.insert(4);
    ascii_tree(vt).print();
    bst.insert(9);
    ascii_tree(vt).print();
    bst.insert(0);
    ascii_tree(vt).print();
    bst.insert(-1);
    ascii_tree(vt).print();
    bst.insert(-9);
    ascii_tree(vt).print();
    bst.remove(1);
    ascii_tree(vt).print();
}