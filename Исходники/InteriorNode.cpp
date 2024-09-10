bool InteriorNode::remove(int key) {
	// If the removal returns an error, it means it has too few pointers and needs to coalese/redistribute
	Node* containsKey = this->getNodeContaining(key);
	if (containsKey->remove(key)) {
		std::vector< std::pair<int,Node*> >::iterator leftSibling = this->pairs.begin();
		std::vector< std::pair<int,Node*> >::iterator rightSibling = this->pairs.begin();
		std::vector< std::pair<int,Node*> >::iterator pair = this->pairs.begin();
		for (std::vector< std::pair<int,Node*> >::iterator it = this->pairs.begin(); it != this->pairs.end(); ++it) {
			if (it->second == containsKey) {
				pair = it;
				continue;
			}

			if (pair->second != containsKey) {
				leftSibling = it;
			} else {
				rightSibling = it;
				break;
			}
		}
		
		if (leftSibling != pair && (leftSibling->second->getNumOfCurrentPairs() + pair->second->getNumOfCurrentPairs()) < leftSibling->second->getMaxNumOfPairs()) {
			leftSibling->second->coalesce(pair->second);
			leftSibling->first = leftSibling->second->getHighestKey();
			this->pairs.erase(pair);
		} else if (rightSibling != this->pairs.begin() && (rightSibling->second->getNumOfCurrentPairs() + pair->second->getNumOfCurrentPairs()) < rightSibling->second->getMaxNumOfPairs()) {
			pair->second->coalesce(rightSibling->second);
			pair->first = pair->second->getHighestKey();
			this->pairs.erase(rightSibling);
		} else if (leftSibling != pair) {
			leftSibling->second->redistribute(pair->second);
			leftSibling->first = leftSibling->second->getHighestKey();
			return false;
		} else if (rightSibling != this->pairs.begin()) {
			pair->second->redistribute(rightSibling->second);
			pair->first = pair->second->getHighestKey();
			return false;
		}
	}

	return !this->hasSufficientPointers(); 
}