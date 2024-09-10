Node* pick(void){
	list<Node*>::iterator it = listNode.begin();
	Node *p = *it;
	for(; it != listNode.end(); it++){
		if (p->f > (*it)->f)
			p = *it;
	}
	listNode.remove(p);
	return p;
}