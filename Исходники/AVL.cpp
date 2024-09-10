void AVL::balanceLeftLeft(Node* currentNode) {
	Node* temp = currentNode->getLeftChild();

	currentNode->setLeftChild(temp->getRightChild());
	if (temp->getRightChild() != NULL) {
		temp->getRightChild()->setParent(currentNode);
	}

	temp->setRightChild(currentNode);
	temp->setParent(currentNode->getParent());
	if (temp->getParent() != NULL) {
		if (temp->getData() < temp->getParent()->getData()) {
			temp->getParent()->setLeftChild(temp);
		} else {
			temp->getParent()->setRightChild(temp);
		}
	}
	currentNode->setParent(temp);
	if (currentNode == rootNode) {
		rootNode = temp;
	}
}