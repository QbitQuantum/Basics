 	void visit(XorNode* node){
 		cout << "(XorNode ";
 		Node *left = node->getLeftChild();
 		Node *right = node->getRightChild();
 		left->accept(*this);
 		right->accept(*this);
 		emit("lxor");
 		cout << ")";
 	}