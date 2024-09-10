bool SearchTreeBrowser::handlePressArrowKey(NodePtr& pNode) const
{
	// Arrow key is start with esc
	getch(); // skip the [
	switch(getch()) { // the real value
    case 'A':
        // code for arrow up
    	if (pNode->hasParent()) {
    		pNode = pNode->getParent();
    		return true;
    	}
        break;
    case 'B':
        // code for arrow down
    	if (pNode->hasChild(0)) {
    		pNode = pNode->getChild(0);
    		return true;
    	}
        break;
    case 'C':
        // code for arrow right
    	if (pNode->hasRight()) {
    		pNode = pNode->getRight();
    		return true;
    	}
        break;
    case 'D':
        // code for arrow left
    	if (pNode->hasLeft()) {
    		pNode = pNode->getLeft();
    		return true;
    	}
        break;
	}
	return false;
}