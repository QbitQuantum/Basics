Token* Transition::getToken() {
	Node* n;
	n = *inputList.begin();//TODO store

	Token* t = n->getToken();
	return t;

}