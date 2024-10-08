int main(int argc, const char *argv[]) {
	//Build tree using insert
    BinarySearchTree tree;
	AsciiTree ascii;
    
    tree.insert(7);
    tree.insert(2);
    tree.insert(1);
    tree.insert(6);
    tree.insert(4);
    tree.insert(3);
    tree.insert(5);
    tree.insert(9);
    tree.insert(8);
    tree.insert(10);
    
    tree.remove(2);
    tree.remove(7);

    ascii.buildTree(tree);
    ascii.draw();

	return 0;
}