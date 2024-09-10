std::string HE::fasterImp(std::string code){
	std::string tmp ="";
	std::string decoded = "";
	Node *n = this->root;
	for(int i = 0; i < code.length(); i++){
		tmp = tmp + code[i];
		while(tmp.compare(n->getBit()) != 0){
			if(code[i] == 1)
				n = n->getRight();
			if(code[i] == 0)
				n = n->getLeft();
			++i;
			tmp = tmp + code[i];
		}
		decoded += n->getC();
		tmp ="";
	}
	return decoded;
}