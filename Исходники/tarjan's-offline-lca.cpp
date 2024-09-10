	void make_set(const value_type& x) {
		setparent(x, x);
		setrank(x, 1);
	}