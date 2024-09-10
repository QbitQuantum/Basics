// 4.6 Write an algorithm to find the 'next' node (i.e., in-order successor) of a given node in a binary search tree.
Node* Tree::FindSuccessor(Node* node) {
	if(node->GetRight() != NULL) { // node has right child/subtree
		node = node->GetRight();
		while(node->GetLeft() != NULL) { // go to the left-most node (min node) in the right subtree
			node = node->GetLeft();
		}
		return node;
	}

	Node* parent = node->GetParent();
	// go up the tree until we encounter a node that is the left child of its parent
	while(parent != NULL && node == parent->GetRight()) {
		node = parent;
		parent = parent->GetParent();
	}
	return parent;
}