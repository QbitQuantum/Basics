	inline void pushup() {
		if (left != 0 && right != 0) {
			minNode = left->minNode;
			maxNode = right->maxNode;
			sumcross = left->sumcross + right->sumcross + left->maxNode->key.cross(key) + key.cross(right->minNode->key);
		}
		else if (left != 0) {
			minNode = left->minNode;
			maxNode = this;
			sumcross = left->sumcross + left->maxNode->key.cross(key);
		}
		else if (right != 0) {
			minNode = this;
			maxNode = right->maxNode;
			sumcross = right->sumcross + key.cross(right->minNode->key);
		}
		else {
			minNode = maxNode = this;
			sumcross = 0;
		}
	}