	bool removeFiltered(const Char* key, int keyLen, Value* value = 0) const
	{
		Ref<Node> node = this;
		while ((node) && (keyLen > 0)) {
			node = node->step<Filter>(*key);
			++key;
			--keyLen;
		}
		bool matchExact = (node) ? node->defined_ : false;
		if (matchExact) {
			if (value) *value = node->value_;
			node->defined_ = false;
			while (node) {
				if (node->defined_ || node->hasChildren()) break;
				Ref<Node> parent = node->parent();
				node->unlink();
				node = parent;
			}
		}
		return matchExact;
	}